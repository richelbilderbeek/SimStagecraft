//---------------------------------------------------------------------------

#ifndef UnitControllerH
#define UnitControllerH
//---------------------------------------------------------------------------
struct Fader;
//---------------------------------------------------------------------------
struct Controller
{
  protected:
  public:
  virtual ~Controller() {}
  protected:

  private:
};
//---------------------------------------------------------------------------
struct Dial : public Controller
{
  Dial(const double position = 0.0);
  const double GetPosition() const { return mPosition; }
  const double GetRelPosition() const;
  void SetPosition(const double position);

  const double GetMinPosition() const { return 0.0; }
  const double GetMaxPosition() const { return 1.0; }

  private:

  double mPosition;

  public:
  virtual ~Dial() {}
  private:
};
//---------------------------------------------------------------------------
struct Fader : public Controller
{
  Fader(const double position = 0.0);
  const double GetPosition() const { return mPosition; }
  void SetPosition(const double position);
  const double GetMinPosition() const { return 0.0; }
  const double GetMaxPosition() const { return 1.0; }
  const double GetRelPosition() const;

  private:
  double mPosition;

  public:
  virtual ~Fader() {}
  private:
};
//---------------------------------------------------------------------------
struct PushButton : public Controller
{
  private:
  public:
  virtual ~PushButton() {}
  private:
};
//---------------------------------------------------------------------------
struct PressButton : public Controller
{
  PressButton() : mIn(false) {}

  const bool IsIn() const { return mIn; }
  void Press()  { mIn = !mIn; }

  private:
  bool mIn;

  public:
  virtual ~PressButton() {}
  private:

};
//---------------------------------------------------------------------------
//TapButton has been moved to UnitTabButton.h
//---------------------------------------------------------------------------
struct TwoSwitch : public Controller
{
  TwoSwitch() : mOn(false) {}

  const bool IsOn() const { return mOn; }
  void SwitchOn()  { mOn = true; }
  void SwitchOff() { mOn = false; }

  private:
  bool mOn;

  public:
  virtual ~TwoSwitch() {}
  private:

};
//---------------------------------------------------------------------------

#endif
