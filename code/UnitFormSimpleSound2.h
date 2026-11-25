//---------------------------------------------------------------------------

#ifndef UnitFormSimpleSound2H
#define UnitFormSimpleSound2H
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormSimpleSound2.h"
//Machine
struct SimpleSound2;
//Control
struct FaderControl;
struct DialControl;
struct PressButtonControl;
//Connect
struct EuroMaleControl;
struct XlrFemaleControl;
struct XlrMaleControl;
//Display
struct AudioSignalControl;
//---------------------------------------------------------------------------
class FormSimpleSound2 : public FormMachine, private UiFormSimpleSound2
{
private:	// User declarations
  //Machine
  std::shared_ptr<SimpleSound2> mSoundTable;
  //Control
  std::shared_ptr<FaderControl> mFaderControl1;
  std::shared_ptr<FaderControl> mFaderControl2;
  std::shared_ptr<DialControl> mDialControl1;
  std::shared_ptr<DialControl> mDialControl2;
  std::shared_ptr<PressButtonControl> mPressButtonControl1;
  std::shared_ptr<PressButtonControl> mPressButtonControl2;
  std::shared_ptr<FaderControl> mFaderControlMaster;
  //Connect
  std::shared_ptr<XlrFemaleControl> mXlrFemaleMic1;
  std::shared_ptr<XlrFemaleControl> mXlrFemaleMic2;
  std::shared_ptr<XlrMaleControl> mXlrMaleMasterLeft;
  std::shared_ptr<XlrMaleControl> mXlrMaleMasterRight;
  std::shared_ptr<EuroMaleControl> mEuroMalePower;
  //Display
  std::shared_ptr<AudioSignalControl> mAudioSignalDisplay;
public:		// User declarations
  FormSimpleSound2(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const Image * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
#endif
