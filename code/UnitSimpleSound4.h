//---------------------------------------------------------------------------

#ifndef UnitSimpleSound4H
#define UnitSimpleSound4H
//---------------------------------------------------------------------------
#include <memory>
#include "UnitAux.h"
#include "UnitChannel.h"
#include "UnitSoundTable.h"
//Control
struct Dial;
struct Fader;
struct PressButton;
//Connect
struct CinchRedFemale;
struct CinchWhiteFemale;
struct Connector;
struct EuroMale;
struct InternalConnection;
struct JackFemale;
struct XlrFemale;
struct XlrMale;
//Display
struct AudioSignalDisplay;
//GUI friend
class FormSimpleSound4;
//---------------------------------------------------------------------------
struct SimpleSound4 : public SoundTable
{
  SimpleSound4();

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
  ~SimpleSound4() {}
  private:

  //View
  //Use
  std::shared_ptr<Fader> mFader1;
  std::shared_ptr<Fader> mFader2;
  std::shared_ptr<Fader> mFader3;
  std::shared_ptr<Fader> mFader4;
  std::shared_ptr<Dial> mDialGain1;
  std::shared_ptr<Dial> mDialGain2;
  std::shared_ptr<Dial> mDialGain3;
  std::shared_ptr<Dial> mDialAux1_1;
  std::shared_ptr<Dial> mDialAux1_2;
  std::shared_ptr<Dial> mDialAux1_3;
  std::shared_ptr<Dial> mDialAux1_4;
  std::shared_ptr<Dial> mDialAux2_1;
  std::shared_ptr<Dial> mDialAux2_2;
  std::shared_ptr<Dial> mDialAux2_3;
  std::shared_ptr<Dial> mDialAux2_4;
  std::shared_ptr<PressButton> mPressButtonPfl1;
  std::shared_ptr<PressButton> mPressButtonPfl2;
  std::shared_ptr<PressButton> mPressButtonPfl3;
  std::shared_ptr<PressButton> mPressButtonPfl4;
  std::shared_ptr<Dial> mDialSendAux1;
  std::shared_ptr<Dial> mDialSendAux2;
  std::shared_ptr<Fader> mFaderMaster;
  //Connect
  std::shared_ptr<XlrFemale> mMic1;
  std::shared_ptr<XlrFemale> mMic2;
  std::shared_ptr<XlrFemale> mMic3;
  std::shared_ptr<CinchWhiteFemale> mCinchFemaleL4;
  std::shared_ptr<CinchRedFemale> mCinchFemaleR4;
  std::shared_ptr<JackFemale> mAux1;
  std::shared_ptr<JackFemale> mAux2;
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
    const Channel channel) const;
  const double AudioSignalMasterOutputStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors,
    const Channel channel) const;
  const double AudioSignalAuxOutputStrength(
    const Connector * const connector,
    std::vector<const Connector*> prevConnectors,
    const Channel channel, const Aux aux) const;


  friend class FormSimpleSound4;
};
//---------------------------------------------------------------------------
#endif
