//---------------------------------------------------------------------------
#ifndef UnitFormSimStagecraftMenuH
#define UnitFormSimStagecraftMenuH
//---------------------------------------------------------------------------
#include <vector>

#include <QDialog>

#include "ui/UiFormSimStagecraftMenu.h"
//---------------------------------------------------------------------------
class QTimer;
class SurfaceWidget;
//---------------------------------------------------------------------------
//The first screen: start, about or quit
class FormSimStagecraftMenu : public QDialog, private UiFormSimStagecraftMenu
{
public:
  explicit FormSimStagecraftMenu(QWidget * const parent = nullptr);

protected:
  void keyPressEvent(QKeyEvent * e) override;

private:
  SurfaceWidget * const mSurface;
  QTimer * const TimerBackground;
  const std::vector<Image*> mImages;
  const int mBorderSize;

  void DrawScreen();
  void FormMouseDown(const int x, const int y);
  void FormResize();
  const std::vector<Image*> GetImages() const;
};
//---------------------------------------------------------------------------
#endif
