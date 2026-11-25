//---------------------------------------------------------------------------

#ifndef UnitAmplifierH
#define UnitAmplifierH
//---------------------------------------------------------------------------
#include <vector>
#include <memory>
#include "UnitMachine.h"
//Use
struct Dial;
struct TwoSwitch;
//Connect
struct EuroMale;
struct InternalConnection;
struct JackXlrFemale;
struct SpeakonFemale;
//Display
struct Led;
//Misc
class FormEasyAmp;
//---------------------------------------------------------------------------
struct Amplifier : public Machine
{
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  virtual const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const = 0;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  virtual const double AudioSignalStrength(const Connector * const,
    std::vector<const Connector*>) const = 0;
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  //Amplifiers do not use DMX
  const double DmxSignalStrength(const int dmxChannel) const { return 0.0; }
  //Does the machine have access to power? Does NOT mean the machine is ON!
  virtual const bool HasPower() const = 0;

  protected:
  public:
  virtual ~Amplifier() {}
  protected:

  //Misc
  const std::vector<std::shared_ptr<Fader> > CreateFaders(const int n) const;
};
//---------------------------------------------------------------------------
struct EasyAmp : public Amplifier
{
  EasyAmp();

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  const double AudioSignalStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //Does the machine have access to power? Does NOT mean the machine is ON!
  const bool HasPower() const;

  private:

  public:
  ~EasyAmp() {}
  private:

  //View
  //Use
  std::shared_ptr<TwoSwitch> mPowerSwitch;
  std::shared_ptr<Dial> mGain;
  //Connect
  std::shared_ptr<EuroMale> mEuroPower;
  std::shared_ptr<JackXlrFemale> mJackXlrL;
  std::shared_ptr<JackXlrFemale> mJackXlrR;
  std::shared_ptr<SpeakonFemale> mSpeakonL;
  std::shared_ptr<SpeakonFemale> mSpeakonR;
  std::shared_ptr<InternalConnection> mConnectionLedPower;
  //Display
  std::shared_ptr<Led> mLedPower;


  friend class FormEasyAmp;
};
//---------------------------------------------------------------------------

#endif
