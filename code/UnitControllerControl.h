//---------------------------------------------------------------------------

#ifndef UnitControllerControlH
#define UnitControllerControlH
//---------------------------------------------------------------------------
#include <memory>
//#include "UnitEnumControllerType.h"
//struct Controller;
class FormMachine;

struct Dial;
struct Fader;
struct PressButton;
struct PushButton;
struct TwoSwitch;
struct Image;
//---------------------------------------------------------------------------
//Handles the GUI of a Controller
//An XControl manages the GUI of an X
struct ControllerControl
{
  ControllerControl(FormMachine * const formParent,
    Image * const image);
  //The x and y are the coordinats on mImage itself,
  //independent of its Image::Left and Image::Top properties
  virtual void OnMouseDown(const int x, const int y) = 0;

  protected:
  Image * const mImage;
  FormMachine * const mFormParent;

  public:
  virtual ~ControllerControl() {}
  protected:

};
//---------------------------------------------------------------------------
struct DialControl : public ControllerControl
{
  DialControl(FormMachine * const formParent,
    const std::shared_ptr<Dial> dial,
    Image * const image);

  void OnMouseDown(const int x, const int y);

  private:
  const std::shared_ptr<Dial> mDial;

  public:
  ~DialControl() {}
  private:
};
//---------------------------------------------------------------------------
struct FaderControl : public ControllerControl
{
  FaderControl(FormMachine * const formParent,
    const std::shared_ptr<Fader> fader,
    Image * const image);

  void OnMouseDown(const int x, const int y);

  private:
  const std::shared_ptr<Fader> mFader;

  public:
  ~FaderControl() {}
  private:
};
//---------------------------------------------------------------------------
struct PressButtonControl : public ControllerControl
{
  PressButtonControl(FormMachine * const formParent,
    const std::shared_ptr<PressButton> pressButton,
    Image * const image);

  void OnMouseDown(const int, const int);

  private:

  const std::shared_ptr<PressButton> mPressButton;
  const Image * const mImageIn;
  const Image * const mImageOut;

  public:
  ~PressButtonControl() {}
  private:
};
//---------------------------------------------------------------------------
// TabButtonControl has been moved to UnitTapButtonControl.h
//---------------------------------------------------------------------------
struct TwoSwitchControl : public ControllerControl
{
  TwoSwitchControl(FormMachine * const formParent,
    const std::shared_ptr<TwoSwitch> twoSwitch,
    Image * const image);

  void OnMouseDown(const int x, const int y);

  private:

  const std::shared_ptr<TwoSwitch> mTwoSwitch;
  const Image * const mImageOn;
  const Image * const mImageOff;

  public:
  ~TwoSwitchControl() {}
  private:
};
//---------------------------------------------------------------------------

#endif
