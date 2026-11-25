//---------------------------------------------------------------------------

#ifndef UnitMdPlayerH
#define UnitMdPlayerH
//---------------------------------------------------------------------------
#include <vector>
#include <memory>
#include "UnitController.h"
#include "UnitMachine.h"
#include "UnitTapButton.h"
struct AudioSignalDisplay;
struct CinchRedFemale;
struct CinchWhiteFemale;
struct Connector;
struct InternalConnection;
struct LcdSymbol;
struct Led;
struct Plug220;
struct PressButton;
class FormMdPlayer;
//---------------------------------------------------------------------------
struct MdPlayer : public Machine
{
  MdPlayer();

  //The power this machine can supply. 0.0 = none, 1.0 = all needed
  const double PowerSupplyStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The audio signal this machine can supply. 0.0 = none, 1.0 = perfect gain
  //this depends on the connector (for example the MasterL connector supplies
  //different audio signals then Aux1
  const double AudioSignalStrength(const Connector * const connector,
    std::vector<const Connector*> prevConnectors) const;
  //The DMX signal this machine can supply for a certain
  //DMX channel. 0.0 = none, 1.0 = 100% (or FF).
  const double DmxSignalStrength(const int) const { return 0.0; };
  //Does the machine have power?
  const bool HasPower() const;

  void PressPower();
  void PressRecord();
  void PressStop();
  void PressPlay();
  void Tick(); //Must be called every time cycle for recording and playing

  private:

  enum MdPlayerState { mdOff, mdOn, mdPlay, mdRec };
  MdPlayerState mState;

  std::vector<double> mAudioRecordedL;
  std::vector<double> mAudioRecordedR;
  int mPlayPos;


  public:
  ~MdPlayer() {}
  private:

  //View
  //Use
  std::shared_ptr< TapButton<MdPlayer> > mButtonPower;
  std::shared_ptr< TapButton<MdPlayer> > mButtonRecord;
  std::shared_ptr< TapButton<MdPlayer> > mButtonStop;
  std::shared_ptr< TapButton<MdPlayer> > mButtonPlay;
  //Connect
  std::shared_ptr<CinchWhiteFemale> mCinchFemaleInL;
  std::shared_ptr<CinchRedFemale> mCinchFemaleInR;
  std::shared_ptr<CinchWhiteFemale> mCinchFemaleOutL;
  std::shared_ptr<CinchRedFemale> mCinchFemaleOutR;
  std::shared_ptr<Plug220> mPlug220Power;
  std::shared_ptr<InternalConnection> mConnectionAudioSignalL;
  std::shared_ptr<InternalConnection> mConnectionAudioSignalR;
  std::shared_ptr<InternalConnection> mConnectionLcdSymbolRecord;
  std::shared_ptr<InternalConnection> mConnectionLcdSymbolPlay;
  std::shared_ptr<InternalConnection> mConnectionLedPower;
  //Display
  std::shared_ptr<AudioSignalDisplay> mAudioSignalDisplayL;
  std::shared_ptr<AudioSignalDisplay> mAudioSignalDisplayR;
  std::shared_ptr<LcdSymbol> mLcdSymbolRecord;
  std::shared_ptr<LcdSymbol> mLcdSymbolPlay;
  std::shared_ptr<Led> mLedPower;

  friend class FormMdPlayer;
};
//---------------------------------------------------------------------------
#endif
