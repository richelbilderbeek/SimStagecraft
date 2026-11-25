//---------------------------------------------------------------------------

#ifndef UnitTripletH
#define UnitTripletH
//---------------------------------------------------------------------------
#include <memory>
#include "UnitMachine.h"
//---------------------------------------------------------------------------
struct TwoSwitch;
//struct Connector;
struct Plug220;
struct Socket220;
class FormTriplet;
//---------------------------------------------------------------------------
struct Triplet : public Machine
{
  Triplet();
  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  //This depends on the connector, especially on a dimmer pack
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*>) const { return 0.0; }
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  const double DmxSignalStrength(const int dmxChannel) const { return 0.0; }
  //Does the machine have access to power? Does NOT mean the machine is ON!
  const bool HasPower() const;

  private:
  //View
  //Use
  //Connect
  std::shared_ptr<Plug220> mPlug;
  std::shared_ptr<Socket220> mSocket220_1;
  std::shared_ptr<Socket220> mSocket220_2;
  std::shared_ptr<Socket220> mSocket220_3;

  friend class FormTriplet;

  public:
  ~Triplet() {}
  private:

};
//---------------------------------------------------------------------------

#endif
