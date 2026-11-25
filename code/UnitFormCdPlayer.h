//---------------------------------------------------------------------------

#ifndef UnitFormCdPlayerH
#define UnitFormCdPlayerH
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormCdPlayer.h"
#include "UnitTapButtonControl.h"
//Machine
struct CdPlayer;
//Control
//TapButton has already been #included
//Connect
struct CinchRedFemaleControl;
struct CinchWhiteFemaleControl;
struct ConnectorControl;
struct Plug220Control;
//Display
struct AudioSignalControl;
struct LcdSymbolPlayControl;
struct LcdSymbolRecControl;
struct LedControl;
//---------------------------------------------------------------------------
class FormCdPlayer : public FormMachine, private UiFormCdPlayer
{
private:
  void TimerTickTimer();	// User declarations
  //Machine
  std::shared_ptr<CdPlayer> mCdPlayer;
  //Control
  std::shared_ptr<TapButtonControl<CdPlayer> > mTapButtonPlay;
  std::shared_ptr<TapButtonControl<CdPlayer> > mTapButtonStop;
  std::shared_ptr<TapButtonControl<CdPlayer> > mTapButtonPower;
  //Connect
  std::shared_ptr<CinchWhiteFemaleControl> mCinchFemaleOutL;
  std::shared_ptr<CinchRedFemaleControl> mCinchFemaleOutR;
  std::shared_ptr<Plug220Control> mPlug220Power;
  //Display
  std::shared_ptr<AudioSignalControl> mAudioSignalDisplayL;
  std::shared_ptr<AudioSignalControl> mAudioSignalDisplayR;
  std::shared_ptr<LcdSymbolPlayControl> mLcdSymbolPlay;
  std::shared_ptr<LedControl> mLedPower;

public:		// User declarations
  FormCdPlayer(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const Image * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
#endif
