//---------------------------------------------------------------------------

#ifndef UnitMemFunCommandH
#define UnitMemFunCommandH
//---------------------------------------------------------------------------
#include <memory>
//---------------------------------------------------------------------------
// From http://www.richelbilderbeek.nl/CppCommandDesignPattern.htm
//---------------------------------------------------------------------------
template <class T>
struct MemFunCommand
{
  typedef void (T::* MemFunPtr)();

  MemFunCommand(T * const target, const MemFunPtr memFun)
    : mTarget(target), mFunction(memFun) { }
  void Execute() const { (mTarget->*mFunction)(); }
  private:
  T * mTarget;
  MemFunPtr mFunction;
};
//---------------------------------------------------------------------------
#endif
