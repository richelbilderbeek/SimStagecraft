//---------------------------------------------------------------------------

#include <cassert>
#include "UnitController.h" //For Fader, etc..
#include "UnitConnector.h"
#include "UnitDisplay.h"
#include "UnitLightTable.h"
//---------------------------------------------------------------------------
SimpleShine1::SimpleShine1()
  : mFaders(this->CreateFaders(12)),
    mFaderMaster(std::shared_ptr<Fader>(new Fader)),
    mEuroMalePower(std::shared_ptr<EuroMale>(new EuroMale(this))),
    mDmxFemaleOut(std::shared_ptr<DmxFemale>(new DmxFemale(this))),
    mConnectionLedPower(std::shared_ptr<InternalConnection>(
      new InternalConnection(this)))

{
  //Display
  mLedPower = std::shared_ptr<Led>(
    new Led(mConnectionLedPower.get(),255,0,0));

}
//---------------------------------------------------------------------------
//The DMX signal this machine can supply for a certain
//DMX channel. 0.0 = none, 1.0 = 100% (or FF).
const double SimpleShine1::DmxSignalStrength(const int dmxChannel) const
{
  if (this->HasPower() == false) return 0.0;
  if (dmxChannel >= 1 && dmxChannel <= 12) //Human based counting
  {
    return this->mFaderMaster->GetRelPosition()
      * this->mFaders[dmxChannel-1]->GetRelPosition();
  }
  return 0.001; //Small leaking current for DMX detection
}
//---------------------------------------------------------------------------
const double SimpleShine1::PowerSupplyStrength(const Connector * const connector,
  std::vector<const Connector*> /* prevConnectors */) const
{
  if (connector == mConnectionLedPower.get())
  {
    return (this->HasPower() == true ? 1.0 : 0.0);
  }
  return 0.0;
}
//---------------------------------------------------------------------------
//Does the machine have access to power? Does NOT mean the machine is ON!
const bool SimpleShine1::HasPower() const
{
  const Connector * const connectedTo = this->mEuroMalePower->GetConnectedTo();
  if (connectedTo == 0) return false;
  const Machine * const otherMachine = connectedTo->mBelongsTo;
  assert(otherMachine != 0);
  return (otherMachine->PowerSupplyStrength(
    connectedTo,std::vector<const Connector*>()) > 0.0 ? true : false);
}
//---------------------------------------------------------------------------
SimpleShine2::SimpleShine2()
  : mFaders(this->CreateFaders(24)),
    mCrossfaderA(std::shared_ptr<Fader>(new Fader)),
    mCrossfaderB(std::shared_ptr<Fader>(new Fader)),
    mFaderMaster(std::shared_ptr<Fader>(new Fader)),
    mEuroMalePower(std::shared_ptr<EuroMale>(new EuroMale(this))),
    mDmxFemaleOut(std::shared_ptr<DmxFemale>(new DmxFemale(this))),
    mConnectionLedPower(std::shared_ptr<InternalConnection>(
      new InternalConnection(this))),
    mConnectionLedA(std::shared_ptr<InternalConnection>(
      new InternalConnection(this))),
    mConnectionLedB(std::shared_ptr<InternalConnection>(
      new InternalConnection(this)))
{
  //Display
  mLedPower = std::shared_ptr<Led>(
    new Led(mConnectionLedPower.get(),255,0,0));
  mLedA = std::shared_ptr<Led>(
    new Led(mConnectionLedA.get(),255,0,0));
  mLedB = std::shared_ptr<Led>(
    new Led(mConnectionLedB.get(),255,0,0));
}
//---------------------------------------------------------------------------
//The DMX signal this machine can supply for a certain
//DMX channel. 0.0 = none, 1.0 = 100% (or FF).
const double SimpleShine2::DmxSignalStrength(const int dmxChannel) const
{
  if (this->HasPower() == false) return 0.0;
  if (dmxChannel >= 1 && dmxChannel <= 12) //Human based counting
  {
    const double master = this->mFaderMaster->GetRelPosition();
    const double crossfaderA = this->mCrossfaderA->GetRelPosition()
      * this->mFaders[dmxChannel-1]->GetRelPosition();
    const double crossfaderB = (1.0 - this->mCrossfaderB->GetRelPosition())
      * this->mFaders[12+dmxChannel-1]->GetRelPosition();
    return master * std::max(crossfaderA,crossfaderB);
  }
  return 0.001; //Small leaking current for DMX detection
}
//---------------------------------------------------------------------------
const double SimpleShine2::PowerSupplyStrength(const Connector * const connector,
  std::vector<const Connector*> /* prevConnectors */) const
{
  if (connector == mConnectionLedPower.get())
  {
    return (this->HasPower() == true ? 1.0 : 0.0);
  }
  else if (connector == mConnectionLedA.get())
  {
    if (this->HasPower() == false) return 0.0;
    return this->mCrossfaderA->GetRelPosition();
  }
  else if (connector == mConnectionLedB.get())
  {
    if (this->HasPower() == false) return 0.0;
    return (1.0 - this->mCrossfaderB->GetRelPosition());
  }

  return 0.0;
}
//---------------------------------------------------------------------------
//Does the machine have access to power? Does NOT mean the machine is ON!
const bool SimpleShine2::HasPower() const
{
  const Connector * const connectedTo = this->mEuroMalePower->GetConnectedTo();
  if (connectedTo == 0) return false;
  const Machine * const otherMachine = connectedTo->mBelongsTo;
  assert(otherMachine != 0);
  return (otherMachine->PowerSupplyStrength(
    connectedTo,std::vector<const Connector*>()) > 0.0 ? true : false);
}
//---------------------------------------------------------------------------
const std::vector<std::shared_ptr<Fader> >
  LightTable::CreateFaders(const int nFaders) const
{
  std::vector<std::shared_ptr<Fader> > faders;
  for (int i=0; i!=nFaders; ++i)
  {
    std::shared_ptr<Fader> fader(new Fader);
    faders.push_back(fader);
  }
  return faders;
}
//---------------------------------------------------------------------------

