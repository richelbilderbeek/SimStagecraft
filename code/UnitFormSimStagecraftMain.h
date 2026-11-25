//---------------------------------------------------------------------------
#ifndef UnitFormSimStagecraftMainH
#define UnitFormSimStagecraftMainH
//---------------------------------------------------------------------------
#include <memory>
#include <vector>

#include <QDialog>
#include <QRect>

#include "UnitEnumDisplayMode.h"
#include "UnitFormMachine.h"
#include "ui/UiFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
class QCheckBox;
class QPushButton;
class QTimer;
class QWidget;
class SurfaceWidget;
struct ConnectorControl;
//---------------------------------------------------------------------------
//The screen the game is played in
class FormSimStagecraftMain : public QDialog, private UiFormSimStagecraftMain
{
public:
  FormSimStagecraftMain(QWidget * const parent, const int selectedLevel);
  ~FormSimStagecraftMain();

  typedef std::vector<std::shared_ptr<FormMachine> >::iterator MachineIterator;
  typedef std::vector<std::shared_ptr<FormMachine> >::const_iterator ConstMachineIterator;
  void DrawScreen();
  void OnConnectorClick(ConnectorControl * const connector);
  void OnControllerClick();

protected:
  void keyPressEvent(QKeyEvent * e) override;

private:
  //Widgets
  SurfaceWidget * const mSurface;
  QWidget * const PanelBottom;
  QCheckBox * const CheckBoxAutoMove;
  QPushButton * const ButtonView;
  QPushButton * const ButtonConnect;
  QPushButton * const ButtonUse;
  QPushButton * const ButtonQuit;
  QTimer * const TimerMain;
  //Variables
  std::vector<std::shared_ptr<FormMachine> > mMachines;
  ConnectorControl * mConnector1;
  ConnectorControl * mConnector2;
  EnumDisplayMode mDisplayMode;
  FormMachine * mDragMachine;
  int mDragX;
  int mDragY;
  //Methods
  void PaintBackground();
  void SetDisplayModes(const EnumDisplayMode mode);
  void UpdateBuffers();
  void AutoMove();
  const int GetDrawingSurfaceHeight() const;
  const int GetDrawingSurfaceWidth() const;
  const bool OnFormMachine(const int x, const int y,
    const FormMachine * const form) const;
  void TileMachines();
  void TimerMainTimer();
  void FormMouseDown(const int x, const int y);
  void FormMouseMove(const int x, const int y);
  void FormMouseUp(const int x, const int y);
  void FormResize();
};
//---------------------------------------------------------------------------
#endif
