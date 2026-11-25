//---------------------------------------------------------------------------
#include <cassert>
#include <cmath>

#include <QFile>
#include <QFont>
#include <QLabel>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QTimer>

#include "UnitFormSimStagecraftAbout.h"
#include "UnitFormSimStagecraftWhatsNew.h"
#include "UnitFormSimStagecraftOtherLicences.h"
#include "UnitShowModal.h"
#include "UnitSurfaceWidget.h"
//---------------------------------------------------------------------------
namespace {

QString ReadResourceText(const QString& resource)
{
  QFile file(resource);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return QString();
  return QString::fromUtf8(file.readAll());
}

QLabel * CreatePanel(QWidget * const parent, const QString& caption,
  const QRect& geometry, const int pixelSize = 11, const bool bold = false)
{
  QLabel * const label = new QLabel(caption,parent);
  label->setGeometry(geometry);
  label->setAlignment(Qt::AlignCenter);
  label->setStyleSheet("background-color: black; color: white;");
  QFont font("Courier New");
  font.setStyleHint(QFont::Monospace);
  font.setPixelSize(pixelSize);
  font.setBold(bold);
  label->setFont(font);
  return label;
}

} //~namespace
//---------------------------------------------------------------------------
FormSimStagecraftAbout::FormSimStagecraftAbout(QWidget * const parent)
  : QDialog(parent),
    mSurface(new SurfaceWidget(this)),
    TimerMain(new QTimer(this)),
    TimerColor(new QTimer(this)),
    mDr(1), mDg(1), mDb(1), mTick(0)
{
  setWindowTitle(QString::fromUtf8(DesignCaption));
  setFixedSize(DesignClientWidth,DesignClientHeight);
  setStyleSheet("QDialog { background-color: black; }");

  mSurface->setGeometry(ImageBackground->left, ImageBackground->top,
    ImageBackground->picture.width(), ImageBackground->picture.height());
  mSurface->buffer = ImageBackground;
  ImageBackground->left = 0;
  ImageBackground->top = 0;

  CreatePanel(this, "SimStagecraft", QRect(327,0,258,41), 29, true);
  CreatePanel(this, "Version 1.1", QRect(327,42,258,39));
  CreatePanel(this, QString::fromUtf8("(C) 2008 Richèl Bilderbeek"), QRect(327,81,258,39));
  CreatePanel(this, "Programmed by", QRect(327,120,258,39));
  CreatePanel(this, QString::fromUtf8("Richèl Bilderbeek"), QRect(327,159,258,39));
  CreatePanel(this, "from October 2008 to and", QRect(327,198,258,39));
  CreatePanel(this, "including January 2009", QRect(327,237,258,39));
  CreatePanel(this, "http://www.richelbilderbeek.nl", QRect(327,276,258,39));

  QPushButton * const buttonOtherLicences = new QPushButton("Other licences",this);
  buttonOtherLicences->setGeometry(8,288,121,25);
  connect(buttonOtherLicences, &QPushButton::clicked, this,
    [this]() { ShowModal(new FormSimStagecraftOtherLicences(this), this); });

  QPushButton * const buttonWhatsNew = new QPushButton("What's new?",this);
  buttonWhatsNew->setGeometry(216,288,99,25);
  connect(buttonWhatsNew, &QPushButton::clicked, this,
    [this]() { ShowModal(new FormSimStagecraftWhatsNew(this), this); });

  QPlainTextEdit * const richEditLicence = new QPlainTextEdit(this);
  richEditLicence->setGeometry(0,320,591,89);
  richEditLicence->setReadOnly(true);
  richEditLicence->setFrameStyle(QFrame::NoFrame);
  richEditLicence->setStyleSheet("background-color: black; color: white;");
  {
    QFont font("Courier New");
    font.setStyleHint(QFont::Monospace);
    font.setPixelSize(11);
    richEditLicence->setFont(font);
  }
  richEditLicence->setPlainText(
    ReadResourceText(":/FormSimStagecraftAbout/RichEditLicence.txt"));

  connect(TimerMain, &QTimer::timeout, this, [this]() { TimerMainTimer(); });
  connect(TimerColor, &QTimer::timeout, this, [this]() { TimerColorTimer(); });

  DrawBackground();
  TimerMainTimer();
  TimerMain->start(50);
  TimerColor->start(1000);
}
//---------------------------------------------------------------------------
void FormSimStagecraftAbout::DrawBackground()
{
  Image * const image = ImageBackground;
  assert(image!=0);
  const int maxx = image->picture.width();
  const int maxy = image->picture.height();
  for (int y = 0; y != maxy; ++y)
  {
    QRgb * const line = reinterpret_cast<QRgb*>(image->picture.scanLine(y));
    const double yD = static_cast<double>(y);
    for (int x = 0; x != maxx; ++x)
    {
      const double xD = static_cast<double>(x);
      //Range z: -3 , +3
      const double zD
        = std::cos(xD / 3.0)
        + std::sin(yD / 4.0)
        - std::sin( (xD + yD) / 5.0);
      const int grey = static_cast<int>( (zD + 3.0) * (256.0 / 6.0) );
      line[x] = qRgb(
        (qRed(line[x])   + grey) % 256,
        (qGreen(line[x]) + grey) % 256,
        (qBlue(line[x])  + grey) % 256);
    }
  }
}
//---------------------------------------------------------------------------
void FormSimStagecraftAbout::TimerColorTimer()
{
  ++mTick;
  switch (mTick % 15)
  {
    case  0: mDr =  3; mDg = -4; mDb =  2; break;
    case  1: mDr =  4; mDg = -3; mDb =  1; break;
    case  2: mDr =  5; mDg = -2; mDb = -1; break;
    case  3: mDr =  4; mDg =  1; mDb = -2; break;
    case  4: mDr =  3; mDg =  2; mDb = -3; break;
    case  5: mDr =  2; mDg =  3; mDb = -4; break;
    case  6: mDr =  1; mDg =  4; mDb = -3; break;
    case  7: mDr = -1; mDg =  5; mDb = -2; break;
    case  8: mDr = -2; mDg =  4; mDb =  1; break;
    case  9: mDr = -3; mDg =  3; mDb =  2; break;
    case 10: mDr = -4; mDg =  2; mDb =  3; break;
    case 11: mDr = -3; mDg =  1; mDb =  4; break;
    case 12: mDr = -2; mDg = -1; mDb =  5; break;
    case 13: mDr =  1; mDg = -2; mDb =  4; break;
    case 14: mDr =  2; mDg = -3; mDb =  3; break;
  }
}
//---------------------------------------------------------------------------
void FormSimStagecraftAbout::TimerMainTimer()
{
  Image * const image = ImageBackground;
  const int maxx = image->picture.width();
  const int maxy = image->picture.height();
  for (int y = 0; y != maxy; ++y)
  {
    QRgb * const line = reinterpret_cast<QRgb*>(image->picture.scanLine(y));
    for (int x = 0; x != maxx; ++x)
    {
      //Overflow is intended: the colors cycle
      line[x] = qRgb(
        (qRed(line[x])   + mDr + 256) % 256,
        (qGreen(line[x]) + mDg + 256) % 256,
        (qBlue(line[x])  + mDb + 256) % 256);
    }
  }
  mSurface->update();
}
//---------------------------------------------------------------------------
