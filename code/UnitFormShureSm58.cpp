//---------------------------------------------------------------------------

#include <cassert>
#include "UnitConnectorControl.h"
#include "UnitMachine.h"
#include "UnitMicrophone.h"
#include "UnitFunctions.h"
#include "UnitImage.h"
#include "UnitFormShureSm58.h"
#include "UnitFormSprites.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
FormShureSm58::FormShureSm58(FormSimStagecraftMain * const formParent)
  : FormMachine(formParent,DesignClientWidth,DesignClientHeight),
    mMicrophone(std::shared_ptr<ShureSm58>(new ShureSm58)),
    mSinging(false),
    mSingerAverage( 0.4 + GetRandomUniform() * 0.6)
{
  //Use
  //Connect
  mXlrMale = std::shared_ptr<XlrMaleControl>(
    new XlrMaleControl(this,mMicrophone->mXlrInput,ImageXlrMale));

  AddTimer(100,[this]() { TimerSingTimer(); });

  Resize();

  CreateWatermark(ImageView,ImageWatermark);
}
//---------------------------------------------------------------------------
void FormShureSm58::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView   :
      DrawImage(ImageBuffer,0,0,ImageView);
      break;
    case modeUse    :
      //Set new audio signal
      DrawAudioSignal(ImageAudioSignal,mMicrophone->GetAudioSignalStrength());
      //Draw 'Use' images
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      DrawOnBuffer(ImageSing);
      DrawOnBuffer(ImageAudioSignal);
      break;
    case modeConnect:
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      DrawOnBuffer(ImageXlrMale);
      break;
    default: assert(!"Should not get here");
  }
  DrawBorderAroundBuffer();
  //Drawing is done by FormSimStagecraftMain
}
//---------------------------------------------------------------------------
void FormShureSm58::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      if (OnImage(x,y,ImageSing))
      {
        if (mSinging == true)
        {
          mSinging = false;
          mMicrophone->SetAudioSignalStrength(0.0);
          ImageSing->AssignPicture(Sprites()->ImageSingNo);
        }
        else
        {
          mSinging = true;
          mMicrophone->SetAudioSignalStrength(1.0);
          ImageSing->AssignPicture(Sprites()->ImageSingYes);
        }
        mFormParent->OnControllerClick();
      }
      break;
    case modeConnect:
      if (OnImage(x,y,ImageXlrMale))
      {
        mFormParent->OnConnectorClick(mXlrMale.get());
      }
      break;
  }
}
//---------------------------------------------------------------------------
void FormShureSm58::TimerSingTimer()
{
  //This singer sings at a strength of mSingerAverage
  // plus or minus 0.5 * mSingerAverage
  const double audioSignalStrength = (mSinging == true
    ? (0.5 * mSingerAverage) + (GetRandomUniform() * mSingerAverage)
    : 0.0);
  mMicrophone->SetAudioSignalStrength(audioSignalStrength);
  DrawAudioSignal(ImageAudioSignal,mMicrophone->GetAudioSignalStrength());
  mFormParent->OnControllerClick();
}
//---------------------------------------------------------------------------
void FormShureSm58::OnAfterResize()
{
  const std::vector<QRect> v(GetRectsHorizontal(ClientRect(),2));
  PlaceInCenter(ImageSing,v[0]);
  PlaceInCenter(ImageAudioSignal,v[1]);
  PlaceInCenter(ImageXlrMale,ClientRect());
}
//---------------------------------------------------------------------------


