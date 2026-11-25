//---------------------------------------------------------------------------

#ifndef UnitTapButtonControlH
#define UnitTapButtonControlH
//---------------------------------------------------------------------------
#include <cassert>
#include <cmath>
#include <memory>
#include <algorithm>
#include "UnitControllerControl.h"
#include "UnitFormMachine.h"
#include "UnitFunctions.h"
#include "UnitImage.h"
#include "UnitTapButton.h"
//---------------------------------------------------------------------------
template <class T>
struct TapButtonControl : public ControllerControl
{
  TapButtonControl(FormMachine * const formParent,
    const std::shared_ptr<TapButton<T> > tapButton,
    Image * const image)
    : ControllerControl(formParent,image),
      mTapButton(tapButton),
      mImage(image)
  {
    assert(mTapButton.get() != 0);
    assert(mImage != 0);
  }

  void OnMouseDown(const int x, const int y)
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
    if (distance < ray )
    {
      mTapButton->Tap();
      //Notify the parent of this event
      mFormParent->OnControllerClick();
    }
  }

  private:

  const std::shared_ptr<TapButton<T> > mTapButton;
  const Image * const mImage;

  public:
  ~TapButtonControl() {}
  private:
};
//---------------------------------------------------------------------------
#endif
