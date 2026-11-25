//---------------------------------------------------------------------------

#ifndef UnitFormPar64H
#define UnitFormPar64H
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormPar64.h"
struct Par64;
struct Plug220Control;
class FormSimStagecraftMain;
//---------------------------------------------------------------------------
class FormPar64 : public FormMachine, private UiFormPar64
{
private:	// User declarations
  //Machine
  std::shared_ptr<Par64> mPar64;
  //Control
  //Connect
  std::shared_ptr<Plug220Control> mPlug220;
public:		// User declarations
  FormPar64(FormSimStagecraftMain * const formParent);
  const Image * const GetImageBuffer() const;
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
#endif
