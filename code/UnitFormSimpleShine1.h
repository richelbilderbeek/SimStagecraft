//---------------------------------------------------------------------------

#ifndef UnitFormSimpleShine1H
#define UnitFormSimpleShine1H
//---------------------------------------------------------------------------
//#include "UnitEnumMachineType.h"
#include "UnitFormMachine.h"
#include "ui/UiFormSimpleShine1.h"
struct FaderControl;
struct SimpleShine1;
struct DmxFemaleControl;
struct EuroMaleControl;
//---------------------------------------------------------------------------
class FormSimpleShine1 : public FormMachine, private UiFormSimpleShine1
{
private:	// User declarations
  //Machine
  std::shared_ptr<SimpleShine1> mSimpleShine1;
  //Control
  std::shared_ptr<FaderControl> mFaderControl1;
  std::shared_ptr<FaderControl> mFaderControl2;
  std::shared_ptr<FaderControl> mFaderControl3;
  std::shared_ptr<FaderControl> mFaderControl4;
  std::shared_ptr<FaderControl> mFaderControl5;
  std::shared_ptr<FaderControl> mFaderControl6;
  std::shared_ptr<FaderControl> mFaderControl7;
  std::shared_ptr<FaderControl> mFaderControl8;
  std::shared_ptr<FaderControl> mFaderControl9;
  std::shared_ptr<FaderControl> mFaderControl10;
  std::shared_ptr<FaderControl> mFaderControl11;
  std::shared_ptr<FaderControl> mFaderControl12;
  std::shared_ptr<FaderControl> mFaderControlMaster;
  //Connect
  std::shared_ptr<DmxFemaleControl> mDmxFemaleOut;
  std::shared_ptr<EuroMaleControl> mEuroMalePower;
  //Display
  std::shared_ptr<LedControl> mLedControlPower;
public:		// User declarations
  FormSimpleShine1(FormSimStagecraftMain * const formParent);
  const Image * const GetImageBuffer() const;
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  void UpdateBuffer();

};
//---------------------------------------------------------------------------
#endif
