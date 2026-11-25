//---------------------------------------------------------------------------

#ifndef UnitMicrophoneH
#define UnitMicrophoneH
//---------------------------------------------------------------------------
#include <memory>
#include "UnitMachine.h"
class FormShureSm58;
struct XlrMale;
//---------------------------------------------------------------------------
struct Microphone : public Machine
{
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //This depends on the connector, especially on a dimmer pack
  const double PowerSupplyStrength(const Connector * const,
    std::vector<const Connector*>) const { return 0.0; }
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  virtual const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const = 0;
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  const double DmxSignalStrength(const int) const { return 0.0; }
  //Does the machine have access to power? Does NOT mean the machine is ON!
  virtual const bool HasPower() const = 0;

  protected:
  public:
  virtual ~Microphone() {}
  protected:


};
//---------------------------------------------------------------------------
struct ShureSm58 : public Microphone
{
  ShureSm58();
  const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  const bool HasPower() const;


  private:

  friend class FormShureSm58;

  double mAudioSignalStrength;
  void SetAudioSignalStrength(const double audioSignalStrength);
  double GetAudioSignalStrength() const { return mAudioSignalStrength; }

  //View
  //Use
  //Shure SM-58 does not have a power switch
  //Connect
  std::shared_ptr<XlrMale> mXlrInput;


  public:
  ~ShureSm58() {}
  private:
};
//---------------------------------------------------------------------------
#endif
