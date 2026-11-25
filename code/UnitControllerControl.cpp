//---------------------------------------------------------------------------

#include <cassert>
#include <cmath>
#include "UnitController.h"
#include "UnitControllerControl.h"
#include "UnitFunctions.h"
#include "UnitFormSprites.h"
#include "UnitFormMachine.h"
#include "UnitImage.h"
//---------------------------------------------------------------------------
ControllerControl::ControllerControl(
  FormMachine * const formParent,
  Image * const image)
  : mFormParent(formParent),
    mImage(image)
{
  assert(formParent!=0);
  assert(mImage!=0);
}
//---------------------------------------------------------------------------
DialControl::DialControl(FormMachine * const formParent,
  const std::shared_ptr<Dial> dial,
  Image * const image)
  : ControllerControl(formParent,image),mDial(dial)
{
  assert(mDial.get()!=0);
}
//---------------------------------------------------------------------------
void DialControl::OnMouseDown(const int x, const int y)
{
  const int midX = mImage->width / 2;
  const int midY = mImage->height / 2;
  const double angle
    = GetAngle( static_cast<double>(x - midX),
        static_cast<double>(y - midY));
  const double ray = static_cast<double>(std::min( midX, midY ));
  const double distance
    = GetDistance(
      static_cast<double>(x - midX),
      static_cast<double>(y - midY) );
  if (distance > 0.25 * ray && (angle < 0.75 * M_PI || angle > 1.25 * M_PI ) )
  {
    DrawDial(mImage, x, y, Qt::white);
    const double position =
      ( angle < 0.75 * M_PI
        ? 0.5 + (0.5 * (angle / (0.75 * M_PI))) //Topright
        : 0.5 * (angle - (1.25 * M_PI)) / (0.75 * M_PI) //Topleft
      );
    assert(position >= 0.0);
    assert(position <= 1.0);
    mDial->SetPosition(position);
    //Notify the parent of this event
    mFormParent->OnControllerClick();
  }
}
//---------------------------------------------------------------------------
FaderControl::FaderControl(FormMachine * const formParent,
  const std::shared_ptr<Fader> fader,
  Image * const image)
  : ControllerControl(formParent,image), mFader(fader)
{
  assert(mFader.get()!=0);
}
//---------------------------------------------------------------------------
void FaderControl::OnMouseDown(const int, const int y)
{
  DrawFader(mImage,y);
  //Top of fader is position 1.0,
  //Bottom of fader is position 0.0
  const double position = 1.0 - static_cast<double>(y)
    / static_cast<double>(mImage->height);
  assert(position >= 0.0);
  assert(position <= 1.0);
  mFader->SetPosition(position);
  //Notify the parent of this event
  mFormParent->OnControllerClick();
}
//---------------------------------------------------------------------------
PressButtonControl::PressButtonControl(FormMachine * const formParent,
  const std::shared_ptr<PressButton> pressButton,
  Image * const image)
  : ControllerControl(formParent,image),
    mPressButton(pressButton),
    mImageIn(Sprites()->ImagePressButtonIn),
    mImageOut(Sprites()->ImagePressButtonOut)
{
  assert(mPressButton.get() != 0);
  assert(mImage != 0);
  assert(mImageIn != 0);
  assert(mImageOut != 0);
  assert(mImageIn->height == mImageOut->height);
  assert(mImageIn->picture.height() == mImageOut->picture.height());
}
//---------------------------------------------------------------------------
void PressButtonControl::OnMouseDown(const int, const int y)
{
  assert(mImage->height == mImageOut->height);
  assert(mImageIn->height == mImageOut->height);
  assert(mImageIn->picture.height() == mImageOut->picture.height());

  mPressButton->Press();

  if (mPressButton->IsIn() == true)
  {
    mImage->AssignPicture(mImageIn);
  }
  else
  {
    mImage->AssignPicture(mImageOut);
  }

  //Notify the parent of this event
  mFormParent->OnControllerClick();
}
//---------------------------------------------------------------------------
TwoSwitchControl::TwoSwitchControl(FormMachine * const formParent,
  const std::shared_ptr<TwoSwitch> twoSwitch,
  Image * const image)
  : ControllerControl(formParent,image),
    mTwoSwitch(twoSwitch),
    mImageOn(Sprites()->ImageTwoSwitchOn),
    mImageOff(Sprites()->ImageTwoSwitchOff)
{
  assert(mTwoSwitch.get() != 0);
  assert(mImage != 0);
  assert(mImageOn != 0);
  assert(mImageOff != 0);
  assert(mImageOn->height == mImageOff->height);
  assert(mImageOn->picture.height() == mImageOff->picture.height());
}
//---------------------------------------------------------------------------
void TwoSwitchControl::OnMouseDown(const int, const int y)
{
  assert(mImage->height == mImageOff->height);
  assert(mImageOn->height == mImageOff->height);
  assert(mImageOn->picture.height() == mImageOff->picture.height());
  const int height = mImage->height;

  //Lower half of image, turn two-switch to on
  if (y > height / 2)
  {
    mImage->AssignPicture(mImageOn);
    mTwoSwitch->SwitchOn();
  }
  else if (y < height / 2)
  {
    //Turn two-switch to off
    mImage->AssignPicture(mImageOff);
    mTwoSwitch->SwitchOff();
  }
  //Notify the parent of this event
  mFormParent->OnControllerClick();
}
//---------------------------------------------------------------------------







