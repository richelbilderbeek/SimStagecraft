//---------------------------------------------------------------------------

#ifndef UnitFormTransitionPieceJackMaleTwoCinchFemaleH
#define UnitFormTransitionPieceJackMaleTwoCinchFemaleH
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormTransitionPieceJackMaleTwoCinchFemale.h"
//Machine
struct TransitionPieceJackMaleTwoCinchFemale;
//Connect
struct CinchWhiteFemaleControl;
struct CinchRedFemaleControl;
struct JackMaleControl;
//Misc
class FormSimStagecraftMain;
//---------------------------------------------------------------------------
class FormTransitionPieceJackMaleTwoCinchFemale : public FormMachine, private UiFormTransitionPieceJackMaleTwoCinchFemale
{
private:	// User declarations
  //Machine
  std::shared_ptr<TransitionPieceJackMaleTwoCinchFemale> mTransitionPiece;
  //Control
  //Connect
  std::shared_ptr<CinchWhiteFemaleControl> mCinchL;
  std::shared_ptr<CinchRedFemaleControl> mCinchR;
  std::shared_ptr<JackMaleControl> mJack;
public:		// User declarations
  FormTransitionPieceJackMaleTwoCinchFemale(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void UpdateBuffer();
  void OnAfterResize();
  const Image * const GetImageBuffer() const;
};
//---------------------------------------------------------------------------
#endif
