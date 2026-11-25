//---------------------------------------------------------------------------
#include <cassert>
#include <stdexcept>

#include <QKeyEvent>
#include <QPlainTextEdit>
#include <QStringList>
#include <QTimer>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "UnitFormSimStagecraftMain.h"
#include "UnitFormSimStagecraftSelect.h"
#include "UnitImage.h"
#include "UnitShowModal.h"
#include "UnitSurfaceWidget.h"
//---------------------------------------------------------------------------
FormSimStagecraftSelect::FormSimStagecraftSelect(QWidget * const parent)
  : QDialog(parent),
    mSurface(new SurfaceWidget(this)),
    RichEdit(new QPlainTextEdit(this)),
    TimerMain(new QTimer(this)),
    mLevel(1),
    mBorderSize(8)
{
  setWindowTitle(QString::fromUtf8(DesignCaption));
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  setStyleSheet("QDialog { background-color: black; }");
  RichEdit->setReadOnly(true);
  RichEdit->setFocusPolicy(Qt::NoFocus);
  RichEdit->setFixedHeight(185);
  QVBoxLayout * const layout = new QVBoxLayout(this);
  layout->setContentsMargins(0,0,0,mBorderSize);
  layout->addWidget(mSurface,1);
  {
    QHBoxLayout * const textLayout = new QHBoxLayout;
    textLayout->setContentsMargins(mBorderSize,0,mBorderSize,0);
    textLayout->addWidget(RichEdit);
    layout->addLayout(textLayout);
  }
  resize(DesignClientWidth,DesignClientHeight);

  mImages = {
    ImageSelectLevel,
    ImageArrowLeft,
    ImageArrowRight,
    ImageSelectLeft,
    ImageSelectRight,
    ImageStart,
    ImageQuit,
    ImageLed1,
    ImageLed2,
    ImageLed3,
    ImageLed4
  };

  ImageBuffer->left = mBorderSize;
  ImageBuffer->top = mBorderSize;
  mSurface->buffer = ImageBuffer;
  mSurface->onMouseDown = [this](int x, int y) { FormMouseDown(x,y); };
  mSurface->onResize = [this]() { FormResize(); };
  connect(TimerMain, &QTimer::timeout, this,
    [this]() { TickBackground(ImageBackground); DrawScreen(); });

  FormResize();
  UpdateText();
  DrawScreen();
  TimerMain->start(50);
}
//---------------------------------------------------------------------------
void FormSimStagecraftSelect::DrawScreen()
{
  //Draw background on buffer
  DrawImage(ImageBuffer,0,0,ImageBackground);
  //Draw all sprites on buffer
  for (const Image * const image: mImages)
  {
    DrawImage(ImageBuffer,image->left,image->top,image);
  }
  //Draw buffer on screen
  mSurface->update();
}
//---------------------------------------------------------------------------
Image * const FormSimStagecraftSelect::GetImage(const int value) const
{
  switch (value)
  {
    case 0: return Image0;
    case 1: return Image1;
    case 2: return Image2;
    case 3: return Image3;
    case 4: return Image4;
    case 5: return Image5;
    case 6: return Image6;
    case 7: return Image7;
    case 8: return Image8;
    case 9: return Image9;
  }
  assert(!"Should not get here");
  throw std::logic_error("Unhandled value in FormSimStagecraftSelect::GetImage");
}
//---------------------------------------------------------------------------
void FormSimStagecraftSelect::FormResize()
{
  const int width  = std::max(1,mSurface->width()  - (mBorderSize * 2));
  const int height = std::max(1,mSurface->height() - (mBorderSize * 2));
  SetPictureSize(ImageBackground,width,height);
  SetPictureSize(ImageBuffer,width,height);
  PaintWavyBackground(ImageBackground);
}
//---------------------------------------------------------------------------
void FormSimStagecraftSelect::FormMouseDown(const int X, const int Y)
{
  if (OnImage(X,Y,ImageStart)==true)
  {
    //Turn timer off temporarily
    TimerMain->stop();
    //And turn it back on when the game is closed
    ShowModal(new FormSimStagecraftMain(this,mLevel), this,
      [this]() { TimerMain->start(); });
  }
  else if (OnImage(X,Y,ImageArrowLeft)==true && mLevel > 1)
  {
    --mLevel;
    ImageSelectLeft->AssignPicture(GetImage(mLevel / 10));
    ImageSelectRight->AssignPicture(GetImage(mLevel % 10));
    UpdateText();
    DrawScreen();
  }
  else if (OnImage(X,Y,ImageArrowRight)==true && mLevel < 99)
  {
    ++mLevel;
    ImageSelectLeft->AssignPicture(GetImage(mLevel / 10));
    ImageSelectRight->AssignPicture(GetImage(mLevel % 10));
    UpdateText();
    DrawScreen();
  }
  else if (OnImage(X,Y,ImageQuit)==true)
  {
    close();
  }
}
//---------------------------------------------------------------------------
void FormSimStagecraftSelect::UpdateText()
{
  QStringList lines;
  switch (mLevel)
  {
    case 1:
      lines << "Level 1: Connect a lamp to a socket";
      lines << "";
      lines << "Equipment:";
      lines << "- Fresnel";
      lines << "- Wall socket, 220 Volts";
      break;
    case 2:
      lines << "Level 2: Connect a microphone to an active speaker";
      lines << "";
      lines << "Equipment:";
      lines << "- Microphone, ShureSm58";
      lines << "- Active speaker, RCF322A";
      lines << "- Wall socket, 220 Volts";
      break;
    case 3:
      lines << "Level 3: Connect and use a simple sound table";
      lines << "";
      lines << "Equipment:";
      lines << "- Microphone, ShureSm58";
      lines << "- Active speaker, RCF322A";
      lines << "- Soundtable, SimpleSound1";
      lines << "- Triplet, 220 Volts";
      lines << "- Wall socket, 220 Volts";
      break;
    case 4:
      lines << "Level 4: Connect and use a simple light table";
      lines << "";
      lines << "Equipment:";
      lines << "- Lighttable, SimpleShine";
      lines << "- Dimmerpack, Dimblock V3";
      lines << "- 5x fresnel";
      lines << "- Wall socket, 220 Volts";
      lines << "- Wall socket, power current";
      break;
    case 5:
      lines << "Level 5: Connect and use a more advanced sound table";
      lines << "";
      lines << "Equipment:";
      lines << "- 2x microphone, ShureSm58";
      lines << "- 2x active speaker, RCF322A";
      lines << "- Soundtable, SimpleSound2";
      lines << "- Triplet, 220 Volts";
      lines << "- Wall socket, 220 Volts";
      break;
    case 6:
      lines << "Level 6: Send sound using AUX";
      lines << "";
      lines << "Equipment:";
      lines << "- Microphone, ShureSm58";
      lines << "- Active speaker, RCF322A";
      lines << "- Soundtable, SimpleSound3";
      lines << "- Triplet, 220 Volts";
      lines << "- Wall socket, 220 Volts";
      break;
    case 7:
      lines << "Level 7: Serve three singers, send sound to PA and monitors";
      lines << "";
      lines << "Equipment:";
      lines << "- 3x microphone, ShureSm58";
      lines << "- 4x active speaker, RCF322A";
      lines << "- Soundtable, SimpleSound3";
      lines << "- Octet, 220 Volts";
      lines << "- Wall socket, 220 Volts";
      break;
    case 8:
      lines << "Level 8: Connect a CD player to speakers";
      lines << "  using a transition piece";
      lines << "";
      lines << "Equipment:";
      lines << "- Active speaker, RCF322A";
      lines << "- CD player";
      lines << "- Transition piece: jack male to 2x cinch female";
      lines << "- Octet, 220 Volts";
      lines << "- Wall socket, 220 Volts";
      break;
    case 9:
      lines << "Level 9: Connect a CD player to speakers";
      lines << "  using a sound table";
      lines << "";
      lines << "Equipment:";
      lines << "- Active speaker, RCF322A";
      lines << "- CD player";
      lines << "- Soundtable, SimpleSound4";
      lines << "- Octet, 220 Volts";
      lines << "- Wall socket, 220 Volts";
      break;
    case 10:
      lines << "Level 10: Record an MD from CD";
      lines << "";
      lines << "Equipment:";
      lines << "- CD player";
      lines << "- MD player";
      lines << "- Transition piece: jack male to 2x cinch female";
      lines << "- Active speaker, RCF322A";
      lines << "- Octet, 220 Volts";
      lines << "- Wall socket, 220 Volts";
      break;
    case 11:
      lines << "Level 11: Record an MD from CD and microphone";
      lines << "";
      lines << "Equipment:";
      lines << "- Microphone, ShureSm58";
      lines << "- MD player";
      lines << "- Transition piece: jack male to 2x cinch female";
      lines << "- Soundtable, SimpleSound4";
      lines << "- Active speaker, RCF322A";
      lines << "- Octet, 220 Volts";
      lines << "- Wall socket, 220 Volts";
      break;
    case 12:
      lines << "Level 12: Learn to use the crossfader";
      lines << "";
      lines << "Equipment:";
      lines << "- Lighttable, SimpleShine2";
      lines << "- Dimmerpack, Dimblock V3";
      lines << "- 5x fresnel";
      lines << "- Wall socket, 220 Volts";
      lines << "- Wall socket, power current";
      break;
    case 13:
      lines << "Level 13: Connect a microphone to a passive speaker";
      lines << "";
      lines << "Equipment:";
      lines << "- Microphone, ShureSm58";
      lines << "- Passive speaker, RCF Event 3000";
      lines << "- Amplifier, EasyAmp";
      lines << "- Wall socket, 220 Volts";
      break;
  }
  RichEdit->setPlainText(lines.join("\n"));
}
//---------------------------------------------------------------------------
void FormSimStagecraftSelect::keyPressEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_S: case Qt::Key_1: case Qt::Key_F1:
      FormMouseDown(ImageStart->left, ImageStart->top);
      break;
    case Qt::Key_Minus: case Qt::Key_Left:
      FormMouseDown(ImageArrowLeft->left, ImageArrowLeft->top);
      break;
    case Qt::Key_Plus: case Qt::Key_Right:
      FormMouseDown(ImageArrowRight->left, ImageArrowRight->top);
      break;
    case Qt::Key_Q: case Qt::Key_2: case Qt::Key_F2:
      FormMouseDown(ImageQuit->left, ImageQuit->top);
      break;
    default:
      QDialog::keyPressEvent(e);
  }
}
//---------------------------------------------------------------------------
