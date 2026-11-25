//---------------------------------------------------------------------------

#include <cassert>
#include <stdexcept>
#include "UnitControllerControl.h"
#include "UnitConnectorControl.h"
#include "UnitMachine.h"
#include "UnitLamp.h"
#include "UnitImage.h"
#include "UnitFormPar64.h"
#include "UnitFormMachine.h"
#include "UnitFormSprites.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
FormPar64::FormPar64(FormSimStagecraftMain * const formParent)
  : FormMachine(formParent,DesignClientWidth,DesignClientHeight),
    mPar64(std::shared_ptr<Par64>(new Par64))
{
  //Control
  //Connect
  mPlug220 = std::shared_ptr<Plug220Control>(
    new Plug220Control(this,mPar64->mPlug220,ImagePlug220));

  CreateWatermark(ImageView,ImageWatermark);

  Resize();
}
//---------------------------------------------------------------------------
void FormPar64::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      DrawImage(ImageBuffer,0,0,ImageView);
      break;
    case modeUse:
      //Update images
      DrawLamp(ImageLamp,mPar64->GetLightIntensity(),255,255,0);
      //Update buffer
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      DrawOnBuffer(ImageLamp);
      break;
    case modeConnect:
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      DrawOnBuffer(ImagePlug220);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
  //Drawing is done by FormSimStagecraftMain
}
//---------------------------------------------------------------------------
void FormPar64::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      break;
    case modeConnect:
      if (OnImage(x,y,ImagePlug220))
      {
        mFormParent->OnConnectorClick(mPlug220.get());
      }
      break;
  }
}
//---------------------------------------------------------------------------
void FormPar64::OnAfterResize()
{
  PlaceInCenter(ImageLamp,ClientRect());
  PlaceInCenter(ImagePlug220,ClientRect());
}
//---------------------------------------------------------------------------

