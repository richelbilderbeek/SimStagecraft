//---------------------------------------------------------------------------

#ifndef UnitFormSimpleShine2H
#define UnitFormSimpleShine2H
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormSimpleShine2.h"
//---------------------------------------------------------------------------
#include <vector>
#include <memory>
#include "UnitFormMachine.h"
struct SimpleShine2;
struct FaderControl;
struct SimpleShine1;
struct DmxFemaleControl;
struct EuroMaleControl;
//---------------------------------------------------------------------------
class FormSimpleShine2 : public FormMachine, private UiFormSimpleShine2
{
private:	// User declarations
  //Machine
  std::shared_ptr<SimpleShine2> mSimpleShine2;
  //Control
  const std::vector<Image*> mImageFaders;
  const std::vector<Image*> mLabels;
  const std::vector<Image*> GetImageFaders() const;
  const std::vector<Image*> GetLabels() const;
  std::vector<std::shared_ptr<FaderControl> > mChannelFaders;
  std::shared_ptr<FaderControl> mCrossfaderA;
  std::shared_ptr<FaderControl> mCrossfaderB;
  std::shared_ptr<FaderControl> mMasterFader;
  //Connect
  std::shared_ptr<DmxFemaleControl> mDmxFemaleOut;
  std::shared_ptr<EuroMaleControl> mEuroMalePower;
  //Display
  std::shared_ptr<LedControl> mLedPower;
  std::shared_ptr<LedControl> mLedA;
  std::shared_ptr<LedControl> mLedB;
public:		// User declarations
  FormSimpleShine2(FormSimStagecraftMain * const formParent);
  const Image * const GetImageBuffer() const;
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  void UpdateBuffer();

};
//---------------------------------------------------------------------------
#endif
