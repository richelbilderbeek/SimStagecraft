//---------------------------------------------------------------------------

#include <cassert>
#include <stdexcept>
#include "UnitControllerControl.h"
#include "UnitConnectorControl.h"
#include "UnitMachine.h"
#include "UnitTransitionPiece.h"
#include "UnitImage.h"
#include "UnitFormTransitionPieceJackMaleTwoCinchFemale.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
FormTransitionPieceJackMaleTwoCinchFemale::FormTransitionPieceJackMaleTwoCinchFemale(
    FormSimStagecraftMain * const formParent)
  : FormMachine(formParent,DesignClientWidth,DesignClientHeight),
    mTransitionPiece(std::shared_ptr<TransitionPieceJackMaleTwoCinchFemale>(
      new TransitionPieceJackMaleTwoCinchFemale))
{
  //Control
  //Connect
  mJack = std::shared_ptr<JackMaleControl>(
    new JackMaleControl(this,mTransitionPiece->mJack,ImageJack));
  mCinchL = std::shared_ptr<CinchWhiteFemaleControl>(
    new CinchWhiteFemaleControl(this,mTransitionPiece->mCinchL,ImageCinchL));
  mCinchR = std::shared_ptr<CinchRedFemaleControl>(
    new CinchRedFemaleControl(this,mTransitionPiece->mCinchR,ImageCinchR));

  CreateWatermark(ImageView,ImageWatermark);

  Resize();
}
//---------------------------------------------------------------------------
void FormTransitionPieceJackMaleTwoCinchFemale::UpdateBuffer()
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
      DrawOnBuffer(ImageJack);
      DrawOnBuffer(ImageCinchL);
      DrawOnBuffer(ImageCinchR);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void FormTransitionPieceJackMaleTwoCinchFemale::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      break;
    case modeConnect:
      if (OnImage(x,y,ImageJack)) mFormParent->OnConnectorClick(mJack.get());
      if (OnImage(x,y,ImageCinchL)) mFormParent->OnConnectorClick(mCinchL.get());
      if (OnImage(x,y,ImageCinchR)) mFormParent->OnConnectorClick(mCinchR.get());
      break;
  }
}
//---------------------------------------------------------------------------
void FormTransitionPieceJackMaleTwoCinchFemale::OnAfterResize()
{
  const std::vector<std::vector<QRect> > v(GetRectsGrid(ClientRect(),2,2));
  PlaceInCenter(ImageCinchL,v[0][0]);
  PlaceInCenter(ImageCinchR,v[1][0]);
  PlaceInCenter(ImageJack,  MergeRects(v[0][1],v[1][1]));
}
//---------------------------------------------------------------------------


