//---------------------------------------------------------------------------

#ifndef UnitFormSimpleSound3H
#define UnitFormSimpleSound3H
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormSimpleSound3.h"
//Machine
struct SimpleSound3;
//Control
struct FaderControl;
struct DialControl;
struct PressButtonControl;
//Connect
struct EuroMaleControl;
struct XlrFemaleControl;
struct XlrMaleControl;
struct JackFemaleControl;
//Display
struct AudioSignalControl;
//---------------------------------------------------------------------------
class FormSimpleSound3 : public FormMachine, private UiFormSimpleSound3
{
private:	// User declarations
  //Machine
  std::shared_ptr<SimpleSound3> mSoundTable;
  //Control
  std::shared_ptr<FaderControl> mFaderControl1;
  std::shared_ptr<FaderControl> mFaderControl2;
  std::shared_ptr<FaderControl> mFaderControl3;
  std::shared_ptr<DialControl> mDialControlGain1;
  std::shared_ptr<DialControl> mDialControlGain2;
  std::shared_ptr<DialControl> mDialControlGain3;
  std::shared_ptr<DialControl> mDialControlAux1_1;
  std::shared_ptr<DialControl> mDialControlAux1_2;
  std::shared_ptr<DialControl> mDialControlAux1_3;
  std::shared_ptr<DialControl> mDialControlSendAux1;
  std::shared_ptr<PressButtonControl> mPressButtonControlPfl1;
  std::shared_ptr<PressButtonControl> mPressButtonControlPfl2;
  std::shared_ptr<PressButtonControl> mPressButtonControlPfl3;
  std::shared_ptr<FaderControl> mFaderControlMaster;
  //Connect
  std::shared_ptr<XlrFemaleControl> mXlrFemaleMic1;
  std::shared_ptr<XlrFemaleControl> mXlrFemaleMic2;
  std::shared_ptr<XlrFemaleControl> mXlrFemaleMic3;
  std::shared_ptr<JackFemaleControl> mJackFemaleAux1;
  std::shared_ptr<XlrMaleControl> mXlrMaleMasterLeft;
  std::shared_ptr<XlrMaleControl> mXlrMaleMasterRight;
  std::shared_ptr<EuroMaleControl> mEuroMalePower;
  //Display
  std::shared_ptr<AudioSignalControl> mAudioSignalDisplay;
public:		// User declarations
  FormSimpleSound3(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const Image * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
#endif
