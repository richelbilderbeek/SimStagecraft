//---------------------------------------------------------------------------

#include <cassert>
#include "UnitConnectorControl.h"
#include "UnitControllerControl.h"
#include "UnitDisplayControl.h"
#include "UnitFormEasyAmp.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
#include "UnitAmplifier.h"
#include "UnitImage.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
FormEasyAmp::FormEasyAmp(FormSimStagecraftMain * const formParent)
  : FormMachine(formParent,DesignClientWidth,DesignClientHeight),
    mAmplifier(std::shared_ptr<EasyAmp>(new EasyAmp))
{


  //Control
  mPowerSwitch = std::shared_ptr<TwoSwitchControl>(
    new TwoSwitchControl(this,mAmplifier->mPowerSwitch,ImagePowerSwitch));
    std::shared_ptr<DialControl> mGain;
  this->mGain = std::shared_ptr<DialControl>(
    new DialControl(this,mAmplifier->mGain,ImageGain));
  assert(this->mGain);
  //Connect
  mEuro = std::shared_ptr<EuroMaleControl>(
    new EuroMaleControl(this,mAmplifier->mEuroPower,ImageEuro));
  mJackXlrL = std::shared_ptr<JackXlrFemaleControl>(
    new JackXlrFemaleControl(this,mAmplifier->mJackXlrL,ImageJackXlrL));
  mJackXlrR = std::shared_ptr<JackXlrFemaleControl>(
    new JackXlrFemaleControl(this,mAmplifier->mJackXlrR,ImageJackXlrR));
  mSpeakonL = std::shared_ptr<SpeakonFemaleControl>(
    new SpeakonFemaleControl(this,mAmplifier->mSpeakonL,ImageSpeakonL));
  mSpeakonR = std::shared_ptr<SpeakonFemaleControl>(
    new SpeakonFemaleControl(this,mAmplifier->mSpeakonR,ImageSpeakonR));
  //Display
  mLedPower = std::shared_ptr<LedControl> (
    new LedControl(mAmplifier->mLedPower,ImageLed));

  CreateWatermark(ImageView,ImageWatermark);

  Resize();

  //Set controls by clicking virtually
  //Strange, if I remove 'this' I get access violations,
  //  because mGain is null (where this->mGain is not)
  this->mGain->OnMouseDown(
    1 * ImageGain->picture.width()  / 4,
    3 * ImageGain->picture.height() / 4);
  mPowerSwitch->OnMouseDown(0,0);
}
//---------------------------------------------------------------------------
void FormEasyAmp::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      DrawImage(ImageBuffer,0,0,ImageView);
      break;
    case modeUse:
      //Update displays
      mLedPower->Update();
      //Draw
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      //Labels
      //Controls
      DrawOnBuffer(ImagePowerSwitch);
      DrawOnBuffer(ImageGain);
      //Display
      DrawOnBuffer(ImageLed);
      break;
    case modeConnect:
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      //Labels
      //Connectors
      DrawOnBuffer(ImageEuro);
      DrawOnBuffer(ImageJackXlrL);
      DrawOnBuffer(ImageJackXlrR);
      DrawOnBuffer(ImageSpeakonL);
      DrawOnBuffer(ImageSpeakonR);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void FormEasyAmp::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      if (OnImage(x,y,ImagePowerSwitch))
      {
        mPowerSwitch->OnMouseDown(
          x - ImagePowerSwitch->left,
          y - ImagePowerSwitch->top);
      }
      else if (OnImage(x,y,ImageGain))
      {
        assert(this->mGain);
        this->mGain->OnMouseDown(
          x - ImageGain->left,
          y - ImageGain->top);
      }
      break;
    case modeConnect:
      if (OnImage(x,y,ImageEuro))
        mFormParent->OnConnectorClick(mEuro.get());
      else if (OnImage(x,y,ImageJackXlrL))
        mFormParent->OnConnectorClick(mJackXlrL.get());
      else if (OnImage(x,y,ImageJackXlrR))
        mFormParent->OnConnectorClick(mJackXlrR.get());
      else if (OnImage(x,y,ImageSpeakonL))
        mFormParent->OnConnectorClick(mSpeakonL.get());
      else if (OnImage(x,y,ImageSpeakonR))
        mFormParent->OnConnectorClick(mSpeakonR.get());
      break;
  }
}
//---------------------------------------------------------------------------
void FormEasyAmp::OnAfterResize()
{
  //Use
  {
    const std::vector<std::vector<QRect> > v(GetRectsGrid(ClientRect(),3,1));
    //Resize bitmaps
    //Place bitmaps
    //Labels
    //Controls
    PlaceInCenter(ImagePowerSwitch,v[0][0]);
    PlaceInCenter(ImageGain,v[0][1]);
    //Others
    //Displays
    PlaceInCenter(ImageLed,v[0][2]);
  }
  //Connect
  {
    const std::vector<std::vector<QRect> > v(GetRectsGrid(ClientRect(),3,2));
    //Labels
    //Connectors
    PlaceInCenter(ImageEuro,MergeRects(v[0][0],v[1][0]));
    PlaceInCenter(ImageJackXlrL,v[0][1]);
    PlaceInCenter(ImageJackXlrR,v[0][2]);
    PlaceInCenter(ImageSpeakonL,v[1][1]);
    PlaceInCenter(ImageSpeakonR,v[1][2]);
  }
}
//---------------------------------------------------------------------------

