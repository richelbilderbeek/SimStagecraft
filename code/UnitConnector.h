//---------------------------------------------------------------------------

#ifndef UnitConnectorH
#define UnitConnectorH
//---------------------------------------------------------------------------
#include <memory>
#include "UnitMachine.h"
//---------------------------------------------------------------------------
// Every Machine has at least one Connector
// A Connector belongs to a Machine and is of a certain type
struct Connector
{
  Connector(const Machine * const belongsTo);

  void Connect(const Connector * const otherConnector);
  void Disconnect();
  const Connector * const GetConnectedTo() const;

  virtual const bool CanConnect(
    const Connector * const otherConnector) const = 0;

  const Machine * const mBelongsTo;
  const bool IsConnected() const { return (mConnectedTo!=0); }

  protected:
  public:
  virtual ~Connector() {}
  protected:


  private:
  const Connector * mConnectedTo;

};
//---------------------------------------------------------------------------
struct CinchRedFemale : public Connector
{
  CinchRedFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~CinchRedFemale() {}
  private:

};
//---------------------------------------------------------------------------
struct CinchRedMale : public Connector
{
  CinchRedMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~CinchRedMale() {}
  private:

};
//---------------------------------------------------------------------------
struct CinchWhiteFemale : public Connector
{
  CinchWhiteFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~CinchWhiteFemale() {}
  private:

};
//---------------------------------------------------------------------------
struct CinchWhiteMale : public Connector
{
  CinchWhiteMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~CinchWhiteMale() {}
  private:

};
//---------------------------------------------------------------------------
struct DmxFemale : public Connector
{
  DmxFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~DmxFemale() {}
  private:

};
//---------------------------------------------------------------------------
struct DmxMale : public Connector
{
  DmxMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~DmxMale() {}
  private:

};
//---------------------------------------------------------------------------
struct EuroFemale : public Connector
{
  EuroFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~EuroFemale() {}
  private:

};
//---------------------------------------------------------------------------
struct EuroMale : public Connector
{
  EuroMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~EuroMale() {}
  private:

};
//---------------------------------------------------------------------------
// InternalConnection is a soldered connection internal to a machine
// For example, the connection between a power LED and a triplet
struct InternalConnection : public Connector
{
  InternalConnection(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~InternalConnection() {}
  private:

};
//---------------------------------------------------------------------------
struct JackFemale : public Connector
{
  JackFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~JackFemale() {}
  private:

};
//---------------------------------------------------------------------------
//Combo connector of both jack female and XLR female
struct JackXlrFemale : public Connector
{
  JackXlrFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~JackXlrFemale() {}
  private:

};
//---------------------------------------------------------------------------
struct JackMale : public Connector
{
  JackMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~JackMale() {}
  private:
};
//---------------------------------------------------------------------------
struct Plug220 : public Connector
{
  Plug220(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~Plug220() {}
  private:

};
//---------------------------------------------------------------------------
struct SpeakonFemale : public Connector
{
  SpeakonFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~SpeakonFemale() {}
  private:

};
//---------------------------------------------------------------------------
struct SpeakonMale : public Connector
{
  SpeakonMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~SpeakonMale() {}
  private:
};
//---------------------------------------------------------------------------
struct SocketPowerMale : public Connector
{
  SocketPowerMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~SocketPowerMale() {}
  private:

};
//---------------------------------------------------------------------------
struct Socket220 : public Connector
{
  Socket220(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~Socket220() {}
  private:

};
//---------------------------------------------------------------------------
struct SocketPowerFemale : public Connector
{
  SocketPowerFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~SocketPowerFemale() {}
  private:
};
//---------------------------------------------------------------------------
struct XlrFemale : public Connector
{
  XlrFemale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~XlrFemale() {}
  private:

};
//---------------------------------------------------------------------------
struct XlrMale : public Connector
{
  XlrMale(const Machine * const belongsTo) : Connector(belongsTo) {}
  const bool CanConnect(
    const Connector * const otherConnector) const;

  private:
  public:
  ~XlrMale() {}
  private:

};
//---------------------------------------------------------------------------
#endif
