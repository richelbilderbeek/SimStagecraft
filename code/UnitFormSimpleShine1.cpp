//---------------------------------------------------------------------------

#include <cassert>
#include "UnitConnectorControl.h"
#include "UnitControllerControl.h"
#include "UnitDisplayControl.h"
#include "UnitLightTable.h"
#include "UnitFormSimpleShine1.h"
#include "UnitImage.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
FormSimpleShine1::FormSimpleShine1(FormSimStagecraftMain * const formParent)
  : FormMachine(formParent,DesignClientWidth,DesignClientHeight),
  mSimpleShine1(std::shared_ptr<SimpleShine1>(new SimpleShine1))
{
  //Control
  mFaderControl1 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine1->mFaders[0],ImageFader1));
  mFaderControl2 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine1->mFaders[1],ImageFader2));
  mFaderControl3 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine1->mFaders[2],ImageFader3));
  mFaderControl4 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine1->mFaders[3],ImageFader4));
  mFaderControl5 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine1->mFaders[4],ImageFader5));
  mFaderControl6 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine1->mFaders[5],ImageFader6));
  mFaderControl7 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine1->mFaders[6],ImageFader7));
  mFaderControl8 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine1->mFaders[7],ImageFader8));
  mFaderControl9 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine1->mFaders[8],ImageFader9));
  mFaderControl10 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine1->mFaders[9],ImageFader10));
  mFaderControl11 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine1->mFaders[10],ImageFader11));
  mFaderControl12 = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine1->mFaders[11],ImageFader12));
  mFaderControlMaster = std::shared_ptr<FaderControl>(
    new FaderControl(this,mSimpleShine1->mFaderMaster,ImageFaderMaster));
  //Connect
  mDmxFemaleOut = std::shared_ptr<DmxFemaleControl>(
    new DmxFemaleControl(this,mSimpleShine1->mDmxFemaleOut,ImageDmxFemaleOut));
  mEuroMalePower = std::shared_ptr<EuroMaleControl>(
    new EuroMaleControl(this,mSimpleShine1->mEuroMalePower,ImageEuroMalePower));
  //Display
  mLedControlPower = std::shared_ptr<LedControl>(new LedControl(
    mSimpleShine1->mLedPower,ImageLedPower));


  CreateWatermark(ImageView,ImageWatermark);
  Resize();

  //Manually set the faders
  mFaderControl1->OnMouseDown(0,ImageFader1->height - 1);
  mFaderControl2->OnMouseDown(0,ImageFader2->height - 1);
  mFaderControl3->OnMouseDown(0,ImageFader3->height - 1);
  mFaderControl4->OnMouseDown(0,ImageFader4->height - 1);
  mFaderControl5->OnMouseDown(0,ImageFader5->height - 1);
  mFaderControl6->OnMouseDown(0,ImageFader6->height - 1);
  mFaderControl7->OnMouseDown(0,ImageFader7->height - 1);
  mFaderControl8->OnMouseDown(0,ImageFader8->height - 1);
  mFaderControl9->OnMouseDown(0,ImageFader9->height - 1);
  mFaderControl10->OnMouseDown(0,ImageFader10->height - 1);
  mFaderControl11->OnMouseDown(0,ImageFader11->height - 1);
  mFaderControl12->OnMouseDown(0,ImageFader12->height - 1);
  mFaderControlMaster->OnMouseDown(0,ImageFaderMaster->height - 1);
}
//---------------------------------------------------------------------------
void FormSimpleShine1::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      DrawImage(ImageBuffer,0,0,ImageView);
      break;
    case modeUse:
      //Update displays
      mLedControlPower->Update();
      //Start drawing
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      //Labels
      DrawOnBuffer(LabelUse1);
      DrawOnBuffer(LabelUse2);
      DrawOnBuffer(LabelUse3);
      DrawOnBuffer(LabelUse4);
      DrawOnBuffer(LabelUse5);
      DrawOnBuffer(LabelUse6);
      DrawOnBuffer(LabelUse7);
      DrawOnBuffer(LabelUse8);
      DrawOnBuffer(LabelUse9);
      DrawOnBuffer(LabelUse10);
      DrawOnBuffer(LabelUse11);
      DrawOnBuffer(LabelUse12);
      DrawOnBuffer(LabelUseMaster);
      DrawOnBuffer(LabelUseSimpleShine1);
      //Controllers
      DrawOnBuffer(ImageFader1);
      DrawOnBuffer(ImageFader2);
      DrawOnBuffer(ImageFader3);
      DrawOnBuffer(ImageFader4);
      DrawOnBuffer(ImageFader5);
      DrawOnBuffer(ImageFader6);
      DrawOnBuffer(ImageFader7);
      DrawOnBuffer(ImageFader8);
      DrawOnBuffer(ImageFader9);
      DrawOnBuffer(ImageFader10);
      DrawOnBuffer(ImageFader11);
      DrawOnBuffer(ImageFader12);
      DrawOnBuffer(ImageFaderMaster);
      //Displays
      DrawOnBuffer(ImageLedPower);
      break;
    case modeConnect:
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      //Labels
      DrawOnBuffer(LabelConnectPower);
      DrawOnBuffer(LabelConnectDmxOut);
      //Connects
      DrawOnBuffer(ImageEuroMalePower);
      DrawOnBuffer(ImageDmxFemaleOut);
      break;
    default: assert(!"Should not get here");
  }
  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void FormSimpleShine1::OnMouseDown(const int x, const int y)
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
          x - ImageFader1->left,
          y - ImageFader1->top);
      }
      else if (OnImage(x,y,ImageFader3))
      {
        mFaderControl3->OnMouseDown(
          x - ImageFader1->left,
          y - ImageFader1->top);
      }
      else if (OnImage(x,y,ImageFader4))
      {
        mFaderControl4->OnMouseDown(
          x - ImageFader1->left,
          y - ImageFader1->top);
      }
      else if (OnImage(x,y,ImageFader5))
      {
        mFaderControl5->OnMouseDown(
          x - ImageFader1->left,
          y - ImageFader1->top);
      }
      else if (OnImage(x,y,ImageFader6))
      {
        mFaderControl6->OnMouseDown(
          x - ImageFader1->left,
          y - ImageFader1->top);
      }
      else if (OnImage(x,y,ImageFader7))
      {
        mFaderControl7->OnMouseDown(
          x - ImageFader1->left,
          y - ImageFader1->top);
      }
      else if (OnImage(x,y,ImageFader8))
      {
        mFaderControl8->OnMouseDown(
          x - ImageFader1->left,
          y - ImageFader1->top);
      }
      else if (OnImage(x,y,ImageFader9))
      {
        mFaderControl9->OnMouseDown(
          x - ImageFader1->left,
          y - ImageFader1->top);
      }
      else if (OnImage(x,y,ImageFader10))
      {
        mFaderControl10->OnMouseDown(
          x - ImageFader1->left,
          y - ImageFader1->top);
      }
      else if (OnImage(x,y,ImageFader11))
      {
        mFaderControl11->OnMouseDown(
          x - ImageFader1->left,
          y - ImageFader1->top);
      }
      else if (OnImage(x,y,ImageFader12))
      {
        mFaderControl12->OnMouseDown(
          x - ImageFader1->left,
          y - ImageFader1->top);
      }
      else if (OnImage(x,y,ImageFaderMaster))
      {
        mFaderControlMaster->OnMouseDown(
          x - ImageFaderMaster->left,
          y - ImageFaderMaster->top);
      }

      break;
    case modeConnect:
      if (OnImage(x,y,ImageEuroMalePower))
        mFormParent->OnConnectorClick(mEuroMalePower.get());
      if (OnImage(x,y,ImageDmxFemaleOut))
        mFormParent->OnConnectorClick(mDmxFemaleOut.get());
      break;
    default: assert(!"Should not get here");
  }
}
//---------------------------------------------------------------------------
void FormSimpleShine1::OnAfterResize()
{
  //Use
  {
    const std::vector<std::vector<QRect> > v(GetRectsGrid(ClientRect(),14,7));
    //Resize bitmaps
    SetPictureHeight(ImageFader1,MergeRects(v[3][0],v[5][0]).height());
    SetPictureHeight(ImageFader2,MergeRects(v[3][1],v[5][1]).height());
    SetPictureHeight(ImageFader3,MergeRects(v[3][2],v[5][2]).height());
    SetPictureHeight(ImageFader4,MergeRects(v[3][3],v[5][3]).height());
    SetPictureHeight(ImageFader5,MergeRects(v[3][4],v[5][4]).height());
    SetPictureHeight(ImageFader6,MergeRects(v[3][5],v[5][5]).height());
    SetPictureHeight(ImageFader7,MergeRects(v[3][6],v[5][6]).height());
    SetPictureHeight(ImageFader8,MergeRects(v[3][7],v[5][7]).height());
    SetPictureHeight(ImageFader9,MergeRects(v[3][8],v[5][8]).height());
    SetPictureHeight(ImageFader10,MergeRects(v[3][9],v[5][9]).height());
    SetPictureHeight(ImageFader11,MergeRects(v[3][10],v[5][10]).height());
    SetPictureHeight(ImageFader12,MergeRects(v[3][11],v[5][11]).height());
    SetPictureHeight(ImageFaderMaster,MergeRects(v[3][12],v[5][13]).height());
    //Place bitmaps
    //Labels
    PlaceInCenter(LabelUse1,v[2][0]);
    PlaceInCenter(LabelUse2,v[2][1]);
    PlaceInCenter(LabelUse3,v[2][2]);
    PlaceInCenter(LabelUse4,v[2][3]);
    PlaceInCenter(LabelUse5,v[2][4]);
    PlaceInCenter(LabelUse6,v[2][5]);
    PlaceInCenter(LabelUse7,v[2][6]);
    PlaceInCenter(LabelUse8,v[2][7]);
    PlaceInCenter(LabelUse9,v[2][8]);
    PlaceInCenter(LabelUse10,v[2][9]);
    PlaceInCenter(LabelUse11,v[2][10]);
    PlaceInCenter(LabelUse12,v[2][11]);
    PlaceInCenter(LabelUseMaster,MergeRects(v[2][12],v[2][13]));
    PlaceInCenter(LabelUseSimpleShine1,MergeRects(v[0][10],v[1][13]));
    //Controls
    PlaceInCenter(ImageFader1,MergeRects(v[3][0],v[5][0]));
    PlaceInCenter(ImageFader2,MergeRects(v[3][1],v[5][1]));
    PlaceInCenter(ImageFader3,MergeRects(v[3][2],v[5][2]));
    PlaceInCenter(ImageFader4,MergeRects(v[3][3],v[5][3]));
    PlaceInCenter(ImageFader5,MergeRects(v[3][4],v[5][4]));
    PlaceInCenter(ImageFader6,MergeRects(v[3][5],v[5][5]));
    PlaceInCenter(ImageFader7,MergeRects(v[3][6],v[5][6]));
    PlaceInCenter(ImageFader8,MergeRects(v[3][7],v[5][7]));
    PlaceInCenter(ImageFader9,MergeRects(v[3][8],v[5][8]));
    PlaceInCenter(ImageFader10,MergeRects(v[3][9],v[5][9]));
    PlaceInCenter(ImageFader11,MergeRects(v[3][10],v[5][10]));
    PlaceInCenter(ImageFader12,MergeRects(v[3][11],v[5][11]));
    PlaceInCenter(ImageFaderMaster,MergeRects(v[3][12],v[5][13]));
    //Displays
    PlaceInCenter(ImageLedPower,MergeRects(v[0][5],v[1][6]));
  }
  //Connect
  {
    const std::vector<std::vector<QRect> > v(GetRectsGrid(ClientRect(),2,2));
    //Labels
    PlaceInCenter(LabelConnectPower ,v[0][0]);
    PlaceInCenter(LabelConnectDmxOut,v[0][1]);
    //Connectors
    PlaceInCenter(ImageEuroMalePower,v[1][0]);
    PlaceInCenter(ImageDmxFemaleOut ,v[1][1]);
  }
}
//---------------------------------------------------------------------------


