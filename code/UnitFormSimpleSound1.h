//---------------------------------------------------------------------------

#ifndef UnitFormSimpleSound1H
#define UnitFormSimpleSound1H
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormSimpleSound1.h"
//Machine
struct SimpleSound1;
//Control
struct FaderControl;
//Connect
struct EuroMaleControl;
struct XlrFemaleControl;
struct XlrMaleControl;
//Display
struct AudioSignalControl;
//---------------------------------------------------------------------------
class FormSimpleSound1 : public FormMachine, private UiFormSimpleSound1
{
private:	// User declarations
  //Machine
  std::shared_ptr<SimpleSound1> mSoundTable;
  //Control
  std::shared_ptr<FaderControl> mFaderControlMaster;
  //Connect
  std::shared_ptr<XlrFemaleControl> mXlrFemaleMic1;
  std::shared_ptr<XlrMaleControl> mXlrMaleMasterLeft;
  std::shared_ptr<XlrMaleControl> mXlrMaleMasterRight;
  std::shared_ptr<EuroMaleControl> mEuroMalePower;
  //Display
  std::shared_ptr<AudioSignalControl> mAudioSignalDisplay;
public:		// User declarations
  FormSimpleSound1(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const Image * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
#endif
