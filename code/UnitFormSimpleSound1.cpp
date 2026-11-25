//---------------------------------------------------------------------------

#include <cassert>
#include "UnitConnectorControl.h"
#include "UnitControllerControl.h"
#include "UnitDisplayControl.h"
#include "UnitSimpleSound1.h"
#include "UnitFormSimpleSound1.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
#include "UnitImage.h"
//---------------------------------------------------------------------------
FormSimpleSound1::FormSimpleSound1(FormSimStagecraftMain * const formParent)
  : FormMachine(formParent,DesignClientWidth,DesignClientHeight),
    mSoundTable(std::shared_ptr<SimpleSound1>(new SimpleSound1))
{

  //Control
  mFaderControlMaster = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSoundTable->mFaderMaster,ImageFaderMaster));
  //Connect
  mEuroMalePower = std::shared_ptr<EuroMaleControl>(
    new EuroMaleControl(this,mSoundTable->mPower,ImageEuroMalePower));
  mXlrFemaleMic1 = std::shared_ptr<XlrFemaleControl>(
    new XlrFemaleControl(this,mSoundTable->mMic1,ImageXlrFemaleMic1));
  mXlrMaleMasterLeft = std::shared_ptr<XlrMaleControl>(
    new XlrMaleControl(this,mSoundTable->mMasterL,ImageXlrMaleMasterLeft));
  mXlrMaleMasterRight = std::shared_ptr<XlrMaleControl>(
    new XlrMaleControl(this,mSoundTable->mMasterR,ImageXlrMaleMasterRight));
  //Display
  mAudioSignalDisplay = std::shared_ptr<AudioSignalControl>(
    new AudioSignalControl(mSoundTable->mAudioSignalDisplay,ImageAudioSignal));

  CreateWatermark(ImageView,ImageWatermark);

  //Make some images transparent
  Resize();
  //Manually set the faders
  mFaderControlMaster->OnMouseDown(0,ImageFaderMaster->picture.height() - 1);
}
//---------------------------------------------------------------------------
void FormSimpleSound1::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      DrawImage(ImageBuffer,0,0,ImageView);
      break;
    case modeUse:
      //Update displays
      mAudioSignalDisplay->Update();
      //Draw
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      //Labels
      DrawOnBuffer(LabelUseMaster);
      DrawOnBuffer(LabelUseSimpleSound1);
      //Controllers
      DrawOnBuffer(ImageFaderMaster);
      //Display
      DrawOnBuffer(ImageAudioSignal);
      break;
    case modeConnect:
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      DrawOnBuffer(ImageXlrFemaleMic1);
      DrawOnBuffer(ImageXlrMaleMasterLeft);
      DrawOnBuffer(ImageXlrMaleMasterRight);
      DrawOnBuffer(ImageEuroMalePower);
      DrawOnBuffer(ImageConnectMic);
      DrawOnBuffer(ImageConnect1);
      DrawOnBuffer(ImageConnectMaster);
      DrawOnBuffer(ImageConnectL);
      DrawOnBuffer(ImageConnectR);
      DrawOnBuffer(ImageConnectPower);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void FormSimpleSound1::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      if (OnImage(x,y,ImageFaderMaster))
      {
        mFaderControlMaster->OnMouseDown(
          x - ImageFaderMaster->left,
          y - ImageFaderMaster->top);
      }
      break;
    case modeConnect:
      if (OnImage(x,y,ImageXlrFemaleMic1))
        mFormParent->OnConnectorClick(mXlrFemaleMic1.get());
      if (OnImage(x,y,ImageXlrMaleMasterLeft))
        mFormParent->OnConnectorClick(mXlrMaleMasterLeft.get());
      if (OnImage(x,y,ImageXlrMaleMasterRight))
        mFormParent->OnConnectorClick(mXlrMaleMasterRight.get());
      if (OnImage(x,y,ImageEuroMalePower))
        mFormParent->OnConnectorClick(mEuroMalePower.get());
      break;
  }
}
//---------------------------------------------------------------------------
void FormSimpleSound1::OnAfterResize()
{
  //Use
  {
    const std::vector<std::vector<QRect> > v(GetRectsGrid(ClientRect(),2,5));
    //Resize images
    SetPictureHeight(ImageFaderMaster,MergeRects(v[1][0],v[3][0]).height());
    //Placement
    PlaceInCenter(LabelUseMaster,v[0][0]);
    PlaceInCenter(LabelUseSimpleSound1,v[0][1]);
    PlaceInCenter(ImageAudioSignal,MergeRects(v[1][1],v[3][1]));
    PlaceInCenter(ImageFaderMaster,MergeRects(v[1][0],v[3][0]));
  }
  //Connect
  {
    const std::vector<std::vector<QRect> > v(GetRectsGrid(ClientRect(),4,6));
    PlaceInCenter(ImageConnectMic   ,v[1][0]);
    PlaceInCenter(ImageConnect1     ,v[2][0]);
    PlaceInCenter(ImageConnectMaster,MergeRects(v[1][1],v[1][2]));
    PlaceInCenter(ImageConnectL     ,v[2][1]);
    PlaceInCenter(ImageConnectR     ,v[2][2]);
    PlaceInCenter(ImageConnectPower ,v[2][3]);
    PlaceInCenter(ImageXlrFemaleMic1     ,MergeRects(v[3][0],v[4][0]));
    PlaceInCenter(ImageXlrMaleMasterLeft ,MergeRects(v[3][1],v[4][1]));
    PlaceInCenter(ImageXlrMaleMasterRight,MergeRects(v[3][2],v[4][2]));
    PlaceInCenter(ImageEuroMalePower     ,MergeRects(v[3][3],v[4][3]));
  }
}
//---------------------------------------------------------------------------





