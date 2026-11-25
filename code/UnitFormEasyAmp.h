//---------------------------------------------------------------------------

#ifndef UnitFormEasyAmpH
#define UnitFormEasyAmpH
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormEasyAmp.h"
//---------------------------------------------------------------------------
#include <memory>
#include "UnitFormMachine.h"
#include "UnitTapButtonControl.h"
//Machine
struct EasyAmp;
//Control
struct TwoSwitchControl;
struct DialControl;
//Connect
struct EuroMaleControl;
struct JackXlrFemaleControl;
struct SpeakonFemaleControl;
//Display
struct LedControl;
//---------------------------------------------------------------------------
class FormEasyAmp : public FormMachine, private UiFormEasyAmp
{
private:	// User declarations
  //Machine
  std::shared_ptr<EasyAmp> mAmplifier;
  //Control
  std::shared_ptr<TwoSwitchControl> mPowerSwitch;
  std::shared_ptr<DialControl> mGain;
  //Connect
  std::shared_ptr<EuroMaleControl> mEuro;
  std::shared_ptr<JackXlrFemaleControl> mJackXlrL;
  std::shared_ptr<JackXlrFemaleControl> mJackXlrR;
  std::shared_ptr<SpeakonFemaleControl> mSpeakonL;
  std::shared_ptr<SpeakonFemaleControl> mSpeakonR;
  //Display
  std::shared_ptr<LedControl> mLedPower;

public:		// User declarations
  FormEasyAmp(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const Image * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
#endif
