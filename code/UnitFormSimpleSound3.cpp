//---------------------------------------------------------------------------

#include <cassert>
#include "UnitConnectorControl.h"
#include "UnitControllerControl.h"
#include "UnitDisplayControl.h"
#include "UnitSimpleSound3.h"
#include "UnitFormSimpleSound3.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
#include "UnitImage.h"
//---------------------------------------------------------------------------
FormSimpleSound3::FormSimpleSound3(FormSimStagecraftMain * const formParent)
  : FormMachine(formParent,DesignClientWidth,DesignClientHeight),
    mSoundTable(std::shared_ptr<SimpleSound3>(new SimpleSound3))
{

  //Control
  mFaderControl1 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSoundTable->mFader1,ImageFader1));
  mFaderControl2 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSoundTable->mFader2,ImageFader2));
  mFaderControl3 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSoundTable->mFader3,ImageFader3));
  mPressButtonControlPfl1 = std::shared_ptr<PressButtonControl>(
    new PressButtonControl(this,mSoundTable->mPressButtonPfl1,ImagePressButtonPfl1));
  mPressButtonControlPfl2 = std::shared_ptr<PressButtonControl>(
    new PressButtonControl(this,mSoundTable->mPressButtonPfl2,ImagePressButtonPfl2));
  mPressButtonControlPfl3 = std::shared_ptr<PressButtonControl>(
    new PressButtonControl(this,mSoundTable->mPressButtonPfl3,ImagePressButtonPfl3));
  mDialControlGain1 = std::shared_ptr<DialControl>(
    new DialControl(this,mSoundTable->mDialGain1,ImageDialGain1));
  mDialControlGain2 = std::shared_ptr<DialControl>(
    new DialControl(this,mSoundTable->mDialGain2,ImageDialGain2));
  mDialControlGain3 = std::shared_ptr<DialControl>(
    new DialControl(this,mSoundTable->mDialGain3,ImageDialGain3));
  mDialControlAux1_1 = std::shared_ptr<DialControl>(
    new DialControl(this,mSoundTable->mDialAux1_1,ImageDialAux1_1));
  mDialControlAux1_2 = std::shared_ptr<DialControl>(
    new DialControl(this,mSoundTable->mDialAux1_2,ImageDialAux1_2));
  mDialControlAux1_3 = std::shared_ptr<DialControl>(
    new DialControl(this,mSoundTable->mDialAux1_3,ImageDialAux1_3));
  mDialControlSendAux1 = std::shared_ptr<DialControl>(
    new DialControl(this,mSoundTable->mDialSendAux1,ImageDialSendAux1));
  mFaderControlMaster = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSoundTable->mFaderMaster,ImageFaderMaster));
  //Connect
  mEuroMalePower = std::shared_ptr<EuroMaleControl>(
    new EuroMaleControl(this,mSoundTable->mPower,ImageEuroMalePower));
  mJackFemaleAux1 = std::shared_ptr<JackFemaleControl>(
    new JackFemaleControl(this,mSoundTable->mAux1,ImageJackFemaleAux1));
  mXlrFemaleMic1 = std::shared_ptr<XlrFemaleControl>(
    new XlrFemaleControl(this,mSoundTable->mMic1,ImageXlrFemaleMic1));
  mXlrFemaleMic2 = std::shared_ptr<XlrFemaleControl>(
    new XlrFemaleControl(this,mSoundTable->mMic2,ImageXlrFemaleMic2));
  mXlrFemaleMic3 = std::shared_ptr<XlrFemaleControl>(
    new XlrFemaleControl(this,mSoundTable->mMic3,ImageXlrFemaleMic3));
  mXlrMaleMasterLeft = std::shared_ptr<XlrMaleControl>(
    new XlrMaleControl(this,mSoundTable->mMasterL,ImageXlrMaleMasterLeft));
  mXlrMaleMasterRight = std::shared_ptr<XlrMaleControl>(
    new XlrMaleControl(this,mSoundTable->mMasterR,ImageXlrMaleMasterRight));
  //Display
  mAudioSignalDisplay = std::shared_ptr<AudioSignalControl>(
    new AudioSignalControl(mSoundTable->mAudioSignalDisplay,ImageAudioSignal));

  CreateWatermark(ImageView,ImageWatermark);

  Resize();
  //Manually set the faders
  mFaderControl1->OnMouseDown(0,ImageFader1->picture.height() - 1);
  mFaderControl2->OnMouseDown(0,ImageFader2->picture.height() - 1);
  mFaderControl3->OnMouseDown(0,ImageFader3->picture.height() - 1);
  mFaderControlMaster->OnMouseDown(0,ImageFaderMaster->picture.height() - 1);
  //Press buttons in and out
  //In
  mPressButtonControlPfl1->OnMouseDown(0,ImagePressButtonPfl1->picture.height() - 1);
  mPressButtonControlPfl2->OnMouseDown(0,ImagePressButtonPfl2->picture.height() - 1);
  mPressButtonControlPfl3->OnMouseDown(0,ImagePressButtonPfl3->picture.height() - 1);
  //Out
  mPressButtonControlPfl1->OnMouseDown(0,ImagePressButtonPfl1->picture.height() - 1);
  mPressButtonControlPfl2->OnMouseDown(0,ImagePressButtonPfl2->picture.height() - 1);
  mPressButtonControlPfl3->OnMouseDown(0,ImagePressButtonPfl3->picture.height() - 1);
  //Set the gains to 0.0
  mDialControlGain1->OnMouseDown(5,17);
  mDialControlGain2->OnMouseDown(5,17);
  mDialControlGain3->OnMouseDown(5,17);
  mDialControlAux1_1->OnMouseDown(5,17);
  mDialControlAux1_2->OnMouseDown(5,17);
  mDialControlAux1_3->OnMouseDown(5,17);
  mDialControlSendAux1->OnMouseDown(5,17);
}
//---------------------------------------------------------------------------
void FormSimpleSound3::UpdateBuffer()
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
      DrawOnBuffer(LabelUse1);
      DrawOnBuffer(LabelUse2);
      DrawOnBuffer(LabelUse3);
      DrawOnBuffer(LabelUseGain);
      DrawOnBuffer(LabelUsePfl);
      DrawOnBuffer(LabelUseAux1_1);
      DrawOnBuffer(LabelUseAux1_2);
      DrawOnBuffer(LabelUseSend);
      DrawOnBuffer(LabelUseMaster);
      DrawOnBuffer(LabelUseSimpleSound3);
      //Controls
      DrawOnBuffer(ImageFader1);
      DrawOnBuffer(ImageFader2);
      DrawOnBuffer(ImageFader3);
      DrawOnBuffer(ImageFaderMaster);
      DrawOnBuffer(ImageDialGain1);
      DrawOnBuffer(ImageDialGain2);
      DrawOnBuffer(ImageDialGain3);
      DrawOnBuffer(ImageDialAux1_1);
      DrawOnBuffer(ImageDialAux1_2);
      DrawOnBuffer(ImageDialAux1_3);
      DrawOnBuffer(ImageDialSendAux1);
      DrawOnBuffer(ImagePressButtonPfl1);
      DrawOnBuffer(ImagePressButtonPfl2);
      DrawOnBuffer(ImagePressButtonPfl3);
      //Display
      DrawOnBuffer(ImageAudioSignal);
      break;
    case modeConnect:
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      //Labels
      DrawOnBuffer(LabelConnectMic1);
      DrawOnBuffer(LabelConnectMic2);
      DrawOnBuffer(LabelConnectMic3);
      DrawOnBuffer(LabelConnectAux1);
      DrawOnBuffer(LabelConnect1);
      DrawOnBuffer(LabelConnect2);
      DrawOnBuffer(LabelConnect3);
      DrawOnBuffer(LabelConnectMaster);
      DrawOnBuffer(LabelConnectL);
      DrawOnBuffer(LabelConnectR);
      DrawOnBuffer(LabelConnectPower);
      //Connectors
      DrawOnBuffer(ImageJackFemaleAux1);
      DrawOnBuffer(ImageXlrFemaleMic1);
      DrawOnBuffer(ImageXlrFemaleMic2);
      DrawOnBuffer(ImageXlrFemaleMic3);
      DrawOnBuffer(ImageXlrMaleMasterLeft);
      DrawOnBuffer(ImageXlrMaleMasterRight);
      DrawOnBuffer(ImageEuroMalePower);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void FormSimpleSound3::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      if (OnImage(x,y,ImageFader1))
      {
        mFaderControl1->OnMouseDown(
          x - ImageFader1->left,
          y - ImageFader1->top);
      }
      else if (OnImage(x,y,ImageFader2))
      {
        mFaderControl2->OnMouseDown(
          x - ImageFader2->left,
          y - ImageFader2->top);
      }
      else if (OnImage(x,y,ImageFader3))
      {
        mFaderControl3->OnMouseDown(
          x - ImageFader3->left,
          y - ImageFader3->top);
      }
      else if (OnImage(x,y,ImagePressButtonPfl1))
      {
        mPressButtonControlPfl1->OnMouseDown(
          x - ImagePressButtonPfl1->left,
          y - ImagePressButtonPfl1->top);
      }
      else if (OnImage(x,y,ImagePressButtonPfl2))
      {
        mPressButtonControlPfl2->OnMouseDown(
          x - ImagePressButtonPfl2->left,
          y - ImagePressButtonPfl2->top);
      }
      else if (OnImage(x,y,ImagePressButtonPfl3))
      {
        mPressButtonControlPfl3->OnMouseDown(
          x - ImagePressButtonPfl3->left,
          y - ImagePressButtonPfl3->top);
      }
      else if (OnImage(x,y,ImageDialGain1))
      {
        mDialControlGain1->OnMouseDown(
          x - ImageDialGain1->left,
          y - ImageDialGain1->top);
      }
      else if (OnImage(x,y,ImageDialGain2))
      {
        mDialControlGain2->OnMouseDown(
          x - ImageDialGain2->left,
          y - ImageDialGain2->top);
      }
      else if (OnImage(x,y,ImageDialGain3))
      {
        mDialControlGain3->OnMouseDown(
          x - ImageDialGain3->left,
          y - ImageDialGain3->top);
      }
      else if (OnImage(x,y,ImageDialAux1_1))
      {
        mDialControlAux1_1->OnMouseDown(
          x - ImageDialAux1_1->left,
          y - ImageDialAux1_1->top);
      }
      else if (OnImage(x,y,ImageDialAux1_2))
      {
        mDialControlAux1_2->OnMouseDown(
          x - ImageDialAux1_2->left,
          y - ImageDialAux1_2->top);
      }
      else if (OnImage(x,y,ImageDialAux1_3))
      {
        mDialControlAux1_3->OnMouseDown(
          x - ImageDialAux1_3->left,
          y - ImageDialAux1_3->top);
      }
      else if (OnImage(x,y,ImageDialSendAux1))
      {
        mDialControlSendAux1->OnMouseDown(
          x - ImageDialSendAux1->left,
          y - ImageDialSendAux1->top);
      }
      else if (OnImage(x,y,ImageFaderMaster))
      {
        mFaderControlMaster->OnMouseDown(
          x - ImageFaderMaster->left,
          y - ImageFaderMaster->top);
      }
      break;
    case modeConnect:
      if (OnImage(x,y,ImageJackFemaleAux1))
        mFormParent->OnConnectorClick(mJackFemaleAux1.get());
      if (OnImage(x,y,ImageXlrFemaleMic1))
        mFormParent->OnConnectorClick(mXlrFemaleMic1.get());
      if (OnImage(x,y,ImageXlrFemaleMic2))
        mFormParent->OnConnectorClick(mXlrFemaleMic2.get());
      if (OnImage(x,y,ImageXlrFemaleMic3))
        mFormParent->OnConnectorClick(mXlrFemaleMic3.get());
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
void FormSimpleSound3::OnAfterResize()
{
  //Use
  {
    const std::vector<std::vector<QRect> > v(GetRectsGrid(ClientRect(),10,8));
    //Resize bitmaps
    SetPictureHeight(ImageFader1,MergeRects(v[4][2],v[6][2]).height());
    SetPictureHeight(ImageFader2,MergeRects(v[4][3],v[6][3]).height());
    SetPictureHeight(ImageFader3,MergeRects(v[4][4],v[6][4]).height());
    SetPictureHeight(ImageFaderMaster,MergeRects(v[4][5],v[6][5]).height());
    //Place bitmaps
    //Labels
    PlaceInCenter(LabelUse1,v[0][2]);
    PlaceInCenter(LabelUse2,v[0][3]);
    PlaceInCenter(LabelUse3,v[0][4]);
    PlaceInCenter(LabelUseGain,MergeRects(v[1][0],v[1][1]));
    PlaceInCenter(LabelUseAux1_1,MergeRects(v[2][0],v[2][1]));
    PlaceInCenter(LabelUsePfl,MergeRects(v[3][0],v[3][1]));
    PlaceInCenter(LabelUseMaster,MergeRects(v[3][5],v[3][6]));
    PlaceInCenter(LabelUseSend,MergeRects(v[0][5],v[0][6]));
    PlaceInCenter(LabelUseAux1_2,MergeRects(v[1][5],v[1][6]));
    PlaceInCenter(LabelUseSimpleSound3,MergeRects(v[0][7],v[1][9]));
    //Controls
    //#1
    PlaceInCenter(ImageDialGain1,v[1][2]);
    PlaceInCenter(ImageDialAux1_1,v[2][2]);
    PlaceInCenter(ImagePressButtonPfl1,v[3][2]);
    PlaceInCenter(ImageFader1,MergeRects(v[4][2],v[6][2]));
    //#2
    PlaceInCenter(ImageDialGain2,v[1][3]);
    PlaceInCenter(ImageDialAux1_2,v[2][3]);
    PlaceInCenter(ImagePressButtonPfl2,v[3][3]);
    PlaceInCenter(ImageFader2,MergeRects(v[4][3],v[6][3]));
    //#3
    PlaceInCenter(ImageDialGain3,v[1][4]);
    PlaceInCenter(ImageDialAux1_3,v[2][4]);
    PlaceInCenter(ImagePressButtonPfl3,v[3][4]);
    PlaceInCenter(ImageFader3,MergeRects(v[4][4],v[6][4]));
    //Others
    PlaceInCenter(ImageDialSendAux1,MergeRects(v[2][5],v[2][6]));
    PlaceInCenter(ImageFaderMaster,MergeRects(v[4][5],v[6][6]));
    //Displays
    PlaceInCenter(ImageAudioSignal,MergeRects(v[2][7],v[7][9]));
  }
  //Connect
  {
    const std::vector<std::vector<QRect> > v(GetRectsGrid(ClientRect(),7,5));
    //Labels
    PlaceInCenter(LabelConnectMic1  ,v[1][0]);
    PlaceInCenter(LabelConnect1     ,v[2][0]);
    PlaceInCenter(LabelConnectMic2  ,v[1][1]);
    PlaceInCenter(LabelConnect2     ,v[2][1]);
    PlaceInCenter(LabelConnectMic3  ,v[1][2]);
    PlaceInCenter(LabelConnect3     ,v[2][2]);
    PlaceInCenter(LabelConnectAux1  ,v[2][3]);
    PlaceInCenter(LabelConnectMaster,MergeRects(v[1][4],v[1][5]));
    PlaceInCenter(LabelConnectL     ,v[2][4]);
    PlaceInCenter(LabelConnectR     ,v[2][5]);
    PlaceInCenter(LabelConnectPower ,v[2][6]);
    //Connectors
    PlaceInCenter(ImageXlrFemaleMic1     ,v[3][0]);
    PlaceInCenter(ImageXlrFemaleMic2     ,v[3][1]);
    PlaceInCenter(ImageXlrFemaleMic3     ,v[3][2]);
    PlaceInCenter(ImageJackFemaleAux1    ,v[3][3]);
    PlaceInCenter(ImageXlrMaleMasterLeft ,v[3][4]);
    PlaceInCenter(ImageXlrMaleMasterRight,v[3][5]);
    PlaceInCenter(ImageEuroMalePower     ,v[3][6]);
  }
}
//---------------------------------------------------------------------------






