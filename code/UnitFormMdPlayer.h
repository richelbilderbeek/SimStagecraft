//---------------------------------------------------------------------------

#ifndef UnitFormMdPlayerH
#define UnitFormMdPlayerH
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormMdPlayer.h"
#include "UnitTapButtonControl.h"
//Machine
struct MdPlayer;
//Control
//TapButton has already been #included
//Connect
struct CinchRedFemaleControl;
struct CinchWhiteFemaleControl;
struct Plug220Control;
//Display
struct AudioSignalControl;
struct LcdSymbolPlayControl;
struct LcdSymbolRecControl;
struct LedControl;
//---------------------------------------------------------------------------
class FormMdPlayer : public FormMachine, private UiFormMdPlayer
{
private:	// User declarations
  //Machine
  std::shared_ptr<MdPlayer> mMdPlayer;
  //Control
  std::shared_ptr<TapButtonControl<MdPlayer> > mTapButtonPlay;
  std::shared_ptr<TapButtonControl<MdPlayer> > mTapButtonRecord;
  std::shared_ptr<TapButtonControl<MdPlayer> > mTapButtonStop;
  std::shared_ptr<TapButtonControl<MdPlayer> > mTapButtonPower;
  //Connect
  std::shared_ptr<CinchWhiteFemaleControl> mCinchFemaleInL;
  std::shared_ptr<CinchRedFemaleControl> mCinchFemaleInR;
  std::shared_ptr<CinchWhiteFemaleControl> mCinchFemaleOutL;
  std::shared_ptr<CinchRedFemaleControl> mCinchFemaleOutR;
  std::shared_ptr<Plug220Control> mPlug220Power;
  //Display
  std::shared_ptr<AudioSignalControl> mAudioSignalDisplayL;
  std::shared_ptr<AudioSignalControl> mAudioSignalDisplayR;
  std::shared_ptr<LcdSymbolRecControl> mLcdSymbolRec;
  std::shared_ptr<LcdSymbolPlayControl> mLcdSymbolPlay;
  std::shared_ptr<LedControl> mLedPower;

public:		// User declarations
  FormMdPlayer(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const Image * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
#endif
