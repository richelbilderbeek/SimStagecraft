//---------------------------------------------------------------------------
#include <algorithm>
#include <cassert>
#include <cmath>

#include <QCheckBox>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

#include "UnitCreateMachines.h"
#include "UnitConnectorControl.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
#include "UnitImage.h"
#include "UnitSurfaceWidget.h"
//---------------------------------------------------------------------------
namespace {

//A rectangle like the VCL TRect, where Right and Bottom are
//one pixel beyond the rectangle
struct Box
{
  int Left;
  int Top;
  int Right;
  int Bottom;
};

const bool InRect(const int x, const int y, const Box& r)
{
  return (x >= r.Left && x < r.Right && y >= r.Top && y < r.Bottom);
}

void MoveAway(Box& r1, Box& r2, const int width, const int height)
{
  int dx1 = 0;
  int dy1 = 0;
  int dx2 = 0;
  int dy2 = 0;
  //No collision
  if (r1.Left   < 0) ++dx1;
  if (r1.Top    < 0) ++dy1;
  if (r1.Right  > width ) --dx1;
  if (r1.Bottom > height) --dy1;
  if (r2.Left   < 0) ++dx2;
  if (r2.Top    < 0) ++dy2;
  if (r2.Right  > width ) --dx2;
  if (r2.Bottom > height) --dy2;

  if (!( r1.Right  < r2.Left || r1.Left > r2.Right
    || r1.Bottom < r2.Top  || r1.Top  > r2.Bottom))
  {
    if (InRect(r1.Left ,r1.Top   ,r2)==true) { ++dx1; ++dy1; --dx2; --dy2;}
    if (InRect(r1.Right,r1.Top   ,r2)==true) { --dx1; ++dy1; ++dx2; --dy2;}
    if (InRect(r1.Left ,r1.Bottom,r2)==true) { ++dx1; --dy1; --dx2; ++dy2;}
    if (InRect(r1.Right,r1.Bottom,r2)==true) { --dx1; --dy1; ++dx2; ++dy2;}
    //If all 4 edges are collision
    if (dx1 == 0 && dy1 == 0)
    {
      ++dx1;
      ++dy1;
      --dx2;
      --dy2;
    }
  }
  r1.Left   += dx1;
  r1.Right  += dx1;
  r1.Top    += dy1;
  r1.Bottom += dy1;
  r2.Left   += dx2;
  r2.Right  += dx2;
  r2.Top    += dy2;
  r2.Bottom += dy2;
}

void PlaceInCenter(FormMachine * const form, const QRect& rect)
{
  assert(form!=0);
  form->Left = rect.left() + (rect.width()  / 2) - (form->ClientWidth  / 2);
  form->Top  = rect.top()  + (rect.height() / 2) - (form->ClientHeight / 2);
}

} //~namespace
//---------------------------------------------------------------------------
FormSimStagecraftMain::FormSimStagecraftMain(
  QWidget * const parent, const int selectedLevel)
  : QDialog(parent),
    mSurface(new SurfaceWidget(this)),
    PanelBottom(new QWidget(this)),
    CheckBoxAutoMove(new QCheckBox("AutoMove",PanelBottom)),
    ButtonView(new QPushButton("1) View",PanelBottom)),
    ButtonConnect(new QPushButton("2) Connect",PanelBottom)),
    ButtonUse(new QPushButton("3) Use",PanelBottom)),
    ButtonQuit(new QPushButton(PanelBottom)),
    TimerMain(new QTimer(this)),
    mConnector1(0), mConnector2(0), //Human, 1-based counting :-)
    mDisplayMode(modeView),
    mDragMachine(0),
    mDragX(0),
    mDragY(0)
{
  setWindowTitle(QString::fromUtf8(DesignCaption));
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  resize(DesignClientWidth,DesignClientHeight);

  //Bottom panel: AutoMove, the three display mode buttons and quit
  {
    for (QPushButton * const button: { ButtonView, ButtonConnect, ButtonUse })
    {
      button->setCheckable(true);
      button->setAutoExclusive(true);
      button->setFocusPolicy(Qt::NoFocus);
    }
    ButtonView->setChecked(true);
    CheckBoxAutoMove->setFocusPolicy(Qt::NoFocus);
    ButtonQuit->setIcon(QPixmap::fromImage(ImageQuit->Graphic()));
    ButtonQuit->setIconSize(ImageQuit->picture.size());
    ButtonQuit->setFlat(true);
    ButtonQuit->setFocusPolicy(Qt::NoFocus);
    ButtonQuit->setToolTip("Quit");
    QHBoxLayout * const layout = new QHBoxLayout(PanelBottom);
    layout->setContentsMargins(4,4,4,4);
    layout->setSpacing(4);
    layout->addWidget(CheckBoxAutoMove);
    layout->addWidget(ButtonView,1);
    layout->addWidget(ButtonConnect,1);
    layout->addWidget(ButtonUse,1);
    layout->addWidget(ButtonQuit);
  }
  {
    QVBoxLayout * const layout = new QVBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    layout->addWidget(mSurface,1);
    layout->addWidget(PanelBottom);
  }

  connect(ButtonView, &QPushButton::clicked, this,
    [this]() { SetDisplayModes(modeView); DrawScreen(); });
  connect(ButtonConnect, &QPushButton::clicked, this,
    [this]() { SetDisplayModes(modeConnect); DrawScreen(); });
  connect(ButtonUse, &QPushButton::clicked, this,
    [this]() { SetDisplayModes(modeUse); DrawScreen(); });
  connect(ButtonQuit, &QPushButton::clicked, this, &QDialog::close);
  connect(TimerMain, &QTimer::timeout, this, [this]() { TimerMainTimer(); });

  mSurface->buffer = ImageBuffer;
  mSurface->onMouseDown = [this](int x, int y) { FormMouseDown(x,y); };
  mSurface->onMouseMove = [this](int x, int y) { FormMouseMove(x,y); };
  mSurface->onMouseUp   = [this](int x, int y) { FormMouseUp(x,y); };
  mSurface->onResize    = [this]() { FormResize(); };

  ImageBuffer->left = 0;
  ImageBuffer->top = 0;

  mMachines = CreateMachines(this,selectedLevel);

  FormResize();
  SetDisplayModes(modeView);
  UpdateBuffers();
  DrawScreen();

  TimerMain->start(100);
  setWindowState(Qt::WindowMaximized);
}
//---------------------------------------------------------------------------
FormSimStagecraftMain::~FormSimStagecraftMain()
{
  TimerMain->stop();
  //Machines must be deleted before the widgets
  mMachines.clear();
}
//---------------------------------------------------------------------------
const int FormSimStagecraftMain::GetDrawingSurfaceHeight() const
{
  return std::max(1,mSurface->height());
}
//---------------------------------------------------------------------------
const int FormSimStagecraftMain::GetDrawingSurfaceWidth() const
{
  return std::max(1,mSurface->width());
}
//---------------------------------------------------------------------------
void FormSimStagecraftMain::DrawScreen()
{
  //Draw background on buffer (or clear buffer otherwise)
  DrawImage(ImageBuffer,0,0,ImageBackground);
  //Draw all Machines
  for (const std::shared_ptr<FormMachine>& machine: mMachines)
  {
    DrawImage(ImageBuffer,machine->Left,machine->Top,machine->ImageBuffer);
  }
  //Draw buffer to screen
  mSurface->update();
}
//---------------------------------------------------------------------------
void FormSimStagecraftMain::SetDisplayModes(const EnumDisplayMode mode)
{
  mDisplayMode = mode;
  //Set the DisplayMode of all FormMachines
  for (const std::shared_ptr<FormMachine>& machine: mMachines)
  {
    machine->SetDisplayMode(mode);
  }
  UpdateBuffers(); //Needed for non-active machines (e.g. Par64 and WallSocket220)
}
//---------------------------------------------------------------------------
void FormSimStagecraftMain::UpdateBuffers()
{
  for (const std::shared_ptr<FormMachine>& machine: mMachines)
  {
    machine->UpdateBuffer();
  }
}
//---------------------------------------------------------------------------
void FormSimStagecraftMain::PaintBackground()
{
  PaintWavyBackground(ImageBackground);
}
//---------------------------------------------------------------------------
void FormSimStagecraftMain::TimerMainTimer()
{
  if (CheckBoxAutoMove->isChecked()) AutoMove();
  DrawScreen();
}
//---------------------------------------------------------------------------
void FormSimStagecraftMain::keyPressEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_A:
      CheckBoxAutoMove->setChecked(!CheckBoxAutoMove->isChecked());
      break;
    case Qt::Key_V: case Qt::Key_1: case Qt::Key_F1:
      ButtonView->click();
      break;
    case Qt::Key_C: case Qt::Key_2: case Qt::Key_F2:
      ButtonConnect->click();
      break;
    case Qt::Key_U: case Qt::Key_3: case Qt::Key_F3:
      ButtonUse->click();
      break;
    case Qt::Key_Q: case Qt::Key_0: case Qt::Key_F10: case Qt::Key_Escape:
      close();
      break;
    default:
      QDialog::keyPressEvent(e);
  }
}
//---------------------------------------------------------------------------
//Children forms will call this method if a connector is clicked.
//This method return if the connector is selected or not
//The child forms know if the connector is connected or not
void FormSimStagecraftMain::OnConnectorClick(
  ConnectorControl * const connector)
{
  assert(connector != 0);
  if (mConnector1 == connector)
  {
    //Unselect
    mConnector1->Unselect();
    mConnector1= 0;
  }
  else if (mConnector2 == connector)
  {
    //Disconnect
    mConnector2->Unselect();
    mConnector2= 0;
  }
  else if ( mConnector1 && mConnector2 != 0)
  {
    assert(mConnector2 != connector); //Assume no self-connection
    mConnector1 = connector;
    mConnector1->Select();
    if ( mConnector1->IsConnected() == false
      && mConnector2->IsConnected() == false)
    {
      //A connection!
      // (Note: if connection is invalid, no actual connection takes place)
      mConnector1->Connect(mConnector2);
      mConnector2->Connect(mConnector1);
      mConnector1->Unselect();
      mConnector2->Unselect();
      mConnector1= 0;
      mConnector2= 0;
    }
    else if ( mConnector1->IsConnectedTo(mConnector2) == true
           && mConnector2->IsConnectedTo(mConnector2) == true)
    {
      //Unconnection
      mConnector1->Disconnect();
      mConnector2->Disconnect();
      mConnector1->Unselect();
      mConnector2->Unselect();
      mConnector1= 0;
      mConnector2= 0;
    }
    else
    {
      //Use selected two different things
      //Leave both selected
    }
  }
  else if ( mConnector1 != 0 && mConnector2 == 0)
  {
    assert(mConnector2 != connector); //Assume no self-connection
    mConnector2 = connector;
    mConnector2->Select();
    if ( mConnector1->IsConnected() == false
      && mConnector2->IsConnected() == false)
    {
      assert( mConnector1->CanConnect(mConnector2)
        == mConnector2->CanConnect(mConnector1)
        && "If A fits (not) in B, B fits (not) into A");
      if (mConnector1->CanConnect(mConnector2)==true)
      {
        //A connection!
        mConnector1->Connect(mConnector2);
        assert(mConnector1->IsConnected()==true);
        assert(mConnector2->IsConnected()==true);
        mConnector2->Connect(mConnector1);
        assert(mConnector1->IsConnectedTo(mConnector2)==true);
        assert(mConnector2->IsConnectedTo(mConnector1)==true);
      }
    }
    else if ( mConnector1->IsConnectedTo(mConnector2) == true
           && mConnector2->IsConnectedTo(mConnector1) == true)
    {
      //Unconnection
      mConnector1->Disconnect();
      mConnector2->Disconnect();
      assert(mConnector1->IsConnected()==false);
      assert(mConnector2->IsConnected()==false);
    }
    else
    {
      //Use selected two different things
      //Leave both selected
    }
    mConnector1->Unselect();
    mConnector2->Unselect();
    mConnector1 = 0;
    mConnector2 = 0;
  }
  else
  {
    assert(mConnector1 == 0 && mConnector2 == 0);
    mConnector1 = connector;
    mConnector1->Select();
  }
  //Update the buffers to show the new state
  UpdateBuffers();
}
//---------------------------------------------------------------------------
void FormSimStagecraftMain::OnControllerClick()
{
  UpdateBuffers(); //Refreshes all FormMachines
}
//---------------------------------------------------------------------------
const bool FormSimStagecraftMain::OnFormMachine(const int x, const int y,
  const FormMachine * const form) const
{
  return (
       x >= form->Left
    && x  < form->Left + form->ClientWidth
    && y >= form->Top
    && y  < form->Top + form->ClientHeight);
}
//---------------------------------------------------------------------------
void FormSimStagecraftMain::FormMouseDown(const int X, const int Y)
{
  const int nFormMachines = mMachines.size();
  for (int i=nFormMachines-1; i!=-1; --i)
  {
    if (OnFormMachine(X,Y,mMachines[i].get())==true)
    {
      //Cursor is on the top window
      const int formX = X - mMachines[i]->Left;
      const int formY = Y - mMachines[i]->Top;
      const int borderSize = FormMachine::mBorderSize;
      //Dragging?
      if ( formX < borderSize
        || formX > mMachines[i]->ClientWidth - borderSize
        || formY < borderSize
        || formY > mMachines[i]->ClientHeight - borderSize)
      {
        //Start dragging
        mDragMachine = mMachines[i].get();
        mDragX = X;
        mDragY = Y;
        //Make dragged machine appear on top
        //by moving it to the end of the std::vector
        std::rotate(mMachines.begin() + i, mMachines.begin() + i + 1, mMachines.end());
        mSurface->setCursor(Qt::ClosedHandCursor);
        return;
      }
      else
      {
        mMachines[i]->OnMouseDown(formX,formY);
        return;
      }
    }
  }
}
//---------------------------------------------------------------------------
void FormSimStagecraftMain::FormMouseMove(const int X, const int Y)
{
  if (mDragMachine != 0)
  {
    const int dX = X - mDragX;
    const int dY = Y - mDragY;
    mDragMachine->Left += dX;
    mDragMachine->Top  += dY;
    mDragX = X;
    mDragY = Y;
    mSurface->setCursor(Qt::ClosedHandCursor);
  }
  else
  {
    //Can drag?
    const int nFormMachines = mMachines.size();
    for (int i=nFormMachines-1; i!=-1; --i)
    {
      if (OnFormMachine(X,Y,mMachines[i].get())==true)
      {
        //We are on the top windows
        const int formX = X - mMachines[i]->Left;
        const int formY = Y - mMachines[i]->Top;
        const int borderSize = FormMachine::mBorderSize;
        //Dragging?
        if ( formX < borderSize
          || formX > mMachines[i]->ClientWidth - borderSize
          || formY < borderSize
          || formY > mMachines[i]->ClientHeight - borderSize)
        {
          mSurface->setCursor(Qt::OpenHandCursor);
          return;
        }
        else
        {
          mSurface->setCursor(Qt::ArrowCursor);
          return;
        }
      }
    }
    mSurface->setCursor(Qt::ArrowCursor);
  }
}
//---------------------------------------------------------------------------
void FormSimStagecraftMain::FormMouseUp(const int, const int)
{
  mDragMachine = 0;
  mSurface->setCursor(Qt::ArrowCursor);
}
//---------------------------------------------------------------------------
void FormSimStagecraftMain::FormResize()
{
  SetPictureSize(ImageBuffer, GetDrawingSurfaceWidth(), GetDrawingSurfaceHeight());
  SetPictureSize(ImageBackground, GetDrawingSurfaceWidth(), GetDrawingSurfaceHeight());
  //Repaint the screen at its new size
  PaintBackground();
  TileMachines();
  DrawScreen();
}
//---------------------------------------------------------------------------
void FormSimStagecraftMain::TileMachines()
{
  if (mMachines.empty() == true) return;
  const int nMachines = mMachines.size();
  const int nCols = 1 + static_cast<int>(
    std::sqrt( static_cast<double>(nMachines - 1) ) );
  const int nRows = static_cast<int>(std::sqrt(
    static_cast<double>(nMachines)
    + std::sqrt( static_cast<double>(nMachines) ) ) );
  const int dx = this->GetDrawingSurfaceWidth()  / nCols;
  const int dy = this->GetDrawingSurfaceHeight() / nRows;
  int count = 0;
  for (const std::shared_ptr<FormMachine>& machine: mMachines)
  {
    const int x = (count % nCols) * dx;
    const int y = (count / nCols) * dy;
    PlaceInCenter(machine.get(), QRect(x,y,dx,dy));
    ++count;
  }
}
//---------------------------------------------------------------------------
void FormSimStagecraftMain::AutoMove()
{
  const int nForms = mMachines.size();
  for (int i=0; i!=nForms; ++i)
  {
    for (int j=0; j!=i; ++j)
    {
      Box r1;
      r1.Left   = mMachines[i]->Left;
      r1.Top    = mMachines[i]->Top;
      r1.Right  = r1.Left + mMachines[i]->ClientWidth;
      r1.Bottom = r1.Top  + mMachines[i]->ClientHeight;
      Box r2;
      r2.Left   = mMachines[j]->Left;
      r2.Top    = mMachines[j]->Top;
      r2.Right  = r2.Left + mMachines[j]->ClientWidth;
      r2.Bottom = r2.Top  + mMachines[j]->ClientHeight;
      MoveAway(r1,r2,GetDrawingSurfaceWidth(),GetDrawingSurfaceHeight());
      mMachines[i]->Left = r1.Left;
      mMachines[i]->Top  = r1.Top;
      mMachines[j]->Left = r2.Left;
      mMachines[j]->Top  = r2.Top;
    }
  }
}
//---------------------------------------------------------------------------
