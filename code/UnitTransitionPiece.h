//---------------------------------------------------------------------------

#ifndef UnitTransitionPieceH
#define UnitTransitionPieceH
//---------------------------------------------------------------------------
#include "UnitMachine.h"
#include <memory>
struct JackMale;
struct CinchRedFemale;
struct CinchWhiteFemale;
class FormTransitionPieceJackMaleTwoCinchFemale;
//---------------------------------------------------------------------------
struct TransitionPiece : public Machine
{
  TransitionPiece() {}

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const { return 0.0; }
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  virtual const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const = 0;
  const double DmxSignalStrength(const int dmxChannel) const { return 0.0; }
  //Does the machine have access to power? Does NOT mean the machine is ON!
  const bool HasPower() const { return false; }

  protected:

  public:
  virtual ~TransitionPiece() {}
  protected:
  //or descandants

  //View
  //Use
  //Connect
  //Display

};
//---------------------------------------------------------------------------
struct TransitionPieceJackMaleTwoCinchFemale : public TransitionPiece
{
  TransitionPieceJackMaleTwoCinchFemale();

  const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;

  private:

  public:
  ~TransitionPieceJackMaleTwoCinchFemale() {}
  private:

  //View
  //Use
  //Connect
  std::shared_ptr<JackMale> mJack;
  std::shared_ptr<CinchWhiteFemale> mCinchL;
  std::shared_ptr<CinchRedFemale> mCinchR;
  //Display

  friend class FormTransitionPieceJackMaleTwoCinchFemale;
};
//---------------------------------------------------------------------------
#endif
