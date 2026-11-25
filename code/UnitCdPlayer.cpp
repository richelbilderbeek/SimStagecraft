//---------------------------------------------------------------------------

#include <cassert>
#include "UnitCdPlayer.h"
//---------------------------------------------------------------------------
#include <cmath>
#include "UnitDisplay.h"
#include "UnitConnector.h"
#include "UnitController.h"
//---------------------------------------------------------------------------
CdPlayer::CdPlayer()
  :
  //Use
  mButtonPower(std::shared_ptr<TapButton<CdPlayer> >(
    new TapButton<CdPlayer>(this,&CdPlayer::PressPower))),
  mButtonStop(std::shared_ptr<TapButton<CdPlayer> >(
    new TapButton<CdPlayer>(this,&CdPlayer::PressStop))),
  mButtonPlay(std::shared_ptr<TapButton<CdPlayer> >(
    new TapButton<CdPlayer>(this,&CdPlayer::PressPlay))),
  //Connect
  mCinchFemaleOutL(std::shared_ptr<CinchWhiteFemale>(new CinchWhiteFemale(this))),
  mCinchFemaleOutR(std::shared_ptr<CinchRedFemale>(new CinchRedFemale(this))),
  mPlug220Power(std::shared_ptr<Plug220>(new Plug220(this))),
  mConnectionAudioSignalL(std::shared_ptr<InternalConnection>(
    new InternalConnection(this))),
  mConnectionAudioSignalR(std::shared_ptr<InternalConnection>(
    new InternalConnection(this))),
  mConnectionLcdSymbolPlay(std::shared_ptr<InternalConnection> (
    new InternalConnection(this))),
  mConnectionLedPower(std::shared_ptr<InternalConnection> (
    new InternalConnection(this))),
  mState(cdOff),
  mAudioRecordedL(this->CreateCdL()),
  mAudioRecordedR(this->CreateCdR()),
  mPlayPos(0)
{
  //Display
  mAudioSignalDisplayL = std::shared_ptr<AudioSignalDisplay>(
    new AudioSignalDisplay(mConnectionAudioSignalL.get()));
  mAudioSignalDisplayR = std::shared_ptr<AudioSignalDisplay>(
    new AudioSignalDisplay(mConnectionAudioSignalR.get()));
  mLcdSymbolPlay = std::shared_ptr<LcdSymbol>(
    new LcdSymbol(mConnectionLcdSymbolPlay.get()));
  mLedPower = std::shared_ptr<Led>(
    new Led(mConnectionLedPower.get(),0,255,0));
}
//---------------------------------------------------------------------------
const double CdPlayer::PowerSupplyStrength(
  const Connector * const connector,
  std::vector<const Connector*> /* prevConnectors */) const
{
  assert(connector != 0);
  if (this->HasPower() == false) return 0.0;

  if (connector == mConnectionAudioSignalL.get())
  {
    return this->AudioSignalStrength(mCinchFemaleOutL.get(),
      std::vector<const Connector*>());
  }
  else if (connector == mConnectionAudioSignalR.get())
  {
    return this->AudioSignalStrength(mCinchFemaleOutR.get(),
      std::vector<const Connector*>());
  }
  else if (connector == mConnectionLcdSymbolPlay.get())
  {
    return (mState == cdPlay ? 1.0 : 0.0);
  }
  else if (connector == mConnectionLedPower.get())
  {
    return (mState != cdOff ? 1.0 : 0.0);
  }
  return 0.0;
}
//---------------------------------------------------------------------------
const double CdPlayer::AudioSignalStrength(
  const Connector * const connector,
  std::vector<const Connector*> prevConnectors) const
{
  assert(connector == mCinchFemaleOutL.get()
      || connector == mCinchFemaleOutR.get() );

  if (this->HasPower() == false) return 0.0;

  if (mState == cdPlay)
  {
    //Playing from CD disc, return CD disc signal ONLY
    //-> that is, input to CD player is discarded
    if (connector == mCinchFemaleOutL.get())
    {
      assert(mPlayPos >= 0);
      assert(mPlayPos < static_cast<int>(mAudioRecordedL.size()));
      return mAudioRecordedL[mPlayPos];
    }
    else if (connector == mCinchFemaleOutR.get())
    {
      assert(mPlayPos >= 0);
      assert(mPlayPos < static_cast<int>(mAudioRecordedR.size()));
      return mAudioRecordedR[mPlayPos];
    }

  }
  return 0.0;
}
//---------------------------------------------------------------------------
const bool CdPlayer::HasPower() const
{
  assert(this->mPlug220Power.get() != 0);
  const Connector * const connectedTo = this->mPlug220Power->GetConnectedTo();
  if (connectedTo == 0)
  {
    //Power plug (220V) not connected to anything
    return false;
  }
  const Machine * const otherMachine = connectedTo->mBelongsTo;
  assert(otherMachine != 0);

  const double powerSupply = otherMachine->PowerSupplyStrength(
    connectedTo,std::vector<const Connector*>());
  return (powerSupply > 0.0 ? true : false);
}
//---------------------------------------------------------------------------
void CdPlayer::PressPower()
{
  if (mState != cdOff) { mState = cdOff; }
  else if (this->HasPower() == true) mState = cdOn;
}
//---------------------------------------------------------------------------
void CdPlayer::PressStop()
{
  if (this->HasPower() == true)
  {
    mState = cdOn;
    mPlayPos = 0;
  }
  else
  {
    mState = cdOff;
  }
}
//---------------------------------------------------------------------------
void CdPlayer::PressPlay()
{
  if (this->HasPower() == true)
  {
    mState = cdPlay;
    mPlayPos = 0;
  }
  else
  {
    mState = cdOff;
  }
}
//---------------------------------------------------------------------------
//Must be called every time cycle for recording and playing
void CdPlayer::Tick()
{
  if (this->HasPower() == false)
  {
    mState = cdOff;
  }
  else if (mState == cdPlay)
  {
    assert(this->HasPower() == true);
    ++mPlayPos;
    assert(mAudioRecordedL.size() == mAudioRecordedR.size());
    if (mPlayPos == static_cast<int>(mAudioRecordedL.size()))
    {
      //Stop playing
      mPlayPos = 0;
      mState = cdOn;
    }
  }
}
//---------------------------------------------------------------------------
const std::vector<double> CdPlayer::CreateCdL() const
{
  const int length = CdPlayer::mAudioRecordedLength;
  std::vector<double> v;
  v.reserve(length);
  for (int i=0; i!=length; ++i)
  {
    const double x
      = (static_cast<double>(i) / static_cast<double>(length))
      * 6.0 * M_PI;
    const double y = 0.5 + (std::cos(x) * 0.45);
    v.push_back(y);
  }
  return v;
}
//---------------------------------------------------------------------------
const std::vector<double> CdPlayer::CreateCdR() const
{
  const int length = CdPlayer::mAudioRecordedLength;
  std::vector<double> v;
  v.reserve(length);
  for (int i=0; i!=length; ++i)
  {
    const double x
      = (static_cast<double>(i) / static_cast<double>(length))
      * 8.0 * M_PI;
    const double y = 0.5 + (std::sin(x) * 0.45);
    v.push_back(y);
  }
  return v;
}
//---------------------------------------------------------------------------

