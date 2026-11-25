//---------------------------------------------------------------------------

#include <cassert>
#include <stdexcept>
#include "UnitControllerControl.h"
#include "UnitConnectorControl.h"
#include "UnitMachine.h"
#include "UnitTriplet.h"
#include "UnitImage.h"
#include "UnitFormTriplet.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
FormTriplet::FormTriplet(FormSimStagecraftMain * const formParent)
  : FormMachine(formParent,DesignClientWidth,DesignClientHeight),
    mTriplet(std::shared_ptr<Triplet>(new Triplet))
{

  //Control
  //Connect
  mSocket220_1 = std::shared_ptr<Socket220Control>(
    new Socket220Control(this,mTriplet->mSocket220_1,ImageSocket220_1));
  mSocket220_2 = std::shared_ptr<Socket220Control>(
    new Socket220Control(this,mTriplet->mSocket220_2,ImageSocket220_2));
  mSocket220_3 = std::shared_ptr<Socket220Control>(
    new Socket220Control(this,mTriplet->mSocket220_3,ImageSocket220_3));
  mPlug220 = std::shared_ptr<Plug220Control>(
    new Plug220Control(this,mTriplet->mPlug,ImagePlug220));

  CreateWatermark(ImageView,ImageWatermark);

  Resize();
}
//---------------------------------------------------------------------------
void FormTriplet::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      DrawImage(ImageBuffer,0,0,ImageView);
      break;
    case modeUse:
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      break;
    case modeConnect:
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      DrawOnBuffer(ImageSocket220_1);
      DrawOnBuffer(ImageSocket220_2);
      DrawOnBuffer(ImageSocket220_3);
      DrawOnBuffer(ImagePlug220);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void FormTriplet::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      break;
    case modeConnect:
      if (OnImage(x,y,ImageSocket220_1)) mFormParent->OnConnectorClick(mSocket220_1.get());
      if (OnImage(x,y,ImageSocket220_2)) mFormParent->OnConnectorClick(mSocket220_2.get());
      if (OnImage(x,y,ImageSocket220_3)) mFormParent->OnConnectorClick(mSocket220_3.get());
      if (OnImage(x,y,ImagePlug220)) mFormParent->OnConnectorClick(mPlug220.get());
      break;
  }
}
//---------------------------------------------------------------------------
void FormTriplet::OnAfterResize()
{
  const std::vector<QRect> v(GetRectsHorizontal(ClientRect(),4));
  PlaceInCenter(ImageSocket220_1,v[0]);
  PlaceInCenter(ImageSocket220_2,v[1]);
  PlaceInCenter(ImageSocket220_3,v[2]);
  PlaceInCenter(ImagePlug220    ,v[3]);
}
//---------------------------------------------------------------------------


