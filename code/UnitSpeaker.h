//---------------------------------------------------------------------------

#ifndef UnitSpeakerH
#define UnitSpeakerH
//---------------------------------------------------------------------------
#include <memory>
#include "UnitMachine.h"
//View
//Use
struct TwoSwitch;
struct Dial;
//Connectors
struct EuroMale;
struct InternalConnection;
struct JackFemale;
struct SpeakonFemale;
struct XlrFemale;
struct XlrMale;
//Display
struct Led;
//Forms
class FormRcf322A;
class FormRcfEvent3000;
//---------------------------------------------------------------------------
struct Speaker : public Machine
{
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //Speakers supply power to for example a power indication LED
  virtual const double PowerSupplyStrength(const Connector * const,
    std::vector<const Connector*> prevConnectors) const = 0;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //Speakers can be daisy-chained, so a speaker can supply an audio signal
  virtual const double AudioSignalStrength(const Connector * const,
    std::vector<const Connector*> prevConnectors) const = 0;
  //Speakers never send out DMX signals
  const double DmxSignalStrength(const int ) const { return 0.0; }
  //Does the machine have power?
  virtual const bool HasPower() const = 0;

  protected:
  public:
  virtual ~Speaker() {}
  protected:

};
//---------------------------------------------------------------------------
struct PassiveSpeaker : public Speaker
{
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //Speakers supply power to for example a power indication LED
  const double PowerSupplyStrength(const Connector * const,
    std::vector<const Connector*> prevConnectors) const { return 0.0; }
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //Speakers can be daisy-chained, so a speaker can supply an audio signal
  virtual const double AudioSignalStrength(const Connector * const,
    std::vector<const Connector*> prevConnectors) const = 0;
  const bool HasPower() const { return 0.0; }

  protected:
  public:
  virtual ~PassiveSpeaker() {}
  protected:

};
//---------------------------------------------------------------------------
struct Rcf322A : public Speaker
{
  Rcf322A();

  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //Does the machine have power?
  const bool HasPower() const;
  //What is the sound output (with the limiter acting)?
  const double GetSoundLevel() const;
  //The maximal sound level before the limiter protection kicks in
  const double mMaxSoundLevel;


  private:

  //The sound level without the limiter acting
  const double GetUnlimitedSoundLevel() const;

  public:
  ~Rcf322A() {}
  private:

  //View
  //Use
  std::shared_ptr<TwoSwitch> mPowerSwitch;
  std::shared_ptr<Dial> mVolumeDial;
  //Connect
  std::shared_ptr<JackFemale> mJackInput;
  std::shared_ptr<XlrMale> mXlrDaisyChain;
  std::shared_ptr<XlrFemale> mXlrInput;
  std::shared_ptr<EuroMale> mEuroMalePower;
  std::shared_ptr<InternalConnection> mConnectionLedPower;
  std::shared_ptr<InternalConnection> mConnectionLedLimProt;
  //Display
  std::shared_ptr<Led> mLedPower;
  std::shared_ptr<Led> mLedLimProt;

  friend class FormRcf322A;
};
//---------------------------------------------------------------------------
struct RcfEvent3000 : public PassiveSpeaker
{
  RcfEvent3000();

  const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //What is the sound output?
  const double GetSoundLevel() const;

  private:

  //The sound level without the limiter acting
  const double GetUnlimitedSoundLevel() const;

  public:
  ~RcfEvent3000() {}
  private:

  //View
  //Use
  //Connect
  std::shared_ptr<SpeakonFemale> mInput;
  std::shared_ptr<SpeakonFemale> mLink;
  //Display

  friend class FormRcfEvent3000;
};
//---------------------------------------------------------------------------

#endif
