//---------------------------------------------------------------------------

#ifndef UnitFormOctletH
#define UnitFormOctletH
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormOctlet.h"
//---------------------------------------------------------------------------
#include <vector>
#include "UnitFormMachine.h"
struct Octlet;
//struct ControllerControl;
struct ConnectorControl;
struct TwoSwitchControl;
struct Socket220Control;
struct Plug220Control;
class FormSimStagecraftMain;
//---------------------------------------------------------------------------
class FormOctlet : public FormMachine, private UiFormOctlet
{
private:	// User declarations
  //Machine
  std::shared_ptr<Octlet> mOctlet;
  //Control
  std::shared_ptr<TwoSwitchControl> mTwoSwitchPower;
  //Connect
  std::vector<std::shared_ptr<Socket220Control> > mSocket220Controls;
  std::shared_ptr<Plug220Control> mPlug220;
  //Misc
  std::vector<Image*> mImageSockets220;
  const std::vector<std::shared_ptr<Socket220Control> >
    CreateSocket220Controls();

public:		// User declarations
  FormOctlet(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void UpdateBuffer();
  void OnAfterResize();
  const Image * const GetImageBuffer() const;
};
//---------------------------------------------------------------------------
#endif
