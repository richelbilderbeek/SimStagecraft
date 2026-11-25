//---------------------------------------------------------------------------

#ifndef UnitDimmerpackH
#define UnitDimmerpackH
//---------------------------------------------------------------------------
#include <vector>
#include <memory>
#include "UnitMachine.h"
class FormDimblockV3;
struct SocketPowerMale;
struct DmxMale;
struct DmxFemale;
struct LcdDisplay;
struct Led;
struct InternalConnection;
//---------------------------------------------------------------------------
struct Dimmerpack : public Machine
{
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //This depends on the connector, especially on a dimmer pack
  virtual const double PowerSupplyStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const = 0;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  //Dimmerpacks never supply audio
  const double AudioSignalStrength(const Connector * const,
    std::vector<const Connector*>) const { return 0.0; }
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  virtual const double DmxSignalStrength(const int dmxChannel) const = 0;
  //Does the machine have access to power? Does NOT mean the machine is ON!
  virtual const bool HasPower() const = 0;

  protected:
  public:
  virtual ~Dimmerpack() {}
  protected:


};
//---------------------------------------------------------------------------
struct DimblockV3 : public Dimmerpack
{
  DimblockV3();

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //This depends on the connector, especially on a dimmer pack
  const double PowerSupplyStrength(const Connector * const  connector,
    std::vector<const Connector*> prevConnectors) const;
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  const double DmxSignalStrength(const int dmxChannel) const;
  //Does the machine have access to power? Does NOT mean the machine is ON!
  const bool HasPower() const;

  private:

  public:
  ~DimblockV3() {}
  private:

  //View
  //Use
  //Connect
  std::shared_ptr<DmxMale> mDmxMaleInput;
  std::shared_ptr<DmxFemale> mDmxFemaleOutput;
  std::shared_ptr<SocketPowerMale> mPowerMale;
  std::vector<std::shared_ptr<Socket220> > mSockets;

  std::shared_ptr<InternalConnection> mConnectionLedMainsPower;
  std::shared_ptr<InternalConnection> mConnectionLedNondimSet;
  std::shared_ptr<InternalConnection> mConnectionLedPresetSet;
  std::shared_ptr<InternalConnection> mConnectionLedDmxPresent;
  std::shared_ptr<InternalConnection> mConnectionLedWarning;
  //Display
  std::shared_ptr<Led> mLedMainsPower;
  std::shared_ptr<Led> mLedNondimSet;
  std::shared_ptr<Led> mLedPresetSet;
  std::shared_ptr<Led> mLedDmxPresent;
  std::shared_ptr<Led> mLedWarning;


  friend class FormDimblockV3;

};
//---------------------------------------------------------------------------
const std::vector<std::shared_ptr<Socket220> > CreateSockets(
  const Machine * const belongTo,
  const int nSockets);
//---------------------------------------------------------------------------
#endif
