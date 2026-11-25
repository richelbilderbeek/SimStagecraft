//---------------------------------------------------------------------------

#ifndef UnitFormSimpleSound4H
#define UnitFormSimpleSound4H
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormSimpleSound4.h"
//Machine
struct SimpleSound4;
//Control
struct FaderControl;
struct DialControl;
struct PressButtonControl;
//Connect
struct CinchRedFemaleControl;
struct CinchWhiteFemaleControl;
struct EuroMaleControl;
struct JackFemaleControl;
struct XlrFemaleControl;
struct XlrMaleControl;
//Display
struct AudioSignalControl;
//---------------------------------------------------------------------------
class FormSimpleSound4 : public FormMachine, private UiFormSimpleSound4
{
private:	// User declarations
  //Machine
  std::shared_ptr<SimpleSound4> mSoundTable;
  //Control
  std::shared_ptr<FaderControl> mFaderControl1;
  std::shared_ptr<FaderControl> mFaderControl2;
  std::shared_ptr<FaderControl> mFaderControl3;
  std::shared_ptr<FaderControl> mFaderControl4;
  std::shared_ptr<DialControl> mDialControlGain1;
  std::shared_ptr<DialControl> mDialControlGain2;
  std::shared_ptr<DialControl> mDialControlGain3;
  std::shared_ptr<DialControl> mDialControlAux1_1;
  std::shared_ptr<DialControl> mDialControlAux1_2;
  std::shared_ptr<DialControl> mDialControlAux1_3;
  std::shared_ptr<DialControl> mDialControlAux1_4;
  std::shared_ptr<DialControl> mDialControlAux2_1;
  std::shared_ptr<DialControl> mDialControlAux2_2;
  std::shared_ptr<DialControl> mDialControlAux2_3;
  std::shared_ptr<DialControl> mDialControlAux2_4;
  std::shared_ptr<DialControl> mDialControlSendAux1;
  std::shared_ptr<DialControl> mDialControlSendAux2;
  std::shared_ptr<PressButtonControl> mPressButtonControlPfl1;
  std::shared_ptr<PressButtonControl> mPressButtonControlPfl2;
  std::shared_ptr<PressButtonControl> mPressButtonControlPfl3;
  std::shared_ptr<PressButtonControl> mPressButtonControlPfl4;
  std::shared_ptr<FaderControl> mFaderControlMaster;
  //Connect
  std::shared_ptr<XlrFemaleControl> mXlrFemaleMic1;
  std::shared_ptr<XlrFemaleControl> mXlrFemaleMic2;
  std::shared_ptr<XlrFemaleControl> mXlrFemaleMic3;
  std::shared_ptr<CinchWhiteFemaleControl> mCinchFemaleL4;
  std::shared_ptr<CinchRedFemaleControl> mCinchFemaleR4;
  std::shared_ptr<JackFemaleControl> mJackFemaleAux1;
  std::shared_ptr<JackFemaleControl> mJackFemaleAux2;
  std::shared_ptr<XlrMaleControl> mXlrMaleMasterLeft;
  std::shared_ptr<XlrMaleControl> mXlrMaleMasterRight;
  std::shared_ptr<EuroMaleControl> mEuroMalePower;
  //Display
  std::shared_ptr<AudioSignalControl> mAudioSignalDisplay;
public:		// User declarations
  FormSimpleSound4(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const Image * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
#endif
