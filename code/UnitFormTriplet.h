//---------------------------------------------------------------------------

#ifndef UnitFormTripletH
#define UnitFormTripletH
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormTriplet.h"
struct Triplet;
//struct ControllerControl;
struct ConnectorControl;
struct TwoSwitchControl;
struct Socket220Control;
struct Plug220Control;
class FormSimStagecraftMain;
//---------------------------------------------------------------------------
class FormTriplet : public FormMachine, private UiFormTriplet
{
private:	// User declarations
  //Machine
  std::shared_ptr<Triplet> mTriplet;
  //Control
  //Connect
  std::shared_ptr<Socket220Control> mSocket220_1;
  std::shared_ptr<Socket220Control> mSocket220_2;
  std::shared_ptr<Socket220Control> mSocket220_3;
  std::shared_ptr<Plug220Control> mPlug220;
public:		// User declarations
  FormTriplet(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void UpdateBuffer();
  void OnAfterResize();
  const Image * const GetImageBuffer() const;
};
//---------------------------------------------------------------------------
#endif
