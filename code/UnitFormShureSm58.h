//---------------------------------------------------------------------------

#ifndef UnitFormShureSm58H
#define UnitFormShureSm58H
//---------------------------------------------------------------------------
#include "UnitFormMachine.h"
#include "ui/UiFormShureSm58.h"
struct ShureSm58;
struct XlrMaleControl;
//---------------------------------------------------------------------------
class FormShureSm58 : public FormMachine, private UiFormShureSm58
{
private:
  void TimerSingTimer();	// User declarations
  std::shared_ptr<ShureSm58> mMicrophone;
  std::shared_ptr<XlrMaleControl> mXlrMale;
  bool mSinging;
  const double mSingerAverage;
public:		// User declarations
  FormShureSm58(FormSimStagecraftMain * const formParent);
  void OnMouseDown(const int x, const int y);
  void OnAfterResize();
  const Image * const GetImageBuffer() const;
  void UpdateBuffer();
};
//---------------------------------------------------------------------------
#endif
