//---------------------------------------------------------------------------
#ifndef UnitFormSimStagecraftSelectH
#define UnitFormSimStagecraftSelectH
//---------------------------------------------------------------------------
#include <vector>

#include <QDialog>

#include "ui/UiFormSimStagecraftSelect.h"
//---------------------------------------------------------------------------
class QPlainTextEdit;
class QTimer;
class SurfaceWidget;
//---------------------------------------------------------------------------
//The screen to select a level in
class FormSimStagecraftSelect : public QDialog, private UiFormSimStagecraftSelect
{
public:
  explicit FormSimStagecraftSelect(QWidget * const parent = nullptr);

protected:
  void keyPressEvent(QKeyEvent * e) override;

private:
  SurfaceWidget * const mSurface;
  QPlainTextEdit * const RichEdit;
  QTimer * const TimerMain;
  int mLevel;
  const int mBorderSize;
  std::vector<Image *> mImages;
  Image * const GetImage(const int value) const;
  void DrawScreen();
  void FormMouseDown(const int x, const int y);
  void FormResize();
  void UpdateText();
};
//---------------------------------------------------------------------------
#endif
