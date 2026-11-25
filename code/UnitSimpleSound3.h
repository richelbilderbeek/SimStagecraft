//---------------------------------------------------------------------------

#ifndef UnitSimpleSound3H
#define UnitSimpleSound3H
//---------------------------------------------------------------------------
#include <memory>
#include "UnitSoundTable.h"
struct Fader;
struct PressButton;
struct Dial;
struct Connector;
struct EuroMale;
struct JackFemale;
struct XlrMale;
struct XlrFemale;
struct InternalConnection;
struct AudioSignalDisplay;
class FormSimpleSound3;
//---------------------------------------------------------------------------
struct SimpleSound3 : public SoundTable
{
  SimpleSound3();

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
  ~SimpleSound3() {}
  private:

  //View
  //Use
  std::shared_ptr<Fader> mFader1;
  std::shared_ptr<Fader> mFader2;
  std::shared_ptr<Fader> mFader3;
  std::shared_ptr<Dial> mDialGain1;
  std::shared_ptr<Dial> mDialGain2;
  std::shared_ptr<Dial> mDialGain3;
  std::shared_ptr<Dial> mDialAux1_1;
  std::shared_ptr<Dial> mDialAux1_2;
  std::shared_ptr<Dial> mDialAux1_3;
  std::shared_ptr<PressButton> mPressButtonPfl1;
  std::shared_ptr<PressButton> mPressButtonPfl2;
  std::shared_ptr<PressButton> mPressButtonPfl3;
  std::shared_ptr<Dial> mDialSendAux1;
  std::shared_ptr<Fader> mFaderMaster;
  //Connect
  std::shared_ptr<XlrFemale> mMic1;
  std::shared_ptr<XlrFemale> mMic2;
  std::shared_ptr<XlrFemale> mMic3;
  std::shared_ptr<JackFemale> mAux1;
  std::shared_ptr<XlrMale> mMasterL;
  std::shared_ptr<XlrMale> mMasterR;
  std::shared_ptr<EuroMale> mPower;
  std::shared_ptr<InternalConnection> mConnectionAudioSignal;
  //Display
  std::shared_ptr<AudioSignalDisplay> mAudioSignalDisplay;
  //Misc
  const double AudioSignalInputStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors,
    const int channel) const;
  const double AudioSignalMasterOutputStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors,
    const int channel) const;
  const double AudioSignalAuxOutputStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors,
    const int channel) const;


  friend class FormSimpleSound3;
};
//---------------------------------------------------------------------------
#endif
