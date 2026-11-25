//---------------------------------------------------------------------------

#ifndef UnitFormWallSocket220H
#define UnitFormWallSocket220H
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormWallSocket220.h"
struct WallSocket220;
struct Socket220Control;
//---------------------------------------------------------------------------
class FormWallSocket220 : public FormMachine, private UiFormWallSocket220
{
private:	// User declarations
  std::shared_ptr<Socket220Control> mSocket220Control;
  std::shared_ptr<WallSocket220> mSocket220;
public:		// User declarations
  FormWallSocket220(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
#endif
