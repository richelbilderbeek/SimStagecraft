//---------------------------------------------------------------------------

#ifndef UnitFormDimblockV3H
#define UnitFormDimblockV3H
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormDimblockV3.h"
//---------------------------------------------------------------------------
#include <vector>
#include "UnitFormMachine.h"
struct DimblockV3;
struct SocketPowerMaleControl;
struct DmxMaleControl;
struct DmxFemaleControl;
struct Socket220Control;
struct LedControl;
//---------------------------------------------------------------------------
class FormDimblockV3 : public FormMachine, private UiFormDimblockV3
{
private:	// User declarations
  //Machine
  std::shared_ptr<DimblockV3> mDimblockV3;
  //Control
  //Connect
  std::shared_ptr<DmxMaleControl> mDmxMaleInput;
  std::shared_ptr<DmxFemaleControl> mDmxFemaleThrough;
  std::shared_ptr<SocketPowerMaleControl> mSocketPowerMale;
  //Display
  std::shared_ptr<LedControl> mLedMainsPower;
  std::shared_ptr<LedControl> mLedNondimSet;
  std::shared_ptr<LedControl> mLedPresetSet;
  std::shared_ptr<LedControl> mLedDmxPresent;
  std::shared_ptr<LedControl> mLedWarning;
  //Other
  std::vector<std::shared_ptr<Socket220Control> > mSockets;
  std::vector<Image*> mImageSockets;
  const std::vector<std::shared_ptr<Socket220Control> >
    CreateSocket220Controls();
public:		// User declarations
  FormDimblockV3(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  void UpdateBuffer();
  const Image * const GetImageBuffer() const;
};
//---------------------------------------------------------------------------
#endif
