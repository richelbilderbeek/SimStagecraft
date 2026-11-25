//---------------------------------------------------------------------------
#include <QKeyEvent>
#include <QTimer>
#include <QVBoxLayout>

#include "UnitImage.h"
#include "UnitFormSimStagecraftMenu.h"
#include "UnitFormSimStagecraftSelect.h"
#include "UnitFormSimStagecraftAbout.h"
#include "UnitShowModal.h"
#include "UnitSurfaceWidget.h"
//---------------------------------------------------------------------------
FormSimStagecraftMenu::FormSimStagecraftMenu(QWidget * const parent)
  : QDialog(parent),
    mSurface(new SurfaceWidget(this)),
    TimerBackground(new QTimer(this)),
    mImages(GetImages()),
    mBorderSize(8)
{
  setWindowTitle(QString::fromUtf8(DesignCaption));
  setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  setStyleSheet("background-color: black;");
  QVBoxLayout * const layout = new QVBoxLayout(this);
  layout->setContentsMargins(0,0,0,0);
  layout->addWidget(mSurface);
  resize(DesignClientWidth,DesignClientHeight);

  ImageBuffer->left = mBorderSize;
  ImageBuffer->top = mBorderSize;
  mSurface->buffer = ImageBuffer;
  mSurface->onMouseDown = [this](int x, int y) { FormMouseDown(x,y); };
  mSurface->onResize = [this]() { FormResize(); };

  connect(TimerBackground, &QTimer::timeout, this,
    [this]() { TickBackground(ImageBackground); DrawScreen(); });

  FormResize();
  DrawScreen();
  TimerBackground->start(50);
}
//---------------------------------------------------------------------------
void FormSimStagecraftMenu::DrawScreen()
{
  //Draw background
  DrawImage(ImageBuffer,0,0,ImageBackground);
  //Draw images
  for (const Image * const image: mImages)
  {
    DrawImage(ImageBuffer,image->left,image->top,image);
  }
  //Put buffer on screen
  mSurface->update();
}
//---------------------------------------------------------------------------
void FormSimStagecraftMenu::FormResize()
{
  const int width  = std::max(1,mSurface->width()  - (mBorderSize * 2));
  const int height = std::max(1,mSurface->height() - (mBorderSize * 2));
  SetPictureSize(ImageBackground,width,height);
  SetPictureSize(ImageBuffer,width,height);
  PaintWavyBackground(ImageBackground);
}
//---------------------------------------------------------------------------
const std::vector<Image*> FormSimStagecraftMenu::GetImages() const
{
  return {
    ImageStart, ImageAbout, ImageQuit, ImageTitle,
    Image1, Image2, Image3, Image4, Image5, Image6
  };
}
//---------------------------------------------------------------------------
void FormSimStagecraftMenu::FormMouseDown(const int X, const int Y)
{
  if (OnImage(X,Y,ImageStart) == true
   || OnImage(X,Y,Image1    ) == true
   || OnImage(X,Y,Image4    ) == true)
  {
    //Start game
    TimerBackground->stop();
    ShowModal(new FormSimStagecraftSelect(this), this,
      [this]() { TimerBackground->start(); });
  }
  else
  if (OnImage(X,Y,ImageAbout) == true
   || OnImage(X,Y,Image2    ) == true
   || OnImage(X,Y,Image5    ) == true)
  {
    //About screen
    TimerBackground->stop();
    ShowModal(new FormSimStagecraftAbout(this), this,
      [this]() { TimerBackground->start(); });
  }
  else
  if (OnImage(X,Y,ImageQuit) == true
   || OnImage(X,Y,Image3   ) == true
   || OnImage(X,Y,Image6   ) == true)
  {
    close();
  }
}
//---------------------------------------------------------------------------
void FormSimStagecraftMenu::keyPressEvent(QKeyEvent * e)
{
  switch (e->key())
  {
    case Qt::Key_S: case Qt::Key_1: case Qt::Key_F1:
      FormMouseDown(ImageStart->left, ImageStart->top);
      break;
    case Qt::Key_A: case Qt::Key_2: case Qt::Key_F2:
      FormMouseDown(ImageAbout->left, ImageAbout->top);
      break;
    case Qt::Key_Q: case Qt::Key_3: case Qt::Key_F3:
      FormMouseDown(ImageQuit->left, ImageQuit->top);
      break;
    default:
      QDialog::keyPressEvent(e);
  }
}
//---------------------------------------------------------------------------
