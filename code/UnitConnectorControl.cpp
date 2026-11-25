//---------------------------------------------------------------------------

#include <cassert>
#include <memory>
#include "UnitConnector.h"
#include "UnitConnectorControl.h"
#include "UnitFormSprites.h"
#include "UnitFormMachine.h"
//---------------------------------------------------------------------------
ConnectorControl::ConnectorControl(FormMachine * const belongsTo,
  Image * const image,
  const Image * const imageUnselectedUnconnected,
  const Image * const imageSelectedUnconnected,
  const Image * const imageUnselectedConnected,
  const Image * const imageSelectedConnected)
  : mBelongsTo(belongsTo),
    mImage(image),
    mImageUnselectedUnconnected(imageUnselectedUnconnected),
    mImageSelectedUnconnected(imageSelectedUnconnected),
    mImageUnselectedConnected(imageUnselectedConnected),
    mImageSelectedConnected(imageSelectedConnected),
    mSelected(false),
    mIsConnectedTo(0)
{
  assert(mBelongsTo != 0);
  assert(mImage != 0);
}
//---------------------------------------------------------------------------
void ConnectorControl::Select()
{
  mSelected = true;
  this->UpdateImage();
}
//---------------------------------------------------------------------------
void ConnectorControl::Unselect()
{
  mSelected = false;
  this->UpdateImage();
}
//---------------------------------------------------------------------------
const bool ConnectorControl::CanConnect(
  ConnectorControl * const otherConnectorControl) const
{
  assert(otherConnectorControl != 0);

  //Two ConnectorControls can connect if their Connectors can connect
  const Connector * const thisConnector = this->GetConnector();
  const Connector * const otherConnector = otherConnectorControl->GetConnector();

  assert(thisConnector  != 0);
  assert(otherConnector != 0);

  assert ( thisConnector->CanConnect(otherConnector)
      == otherConnector->CanConnect(thisConnector)
    && "If A can (not) connect to B, B can (not) connect to A");

  return thisConnector->CanConnect(otherConnector);
}
//---------------------------------------------------------------------------
void ConnectorControl::Connect(ConnectorControl * const otherConnectorControl)
{
  assert(otherConnectorControl != 0);
  assert(this->CanConnect(otherConnectorControl)==true);

  {
    //Connect the two ConnectorControls
    this->mIsConnectedTo = otherConnectorControl;
    otherConnectorControl->mIsConnectedTo = this; //???Should not compile???
    assert(this->IsConnected() == true);
    assert(otherConnectorControl->IsConnected() == true);
  }

  {
    //Connect the two Connectors the ConnectorControls manage
    Connector * const thisConnector = this->GetConnector();
    assert(thisConnector != 0);
    Connector * const otherConnector = otherConnectorControl->GetConnector();
    assert(otherConnector != 0);

    //Two connections will take place, therefore otherConnector is either
    //null or already connected to this connector
    assert( (thisConnector->GetConnectedTo() == 0
        || thisConnector->GetConnectedTo() == otherConnector)
      && "Assume not connected and that this is handled by GUI?");
    assert( (otherConnector->GetConnectedTo() == 0
        || otherConnector->GetConnectedTo() == thisConnector)
      && "Assume not connected and that this is handled by GUI?");
    //Connect
    thisConnector->Connect(otherConnector);
    otherConnector->Connect(thisConnector);

    assert(thisConnector->IsConnected() == true);
    assert(otherConnector->IsConnected() == true);
  }

  //Choose image
  this->UpdateImage();
}
//---------------------------------------------------------------------------
const bool ConnectorControl::IsConnected() const
{
  return (this->mIsConnectedTo != 0);
}
//---------------------------------------------------------------------------
const bool ConnectorControl::IsConnectedTo(const ConnectorControl * other) const
{
  return (this->mIsConnectedTo == other);
}
//---------------------------------------------------------------------------
void ConnectorControl::Disconnect()
{
  //Disconnect the ConnectorControl
  mIsConnectedTo = 0;

  //Disconnect the Connector
  this->GetConnector()->Disconnect();

  this->UpdateImage();
}
//---------------------------------------------------------------------------
void ConnectorControl::UpdateImage()
{
  if (mSelected == true)
  {
    if (this->IsConnected() == true)
    {
      mImage->AssignPicture(mImageSelectedConnected);
    }
    else
    {
      mImage->AssignPicture(mImageSelectedUnconnected);
    }
  }
  else
  {
    if (this->IsConnected() == true)
    {
      mImage->AssignPicture(mImageUnselectedConnected);
    }
    else
    {
      mImage->AssignPicture(mImageUnselectedUnconnected);
    }
  }
}
//---------------------------------------------------------------------------
CinchRedFemaleControl::CinchRedFemaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<CinchRedFemale> cinchFemale,
  Image * const image)
  : ConnectorControl(
      belongsTo,
      image,
      Sprites()->ImageCinchFemaleRed,
      Sprites()->ImageCinchFemaleRedSelected,
      Sprites()->ImageCinchFemaleRedConnected,
      Sprites()->ImageCinchFemaleRedConnectedSelected),
    mCinchFemale(cinchFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const CinchRedFemaleControl::GetConnector() const
{
  return mCinchFemale.get();
}
//---------------------------------------------------------------------------
Connector * CinchRedFemaleControl::GetConnector()
{
  return mCinchFemale.get();
}
//---------------------------------------------------------------------------
CinchWhiteFemaleControl::CinchWhiteFemaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<CinchWhiteFemale> cinchFemale,
  Image * const image)
  : ConnectorControl(
      belongsTo,
      image,
      Sprites()->ImageCinchFemaleWhite,
      Sprites()->ImageCinchFemaleWhiteSelected,
      Sprites()->ImageCinchFemaleWhiteConnected,
      Sprites()->ImageCinchFemaleWhiteConnectedSelected),
    mCinchFemale(cinchFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const CinchWhiteFemaleControl::GetConnector() const
{
  return mCinchFemale.get();
}
//---------------------------------------------------------------------------
Connector * CinchWhiteFemaleControl::GetConnector()
{
  return mCinchFemale.get();
}
//---------------------------------------------------------------------------
DmxFemaleControl::DmxFemaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<DmxFemale> dmxFemale,
  Image * const image)
  : ConnectorControl(
      belongsTo,
      image,
      Sprites()->ImageDmxFemale,
      Sprites()->ImageDmxFemaleSelected,
      Sprites()->ImageDmxFemaleConnected,
      Sprites()->ImageDmxFemaleConnectedSelected),
    mDmxFemale(dmxFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const DmxFemaleControl::GetConnector() const
{
  return mDmxFemale.get();
}
//---------------------------------------------------------------------------
Connector * DmxFemaleControl::GetConnector()
{
  return mDmxFemale.get();
}
//---------------------------------------------------------------------------
DmxMaleControl::DmxMaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<DmxMale> euroMale,
  Image * const image)
  : ConnectorControl(
      belongsTo,
      image,
      Sprites()->ImageDmxMale,
      Sprites()->ImageDmxMaleSelected,
      Sprites()->ImageDmxMaleConnected,
      Sprites()->ImageDmxMaleConnectedSelected),
    mDmxMale(euroMale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const DmxMaleControl::GetConnector() const
{
  return mDmxMale.get();
}
//---------------------------------------------------------------------------
Connector * DmxMaleControl::GetConnector()
{
  return mDmxMale.get();
}
//---------------------------------------------------------------------------
EuroMaleControl::EuroMaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<EuroMale> euroMale,
  Image * const image)
  : ConnectorControl(
      belongsTo,
      image,
      Sprites()->ImageEuroMale,
      Sprites()->ImageEuroMaleSelected,
      Sprites()->ImageEuroMaleConnected,
      Sprites()->ImageEuroMaleConnectedSelected),
    mEuroMale(euroMale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const EuroMaleControl::GetConnector() const
{
  return mEuroMale.get();
}
//---------------------------------------------------------------------------
Connector * EuroMaleControl::GetConnector()
{
  return mEuroMale.get();
}
//---------------------------------------------------------------------------
EuroFemaleControl::EuroFemaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<EuroFemale> euroMale,
  Image * const image)
  : ConnectorControl(
      belongsTo,
      image,
      Sprites()->ImageEuroFemale,
      Sprites()->ImageEuroFemaleSelected,
      Sprites()->ImageEuroFemaleConnected,
      Sprites()->ImageEuroFemaleConnectedSelected),
    mEuroFemale(euroMale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const EuroFemaleControl::GetConnector() const
{
  return mEuroFemale.get();
}
//---------------------------------------------------------------------------
Connector * EuroFemaleControl::GetConnector()
{
  return mEuroFemale.get();
}
//---------------------------------------------------------------------------
JackFemaleControl::JackFemaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<JackFemale> xlrFemale,
  Image * const image)
  : ConnectorControl(belongsTo,image,
      Sprites()->ImageJackFemale,
      Sprites()->ImageJackFemaleSelected,
      Sprites()->ImageJackFemaleConnected,
      Sprites()->ImageJackFemaleConnectedSelected),
    mJackFemale(xlrFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const JackFemaleControl::GetConnector() const
{
  return mJackFemale.get();
}
//---------------------------------------------------------------------------
Connector * JackFemaleControl::GetConnector()
{
  return mJackFemale.get();
}
//---------------------------------------------------------------------------
JackXlrFemaleControl::JackXlrFemaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<JackXlrFemale> xlrFemale,
  Image * const image)
  : ConnectorControl(belongsTo,image,
      Sprites()->ImageJackXlrFemale,
      Sprites()->ImageJackXlrFemaleSelected,
      Sprites()->ImageJackXlrFemaleConnected,
      Sprites()->ImageJackXlrFemaleConnectedSelected),
    mJackXlrFemale(xlrFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const JackXlrFemaleControl::GetConnector() const
{
  return mJackXlrFemale.get();
}
//---------------------------------------------------------------------------
Connector * JackXlrFemaleControl::GetConnector()
{
  return mJackXlrFemale.get();
}
//---------------------------------------------------------------------------
JackMaleControl::JackMaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<JackMale> xlrFemale,
  Image * const image)
  : ConnectorControl(belongsTo,image,
      Sprites()->ImageJackMale,
      Sprites()->ImageJackMaleSelected,
      Sprites()->ImageJackMaleConnected,
      Sprites()->ImageJackMaleConnectedSelected),
    mJackMale(xlrFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const JackMaleControl::GetConnector() const
{
  return mJackMale.get();
}
//---------------------------------------------------------------------------
Connector * JackMaleControl::GetConnector()
{
  return mJackMale.get();
}
//---------------------------------------------------------------------------
Plug220Control::Plug220Control(
  FormMachine * const belongsTo,
  const std::shared_ptr<Plug220> plug220,
  Image * const image)
  : ConnectorControl(belongsTo,image,
      Sprites()->ImagePlug220,
      Sprites()->ImagePlug220Selected,
      Sprites()->ImagePlug220Connected,
      Sprites()->ImagePlug220ConnectedSelected),
    mPlug220(plug220)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const Plug220Control::GetConnector() const
{
  return mPlug220.get();
}
//---------------------------------------------------------------------------
Connector * Plug220Control::GetConnector()
{
  return mPlug220.get();
}
//---------------------------------------------------------------------------
Socket220Control::Socket220Control(
  FormMachine * const belongsTo,
  const std::shared_ptr<Socket220> socket220,
  Image * const image)
  : ConnectorControl(belongsTo,image,
      Sprites()->ImageSocket220,
      Sprites()->ImageSocket220Selected,
      Sprites()->ImageSocket220Connected,
      Sprites()->ImageSocket220ConnectedSelected),
    mSocket220(socket220)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const Socket220Control::GetConnector() const
{
  return mSocket220.get();
}
//---------------------------------------------------------------------------
Connector * Socket220Control::GetConnector()
{
  return mSocket220.get();
}
//---------------------------------------------------------------------------
SocketPowerFemaleControl::SocketPowerFemaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<SocketPowerFemale> socketPowerFemale,
  Image * const image)
  : ConnectorControl(belongsTo,image,
      Sprites()->ImageSocketPowerFemale,
      Sprites()->ImageSocketPowerFemaleSelected,
      Sprites()->ImageSocketPowerFemaleConnected,
      Sprites()->ImageSocketPowerFemaleConnectedSelected),
    mSocketPowerFemale(socketPowerFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const SocketPowerFemaleControl::GetConnector() const
{
  return mSocketPowerFemale.get();
}
//---------------------------------------------------------------------------
Connector * SocketPowerFemaleControl::GetConnector()
{
  return mSocketPowerFemale.get();
}
//---------------------------------------------------------------------------
SocketPowerMaleControl::SocketPowerMaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<SocketPowerMale> socketPowerMale,
  Image * const image)
  : ConnectorControl(belongsTo,image,
      Sprites()->ImageSocketPowerMale,
      Sprites()->ImageSocketPowerMaleSelected,
      Sprites()->ImageSocketPowerMaleConnected,
      Sprites()->ImageSocketPowerMaleConnectedSelected),
    mSocketPowerMale(socketPowerMale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const SocketPowerMaleControl::GetConnector() const
{
  return mSocketPowerMale.get();
}
//---------------------------------------------------------------------------
Connector * SocketPowerMaleControl::GetConnector()
{
  return mSocketPowerMale.get();
}
//---------------------------------------------------------------------------
SpeakonFemaleControl::SpeakonFemaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<SpeakonFemale> xlrFemale,
  Image * const image)
  : ConnectorControl(belongsTo,image,
      Sprites()->ImageSpeakonFemale,
      Sprites()->ImageSpeakonFemaleSelected,
      Sprites()->ImageSpeakonFemaleConnected,
      Sprites()->ImageSpeakonFemaleConnectedSelected),
    mSpeakonFemale(xlrFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const SpeakonFemaleControl::GetConnector() const
{
  return mSpeakonFemale.get();
}
//---------------------------------------------------------------------------
Connector * SpeakonFemaleControl::GetConnector()
{
  return mSpeakonFemale.get();
}
//---------------------------------------------------------------------------
SpeakonMaleControl::SpeakonMaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<SpeakonMale> xlrFemale,
  Image * const image)
  : ConnectorControl(belongsTo,image,
      Sprites()->ImageSpeakonMale,
      Sprites()->ImageSpeakonMaleSelected,
      Sprites()->ImageSpeakonMaleConnected,
      Sprites()->ImageSpeakonMaleConnectedSelected),
    mSpeakonMale(xlrFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const SpeakonMaleControl::GetConnector() const
{
  return mSpeakonMale.get();
}
//---------------------------------------------------------------------------
Connector * SpeakonMaleControl::GetConnector()
{
  return mSpeakonMale.get();
}
//---------------------------------------------------------------------------
XlrFemaleControl::XlrFemaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<XlrFemale> xlrFemale,
  Image * const image)
  : ConnectorControl(belongsTo,image,
      Sprites()->ImageXlrFemale,
      Sprites()->ImageXlrFemaleSelected,
      Sprites()->ImageXlrFemaleConnected,
      Sprites()->ImageXlrFemaleConnectedSelected),
    mXlrFemale(xlrFemale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const XlrFemaleControl::GetConnector() const
{
  return mXlrFemale.get();
}
//---------------------------------------------------------------------------
Connector * XlrFemaleControl::GetConnector()
{
  return mXlrFemale.get();
}
//---------------------------------------------------------------------------
XlrMaleControl::XlrMaleControl(
  FormMachine * const belongsTo,
  const std::shared_ptr<XlrMale> xlrMale,
  Image * const image)
  : ConnectorControl(belongsTo,image,
      Sprites()->ImageXlrMale,
      Sprites()->ImageXlrMaleSelected,
      Sprites()->ImageXlrMaleConnected,
      Sprites()->ImageXlrMaleConnectedSelected),
    mXlrMale(xlrMale)
{
  assert(belongsTo!=0);
}
//---------------------------------------------------------------------------
const Connector * const XlrMaleControl::GetConnector() const
{
  return mXlrMale.get();
}
//---------------------------------------------------------------------------
Connector * XlrMaleControl::GetConnector()
{
  return mXlrMale.get();
}
//---------------------------------------------------------------------------


