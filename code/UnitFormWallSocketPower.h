//---------------------------------------------------------------------------

#ifndef UnitFormWallSocketPowerH
#define UnitFormWallSocketPowerH
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormWallSocketPower.h"
struct WallSocketPower;
struct SocketPowerFemaleControl;
//---------------------------------------------------------------------------
class FormWallSocketPower : public FormMachine, private UiFormWallSocketPower
{
private:	// User declarations
  std::shared_ptr<SocketPowerFemaleControl> mSocketPowerControl;
  std::shared_ptr<WallSocketPower> mSocketPower;
public:		// User declarations
  FormWallSocketPower(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();

  const Image * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
#endif
