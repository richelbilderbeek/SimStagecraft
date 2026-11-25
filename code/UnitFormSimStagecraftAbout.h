//---------------------------------------------------------------------------
#ifndef UnitFormSimStagecraftAboutH
#define UnitFormSimStagecraftAboutH
//---------------------------------------------------------------------------
#include <QDialog>

#include "ui/UiFormSimStagecraftAbout.h"
//---------------------------------------------------------------------------
class QTimer;
class SurfaceWidget;
//---------------------------------------------------------------------------
class FormSimStagecraftAbout : public QDialog, private UiFormSimStagecraftAbout
{
public:
  explicit FormSimStagecraftAbout(QWidget * const parent = nullptr);

private:
  SurfaceWidget * const mSurface;
  QTimer * const TimerMain;
  QTimer * const TimerColor;
  int mDr;
  int mDg;
  int mDb;
  int mTick;
  void DrawBackground();
  void TimerMainTimer();
  void TimerColorTimer();
};
//---------------------------------------------------------------------------
#endif
