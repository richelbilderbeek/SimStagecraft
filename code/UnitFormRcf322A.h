//---------------------------------------------------------------------------

#ifndef UnitFormRcf322AH
#define UnitFormRcf322AH
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormRcf322A.h"
//---------------------------------------------------------------------------
#include <vector>
#include "UnitFormMachine.h"
//Machine
struct Rcf322A;
//Control
struct TwoSwitchControl;
struct DialControl;
//Connect
struct XlrMaleControl;
struct XlrFemaleControl;
struct JackFemaleControl;
struct EuroMaleControl;
//Display
struct LedControl;
//---------------------------------------------------------------------------
class FormRcf322A : public FormMachine, private UiFormRcf322A
{
private:	// User declarations
  //Machine
  std::shared_ptr<Rcf322A> mSpeaker;
  //Control
  std::shared_ptr<TwoSwitchControl> mPowerSwitch;
  std::shared_ptr<DialControl> mVolumeDial;
  //Connect
  std::shared_ptr<EuroMaleControl> mEuroMale;
  std::shared_ptr<XlrMaleControl> mXlrMale;
  std::shared_ptr<XlrFemaleControl> mXlrFemale;
  std::shared_ptr<JackFemaleControl> mJackFemale;
  //Display
  std::shared_ptr<LedControl> mLedPower;
  std::shared_ptr<LedControl> mLedLimProt;
public:		// User declarations
  FormRcf322A(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const Image * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
#endif
