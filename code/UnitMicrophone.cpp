//---------------------------------------------------------------------------

#include <cassert>
#include "UnitConnector.h"
#include "UnitMicrophone.h"
//---------------------------------------------------------------------------
ShureSm58::ShureSm58()
  : mXlrInput(std::shared_ptr<XlrMale>(new XlrMale(this))),
    mAudioSignalStrength(0.0)
{
  assert(mXlrInput.get() != 0);
}
//---------------------------------------------------------------------------
const double ShureSm58::AudioSignalStrength(const Connector * const connector,
  std::vector<const Connector*> /* prevConnectors */) const
{
  assert(connector == mXlrInput.get() );
  return mAudioSignalStrength;
}
//---------------------------------------------------------------------------
const bool ShureSm58::HasPower() const
{
  assert("This is not a very important method");
  return true;
}
//---------------------------------------------------------------------------
void ShureSm58::SetAudioSignalStrength(const double audioSignalStrength)
{
  mAudioSignalStrength = audioSignalStrength;
}
//---------------------------------------------------------------------------
