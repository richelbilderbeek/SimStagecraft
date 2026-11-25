//---------------------------------------------------------------------------

#ifndef UnitConnectorControlH
#define UnitConnectorControlH
//---------------------------------------------------------------------------
#include <memory>
struct Connector;
class FormSprites;
class FormMachine;
struct CinchRedFemale;
struct CinchRedMale;
struct CinchWhiteFemale;
struct CinchWhiteMale;
struct DmxFemale;
struct DmxMale;
struct EuroFemale;
struct EuroMale;
struct JackFemale;
struct JackXlrFemale; //Combo connector of both Jack female and XLR female
struct JackMale;
struct Plug220;
struct Socket220;
struct SocketPowerFemale;
struct SocketPowerMale;
struct SpeakonFemale;
struct SpeakonMale;
struct XlrFemale;
struct XlrMale;
struct Image;
//---------------------------------------------------------------------------
//Handles the GUI of a Connector
struct ConnectorControl
{
  ConnectorControl(
    FormMachine * const belongsTo,
    Image * const image,
    const Image * const imageUnselectedUnconnected,
    const Image * const imageSelectedUnconnected,
    const Image * const imageUnselectedConnected,
    const Image * const imageSelectedConnected);

  void Select();
  void Unselect();
  void Connect(ConnectorControl * const otherConnectorControl);
  void Disconnect();
  const bool CanConnect(ConnectorControl * const otherConnectorControl) const;

  virtual const Connector * const GetConnector() const = 0;
  virtual Connector * GetConnector() = 0;

  const bool IsConnected() const;
  const bool IsConnectedTo(const ConnectorControl * other) const;

  protected:
  public:
  virtual ~ConnectorControl() {}
  protected:

  const Image * const mImageUnselectedUnconnected;
  const Image * const mImageSelectedUnconnected;
  const Image * const mImageUnselectedConnected;
  const Image * const mImageSelectedConnected;

  private:
  bool mSelected;
  Image * const mImage;
  FormMachine * const mBelongsTo;
  ConnectorControl * mIsConnectedTo;
  void UpdateImage();
};
//---------------------------------------------------------------------------
struct CinchRedFemaleControl : public ConnectorControl
{
  CinchRedFemaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<CinchRedFemale> cinchFemale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<CinchRedFemale> mCinchFemale;

  public:
  ~CinchRedFemaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct CinchWhiteFemaleControl : public ConnectorControl
{
  CinchWhiteFemaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<CinchWhiteFemale> cinchFemale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<CinchWhiteFemale> mCinchFemale;

  public:
  ~CinchWhiteFemaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct CinchRedMaleControl : public ConnectorControl
{
  CinchRedMaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<CinchRedMale> cinchMale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<CinchRedMale> mCinchMale;

  public:
  ~CinchRedMaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct CinchWhiteMaleControl : public ConnectorControl
{
  CinchWhiteMaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<CinchRedMale> cinchMale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<CinchRedMale> mCinchMale;

  public:
  ~CinchWhiteMaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct DmxFemaleControl : public ConnectorControl
{
  DmxFemaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<DmxFemale> dmxFemale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<DmxFemale> mDmxFemale;

  public:
  ~DmxFemaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct DmxMaleControl : public ConnectorControl
{
  DmxMaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<DmxMale> dmxMale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<DmxMale> mDmxMale;

  public:
  ~DmxMaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct EuroFemaleControl : public ConnectorControl
{
  EuroFemaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<EuroFemale> euroFemale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<EuroFemale> mEuroFemale;

  public:
  ~EuroFemaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct EuroMaleControl : public ConnectorControl
{
  EuroMaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<EuroMale> euroMale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<EuroMale> mEuroMale;

  public:
  ~EuroMaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct JackFemaleControl : public ConnectorControl
{
  JackFemaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<JackFemale> euroFemale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<JackFemale> mJackFemale;

  public:
  ~JackFemaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct JackXlrFemaleControl : public ConnectorControl
{
  JackXlrFemaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<JackXlrFemale> euroFemale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<JackXlrFemale> mJackXlrFemale;

  public:
  ~JackXlrFemaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct JackMaleControl : public ConnectorControl
{
  JackMaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<JackMale> euroFemale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<JackMale> mJackMale;

  public:
  ~JackMaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct Plug220Control : public ConnectorControl
{
  Plug220Control(
    FormMachine * const belongsTo,
    const std::shared_ptr<Plug220> plug220,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<Plug220> mPlug220;

  public:
  ~Plug220Control() {}
  private:
};
//---------------------------------------------------------------------------
struct Socket220Control : public ConnectorControl
{
  Socket220Control(
    FormMachine * const belongsTo,
    const std::shared_ptr<Socket220> socket220,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();


  private:

  std::shared_ptr<Socket220> mSocket220;

  public:
  ~Socket220Control() {}
  private:
};
//---------------------------------------------------------------------------
struct SocketPowerFemaleControl : public ConnectorControl
{
  SocketPowerFemaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<SocketPowerFemale> socketPowerFemale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();


  private:

  std::shared_ptr<SocketPowerFemale> mSocketPowerFemale;

  public:
  ~SocketPowerFemaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct SocketPowerMaleControl : public ConnectorControl
{
  SocketPowerMaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<SocketPowerMale> socketPowerMale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();


  private:

  std::shared_ptr<SocketPowerMale> mSocketPowerMale;

  public:
  ~SocketPowerMaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct SpeakonFemaleControl : public ConnectorControl
{
  SpeakonFemaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<SpeakonFemale> euroFemale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<SpeakonFemale> mSpeakonFemale;

  public:
  ~SpeakonFemaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct SpeakonMaleControl : public ConnectorControl
{
  SpeakonMaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<SpeakonMale> euroFemale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<SpeakonMale> mSpeakonMale;

  public:
  ~SpeakonMaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct XlrFemaleControl : public ConnectorControl
{
  XlrFemaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<XlrFemale> xlrFemale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<XlrFemale> mXlrFemale;

  public:
  ~XlrFemaleControl() {}
  private:
};
//---------------------------------------------------------------------------
struct XlrMaleControl : public ConnectorControl
{
  XlrMaleControl(
    FormMachine * const belongsTo,
    const std::shared_ptr<XlrMale> xlrMale,
    Image * const image);

  const Connector * const GetConnector() const;
  Connector * GetConnector();

  private:

  std::shared_ptr<XlrMale> mXlrMale;

  public:
  ~XlrMaleControl() {}
  private:
};
//---------------------------------------------------------------------------



#endif
