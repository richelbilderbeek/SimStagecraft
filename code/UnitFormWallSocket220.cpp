//---------------------------------------------------------------------------

#include <cassert>
#include "UnitMachine.h"
#include "UnitWallSocket220.h"
#include "UnitConnectorControl.h"
#include "UnitImage.h"
#include "UnitFormWallSocket220.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
FormWallSocket220::FormWallSocket220(FormSimStagecraftMain * const formParent)
  : FormMachine(formParent,DesignClientWidth,DesignClientHeight),
    mSocket220(std::shared_ptr<WallSocket220>(new WallSocket220))
{
  mSocket220Control = std::shared_ptr<Socket220Control>(
    new Socket220Control( this,mSocket220->mSocket220,ImageSocket220));

  CreateWatermark(ImageView,ImageWatermark);

  Resize();
}
//---------------------------------------------------------------------------
void FormWallSocket220::UpdateBuffer()
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
      DrawOnBuffer(ImageSocket220);
      break;
    default: assert(!"Should not get here");
  }
  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void FormWallSocket220::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      break;
    case modeConnect:
      if (OnImage(x,y,ImageSocket220))
        mFormParent->OnConnectorClick(mSocket220Control.get());
      break;
    default: assert(!"Should not get here");
  }
}
//---------------------------------------------------------------------------
void FormWallSocket220::OnAfterResize()
{
  PlaceInCenter(ImageSocket220,ClientRect());
}
//---------------------------------------------------------------------------


