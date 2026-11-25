//---------------------------------------------------------------------------

#include <cassert>
#include <cmath>
#include <stdexcept>
#include "UnitControllerControl.h"
#include "UnitConnectorControl.h"
#include "UnitDisplayControl.h"
#include "UnitMachine.h"
#include "UnitSpeaker.h"
#include "UnitImage.h"
#include "UnitFormRcf322A.h"
#include "UnitFormMachine.h"
#include "UnitFormSprites.h"

#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
FormRcf322A::FormRcf322A(FormSimStagecraftMain * const formParent)
  : FormMachine(formParent,DesignClientWidth,DesignClientHeight),
    mSpeaker(std::shared_ptr<Rcf322A>(new Rcf322A))
{
  //Control
  mPowerSwitch = std::shared_ptr<TwoSwitchControl>(
    new TwoSwitchControl(this,
      mSpeaker->mPowerSwitch,ImageTwoSwitchPower));
  mVolumeDial = std::shared_ptr<DialControl>(
    new DialControl(this,
      mSpeaker->mVolumeDial,ImageVolumeDial));
  //Connect
  mEuroMale = std::shared_ptr<EuroMaleControl>(
    new EuroMaleControl(this,mSpeaker->mEuroMalePower,ImageEuroMale));
  mXlrFemale = std::shared_ptr<XlrFemaleControl>(
    new XlrFemaleControl(this,mSpeaker->mXlrInput,ImageXlrFemale));
  mXlrMale = std::shared_ptr<XlrMaleControl>(
    new XlrMaleControl(this,mSpeaker->mXlrDaisyChain,ImageXlrMale));
  mJackFemale = std::shared_ptr<JackFemaleControl>(
    new JackFemaleControl(this,mSpeaker->mJackInput,ImageJackFemale));
  //Display
  mLedPower = std::shared_ptr<LedControl>(new LedControl(
    mSpeaker->mLedPower,ImageLedPower));
  mLedLimProt = std::shared_ptr<LedControl>(new LedControl(
    mSpeaker->mLedLimProt,ImageLedLimProt));


  CreateWatermark(ImageView,ImageWatermark);

  SetPictureWidth(ImageVolumeDial,50);
  SetPictureHeight(ImageVolumeDial,50);
  ImageVolumeDial->transparent = true;

  Resize();

  //Set controls by clicking virtually
  mVolumeDial->OnMouseDown(
    1 * ImageVolumeDial->picture.width()  / 4,
    3 * ImageVolumeDial->picture.height() / 4);
  mPowerSwitch->OnMouseDown(0,0);
}
//---------------------------------------------------------------------------
void FormRcf322A::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      DrawImage(ImageBuffer,0,0,ImageView);
      break;
    case modeUse:
      //Update all
      mLedPower->Update();
      mLedLimProt->Update();
      DrawAudioSignal(ImageSound,mSpeaker->GetSoundLevel());
      //Start drawing
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      //Labels
      DrawOnBuffer(LabelUseVolume);
      DrawOnBuffer(LabelUsePowerOn);
      DrawOnBuffer(LabelUseLimProt);
      //Controls
      DrawOnBuffer(ImageVolumeDial);
      DrawOnBuffer(ImageTwoSwitchPower);
      DrawOnBuffer(ImageSound);
      DrawOnBuffer(ImageLedPower);
      DrawOnBuffer(ImageLedLimProt);
      break;
    case modeConnect:
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      //Labels
      DrawOnBuffer(LabelConnectBalanced);
      DrawOnBuffer(LabelConnectMains);
      //Connectors
      DrawOnBuffer(ImageXlrFemale);
      DrawOnBuffer(ImageXlrMale);
      DrawOnBuffer(ImageEuroMale);
      DrawOnBuffer(ImageJackFemale);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void FormRcf322A::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      if (OnImage(x,y,ImageVolumeDial))
      {
        mVolumeDial->OnMouseDown(
          x - ImageVolumeDial->left,
          y - ImageVolumeDial->top);
      }
      else if (OnImage(x,y,ImageTwoSwitchPower))
      {
        mPowerSwitch->OnMouseDown(
          x - ImageTwoSwitchPower->left,
          y - ImageTwoSwitchPower->top);
      }
      break;
    case modeConnect:
      if (OnImage(x,y,ImageXlrMale   )) mFormParent->OnConnectorClick(mXlrMale.get()   );
      if (OnImage(x,y,ImageXlrFemale )) mFormParent->OnConnectorClick(mXlrFemale.get() );
      if (OnImage(x,y,ImageEuroMale  )) mFormParent->OnConnectorClick(mEuroMale.get()  );
      if (OnImage(x,y,ImageJackFemale)) mFormParent->OnConnectorClick(mJackFemale.get());
      break;
  }
}
//---------------------------------------------------------------------------
void FormRcf322A::OnAfterResize()
{
  //Use
  {
    //Get y-x-ordered vector of QRects
    const std::vector<std::vector<QRect> > v(GetRectsGrid(ClientRect(),2,6));
    //Resize bitmaps
      //SetPictureHeight(ImageFader1,MergeRects(v[3][2],v[5][2]).height());
      //ImageFader1->Refresh();
    //Place bitmaps
    //Labels
    PlaceInCenter(LabelUseVolume,v[0][0]);
    PlaceInCenter(LabelUsePowerOn,v[2][1]);
    PlaceInCenter(LabelUseLimProt,v[4][1]);
    //Controls
    PlaceInCenter(ImageVolumeDial,v[1][0]);
    PlaceInCenter(ImageTwoSwitchPower,v[4][0]);
    //Displays
    PlaceInCenter(ImageSound,MergeRects(v[0][1],v[1][1]));
    PlaceInCenter(ImageLedPower,v[3][1]);
    PlaceInCenter(ImageLedLimProt,v[5][1]);
  }
  //Connect
  {
    const std::vector<std::vector<QRect> > v(GetRectsGrid(ClientRect(),1,6));
    //Labels
    PlaceInCenter(LabelConnectBalanced  ,v[0][0]);
    PlaceInCenter(LabelConnectMains     ,v[4][0]);
    //Connectors
    PlaceInCenter(ImageJackFemale,v[1][0]);
    PlaceInCenter(ImageXlrFemale ,v[2][0]);
    PlaceInCenter(ImageXlrMale   ,v[3][0]);
    PlaceInCenter(ImageEuroMale  ,v[5][0]);
  }
}
//---------------------------------------------------------------------------

