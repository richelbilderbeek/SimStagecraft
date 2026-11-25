//---------------------------------------------------------------------------

#include <cassert>
#include "UnitMachine.h"
#include "UnitWallSocketPower.h"
#include "UnitConnectorControl.h"
#include "UnitImage.h"
#include "UnitFormWallSocketPower.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
FormWallSocketPower::FormWallSocketPower(FormSimStagecraftMain * const formParent)
  : FormMachine(formParent,DesignClientWidth,DesignClientHeight),
    mSocketPower(std::shared_ptr<WallSocketPower>(new WallSocketPower))
{
  //Connect
  mSocketPowerControl = std::shared_ptr<SocketPowerFemaleControl>(
    new SocketPowerFemaleControl( this,mSocketPower->mSocketPower,ImageSocketPower));


  CreateWatermark(ImageView,ImageWatermark);

  Resize();
}
//---------------------------------------------------------------------------
void FormWallSocketPower::UpdateBuffer()
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
      DrawOnBuffer(ImageSocketPower);
      break;
    default: assert(!"Should not get here");
  }
  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void FormWallSocketPower::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      break;
    case modeConnect:
      if (OnImage(x,y,ImageSocketPower))
        mFormParent->OnConnectorClick(mSocketPowerControl.get());
      break;
    default: assert(!"Should not get here");
  }
}
//---------------------------------------------------------------------------
void FormWallSocketPower::OnAfterResize()
{
  PlaceInCenter(ImageSocketPower,ClientRect());
}
//---------------------------------------------------------------------------

