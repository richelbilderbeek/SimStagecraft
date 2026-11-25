//---------------------------------------------------------------------------

#include <cassert>
#include "UnitTapButtonControl.h"
//---------------------------------------------------------------------------
/*
template <class T>
TapButtonControl<T>::TapButtonControl(FormMachine * const formParent,
  const std::shared_ptr<TapButton<T> > tapButton,
  Image * const image)
  : ControllerControl(formParent,image),
    mTapButton(tapButton),
    mImage(image)
{
  assert(mTapButton.get() != 0);
  assert(mImage != 0);
}
//---------------------------------------------------------------------------
template <class T>
void TapButtonControl<T>::OnMouseDown(const int, const int y)
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
    mTapButton->Tap();
    //Notify the parent of this event
    mFormParent->OnControllerClick();
  }
}
//---------------------------------------------------------------------------
*/
