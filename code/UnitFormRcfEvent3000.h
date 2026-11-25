//---------------------------------------------------------------------------

#ifndef UnitFormRcfEvent3000H
#define UnitFormRcfEvent3000H
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormRcfEvent3000.h"
//---------------------------------------------------------------------------
#include <vector>
#include "UnitFormMachine.h"
//Machine
struct RcfEvent3000;
//Control
//Connect
struct SpeakonFemaleControl;
//Display
struct AudioSignalControl;
//---------------------------------------------------------------------------
class FormRcfEvent3000 : public FormMachine, private UiFormRcfEvent3000
{
private:	// User declarations
  //Machine
  std::shared_ptr<RcfEvent3000> mSpeaker;
  //Control
  //Connect
  std::shared_ptr<SpeakonFemaleControl> mInput;
  std::shared_ptr<SpeakonFemaleControl> mLink;
  //Display
  //RCF Event 3000 does not use the DisplayControl
  //because it is not an actual physical electrical display 
  //std::shared_ptr<AudioSignalControl> mDisplay;
public:		// User declarations
  FormRcfEvent3000(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const Image * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
#endif
