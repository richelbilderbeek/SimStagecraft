//---------------------------------------------------------------------------

#ifndef UnitLightTableH
#define UnitLightTableH
//---------------------------------------------------------------------------
#include <vector>
#include <memory>
#include "UnitMachine.h"
//Use
struct Fader;
//Connect
struct Connector;
struct InternalConnection;
struct EuroMale;
struct DmxFemale;
//Display
struct Led;
//Misc
class FormSimpleShine1;
class FormSimpleShine2;
//---------------------------------------------------------------------------
struct LightTable : public Machine
{
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const = 0;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  //Light tables NEVER supply audio
  const double AudioSignalStrength(const Connector * const,
    std::vector<const Connector*>) const { return 0.0; }
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  virtual const double DmxSignalStrength(const int dmxChannel) const = 0;
  //Does the machine have access to power? Does NOT mean the machine is ON!
  virtual const bool HasPower() const = 0;

  protected:
  public:
  virtual ~LightTable() {}
  protected:

  //Misc
  const std::vector<std::shared_ptr<Fader> > CreateFaders(const int n) const;
};
//---------------------------------------------------------------------------
struct SimpleShine1 : public LightTable
{
  SimpleShine1();

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  const double DmxSignalStrength(const int dmxChannel) const;
  //Does the machine have access to power? Does NOT mean the machine is ON!
  const bool HasPower() const;

  private:

  public:
  ~SimpleShine1() {}
  private:

  //View
  //Use
  std::vector<std::shared_ptr<Fader> > mFaders;
  std::shared_ptr<Fader> mFaderMaster;
  //Connect
  std::shared_ptr<EuroMale> mEuroMalePower;
  std::shared_ptr<DmxFemale> mDmxFemaleOut;
  std::shared_ptr<InternalConnection> mConnectionLedPower;
  //Display
  std::shared_ptr<Led> mLedPower;


  friend class FormSimpleShine1;
};
//---------------------------------------------------------------------------
struct SimpleShine2 : public LightTable
{
  SimpleShine2();

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  const double DmxSignalStrength(const int dmxChannel) const;
  //Does the machine have access to power? Does NOT mean the machine is ON!
  const bool HasPower() const;

  private:

  public:
  ~SimpleShine2() {}
  private:

  //View
  //Use
  std::vector<std::shared_ptr<Fader> > mFaders;
  std::shared_ptr<Fader> mFaderMaster;
  std::shared_ptr<Fader> mCrossfaderA;
  std::shared_ptr<Fader> mCrossfaderB;
  //Connect
  std::shared_ptr<EuroMale> mEuroMalePower;
  std::shared_ptr<DmxFemale> mDmxFemaleOut;
  std::shared_ptr<InternalConnection> mConnectionLedPower;
  std::shared_ptr<InternalConnection> mConnectionLedA;
  std::shared_ptr<InternalConnection> mConnectionLedB;
  //Display
  std::shared_ptr<Led> mLedPower;
  std::shared_ptr<Led> mLedA;
  std::shared_ptr<Led> mLedB;


  friend class FormSimpleShine2;
};
//---------------------------------------------------------------------------

#endif
