//---------------------------------------------------------------------------

#ifndef UnitTapButtonH
#define UnitTapButtonH
//---------------------------------------------------------------------------
#include "UnitController.h"
#include "UnitMemFunCommand.h"
//---------------------------------------------------------------------------
template <class T>
struct TapButton : public Controller
{
  typedef void (T::* MemFunPtr)();

  TapButton(T * const target, const MemFunPtr command)
  : mCommand(target,command)
  {

  }


  void Tap()
  {
    mCommand.Execute();
  }

  private:

  const MemFunCommand<T> mCommand;

  public:
  virtual ~TapButton() {}
  private:

};
//---------------------------------------------------------------------------



#endif
