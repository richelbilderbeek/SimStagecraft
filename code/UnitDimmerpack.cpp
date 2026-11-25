//---------------------------------------------------------------------------

#include <cassert>
#include "UnitDisplay.h"
#include "UnitConnector.h"
#include "UnitDimmerpack.h"
//---------------------------------------------------------------------------
DimblockV3::DimblockV3()
  : mDmxMaleInput(std::shared_ptr<DmxMale>(new DmxMale(this))),
    mDmxFemaleOutput(std::shared_ptr<DmxFemale>(new DmxFemale(this))),
    mPowerMale(std::shared_ptr<SocketPowerMale>(new SocketPowerMale(this))),
    mSockets(CreateSockets(this,12)),
    mConnectionLedMainsPower(std::shared_ptr<InternalConnection>(
      new InternalConnection(this))),
    mConnectionLedNondimSet(std::shared_ptr<InternalConnection>(
      new InternalConnection(this))),
    mConnectionLedPresetSet(std::shared_ptr<InternalConnection>(
      new InternalConnection(this))),
    mConnectionLedDmxPresent(std::shared_ptr<InternalConnection>(
      new InternalConnection(this))),
    mConnectionLedWarning(std::shared_ptr<InternalConnection>(
      new InternalConnection(this)))
{
  assert(mDmxMaleInput.get() != 0);
  assert(mDmxFemaleOutput.get() != 0);
  assert(mPowerMale.get() != 0);
  assert(mSockets.size() == 12);

  //Display
  mLedMainsPower = std::shared_ptr<Led>(
    new Led(mConnectionLedMainsPower.get(),255,0,0));
  mLedNondimSet = std::shared_ptr<Led>(
    new Led(mConnectionLedNondimSet.get(),0,255,0));
  mLedPresetSet = std::shared_ptr<Led>(
    new Led(mConnectionLedPresetSet.get(),255,255,0));
  mLedDmxPresent = std::shared_ptr<Led>(
    new Led(mConnectionLedDmxPresent.get(),0,255,0));
  mLedWarning = std::shared_ptr<Led>(
    new Led(mConnectionLedWarning.get(),255,0,0));

}
//---------------------------------------------------------------------------
//No need of prevConnectors, as this dimmerpack cannot be cirle-connected
const double DimblockV3::PowerSupplyStrength(
  const Connector * const connector,
  std::vector<const Connector*> /* prevConnectors */) const
{
  if (this->HasPower() == false) return 0.0;

  //Check sockets
  const int nSockets = mSockets.size();
  for (int i=0; i!=nSockets; ++i)
  {
    if (connector == mSockets[i].get())
    {
      //Is dimmerpack connected to table?
      const Connector * const otherConnector = this->mDmxMaleInput->GetConnectedTo();
      if (otherConnector == 0) return 0.0;
      //To which machine?
      const Machine * const otherMachine = otherConnector->mBelongsTo;
      assert(otherMachine != 0);
      //The strength of DMX signal is linear to the power supplied to this socket
      //'+1', because DMX signals start counting at 1
      return otherMachine->DmxSignalStrength(i+1);
    }
  }
  //Check internal connections
  if (connector == mConnectionLedMainsPower.get() )
  {
    return (this->HasPower() == true ? 1.0 : 0.0);
  }
  if (connector == mConnectionLedNondimSet.get() )
  {
    //Don't know when the indication LED should light
    return 0.0;
  }
  if (connector == mConnectionLedPresetSet.get() )
  {
    //Don't know when the indication LED should light
    return 0.0;
  }
  if (connector == mConnectionLedDmxPresent.get() )
  {
    //Check 512 channels
    for (int i=0; i!=512; ++i)
    {
      if (this->DmxSignalStrength(i) > 0.0) return 1.0;
    }
    return 0.0;
  }
  if (connector == mConnectionLedWarning.get() )
  {
    //Don't know when the indication LED should light
    return 0.0;
  }
  return 0.0;
}
//---------------------------------------------------------------------------
const double DimblockV3::DmxSignalStrength(const int dmxChannel) const
{
  if (this->HasPower() == false) return 0.0;

  //Forward the DMX signal

  //Is dimmerpack connected to table?
  const Connector * const otherConnector = this->mDmxMaleInput->GetConnectedTo();
  if (otherConnector == 0) return 0.0;
  //To which machine?
  const Machine * const otherMachine = otherConnector->mBelongsTo;
  assert(otherMachine != 0);
  //The strength of DMX signal is linear to the power supplied to this socket
  return otherMachine->DmxSignalStrength(dmxChannel);
}
//---------------------------------------------------------------------------
const bool DimblockV3::HasPower() const
{
  //Is dimmerpack connected to table?
  const Connector * const otherConnector = this->mPowerMale->GetConnectedTo();
  if (otherConnector == 0) return 0.0;
  //To which machine?
  const Machine * const otherMachine = otherConnector->mBelongsTo;
  assert(otherMachine != 0);
  //The strength of DMX signal is linear to the power supplied to this socket
  return otherMachine->PowerSupplyStrength(
    otherConnector,std::vector<const Connector*>());
}
//---------------------------------------------------------------------------
const std::vector<std::shared_ptr<Socket220> > CreateSockets(
  const Machine * const belongTo,
  const int nSockets)
{
  std::vector<std::shared_ptr<Socket220> > sockets;

  for (int i=0; i!=nSockets; ++i)
  {
    std::shared_ptr<Socket220> socket(new Socket220(belongTo));
    sockets.push_back(socket);
  }
  return sockets;
}
//---------------------------------------------------------------------------
