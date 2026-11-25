//---------------------------------------------------------------------------

#ifndef UnitSimpleSound2H
#define UnitSimpleSound2H
//---------------------------------------------------------------------------
#include <memory>
#include "UnitSoundTable.h"
struct Fader;
struct PressButton;
struct Dial;
struct Connector;
struct EuroMale;
struct XlrMale;
struct XlrFemale;
struct InternalConnection;
struct AudioSignalDisplay;
class FormSimpleSound2;
//---------------------------------------------------------------------------
struct SimpleSound2 : public SoundTable
{
  SimpleSound2();

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //Does the machine have power?
  const bool HasPower() const;

  private:

  public:
  ~SimpleSound2() {}
  private:

  //View
  //Use
  std::shared_ptr<Fader> mFader1;
  std::shared_ptr<Fader> mFader2;
  std::shared_ptr<Dial> mDial1; //Gain dial
  std::shared_ptr<Dial> mDial2; //Gain dial
  std::shared_ptr<PressButton> mPressButton1; //PFL button
  std::shared_ptr<PressButton> mPressButton2; //PFL button
  std::shared_ptr<Fader> mFaderMaster;
  //Connect
  std::shared_ptr<XlrFemale> mMic1;
  std::shared_ptr<XlrFemale> mMic2;
  std::shared_ptr<XlrMale> mMasterL;
  std::shared_ptr<XlrMale> mMasterR;
  std::shared_ptr<EuroMale> mPower;
  std::shared_ptr<InternalConnection> mConnectionAudioSignal;
  //Display
  std::shared_ptr<AudioSignalDisplay> mAudioSignalDisplay;
  //Misc

  friend class FormSimpleSound2;
};
//---------------------------------------------------------------------------
#endif
