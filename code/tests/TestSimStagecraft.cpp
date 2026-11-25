//---------------------------------------------------------------------------
// Smoke test of the Qt version of SimStagecraft
//
// Creates every screen and every level, switches between the
// View, Connect and Use modes and clicks all over every machine.
// Build in Debug mode, so that the many asserts in the code are active.
//
// Run with QT_QPA_PLATFORM=offscreen when there is no display.
// Pass a folder name as argument to save screenshots there.
//---------------------------------------------------------------------------
#include <cstdlib>
#include <iostream>

#include <QApplication>
#include <QDir>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QPixmap>

#include "UnitFormSimStagecraftAbout.h"
#include "UnitFormSimStagecraftMain.h"
#include "UnitFormSimStagecraftMenu.h"
#include "UnitFormSimStagecraftOtherLicences.h"
#include "UnitFormSimStagecraftSelect.h"
#include "UnitFormSimStagecraftWhatsNew.h"
#include "UnitSurfaceWidget.h"
//---------------------------------------------------------------------------
namespace {

QString screenshotFolder;

void Save(QWidget * const widget, const QString& name)
{
  QApplication::processEvents();
  if (screenshotFolder.isEmpty()) return;
  widget->grab().save(QDir(screenshotFolder).filePath(name + ".png"));
}

void PressKey(QWidget * const widget, const int key)
{
  QKeyEvent press(QEvent::KeyPress, key, Qt::NoModifier);
  QApplication::sendEvent(widget, &press);
  QApplication::processEvents();
}

SurfaceWidget * FindSurface(QWidget * const widget)
{
  for (QWidget * const child: widget->findChildren<QWidget*>())
  {
    if (SurfaceWidget * const surface = dynamic_cast<SurfaceWidget*>(child))
    {
      return surface;
    }
  }
  return nullptr;
}

void Click(QWidget * const widget, const int x, const int y)
{
  const QPointF pos(x,y);
  QMouseEvent press(QEvent::MouseButtonPress, pos, widget->mapToGlobal(pos),
    Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
  QApplication::sendEvent(widget, &press);
  QMouseEvent release(QEvent::MouseButtonRelease, pos, widget->mapToGlobal(pos),
    Qt::LeftButton, Qt::NoButton, Qt::NoModifier);
  QApplication::sendEvent(widget, &release);
}

void TestLevel(const int level)
{
  FormSimStagecraftMain form(nullptr, level);
  form.resize(1024, 768);
  form.show();
  QApplication::processEvents();
  SurfaceWidget * const surface = FindSurface(&form);
  if (!surface) { std::cerr << "No surface\n"; std::exit(1); }
  const QString prefix = QString("level%1_").arg(level, 2, 10, QChar('0'));
  Save(&form, prefix + "1_view");
  //Connect mode: click everywhere, twice, to (dis)connect connectors
  PressKey(&form, Qt::Key_2);
  Save(&form, prefix + "2_connect");
  for (int pass = 0; pass != 2; ++pass)
  {
    for (int y = 3; y < surface->height(); y += 13)
    {
      for (int x = 3; x < surface->width(); x += 13)
      {
        Click(surface, x, y);
      }
    }
  }
  //Use mode: click everywhere, to use dials, faders and buttons
  PressKey(&form, Qt::Key_3);
  for (int y = 2; y < surface->height(); y += 7)
  {
    for (int x = 2; x < surface->width(); x += 7)
    {
      Click(surface, x, y);
    }
  }
  Save(&form, prefix + "3_use");
  //AutoMove and drag a machine
  PressKey(&form, Qt::Key_A);
  for (int i = 0; i != 5; ++i) form.DrawScreen();
  PressKey(&form, Qt::Key_1);
  form.close();
}

} //~namespace
//---------------------------------------------------------------------------
int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  Q_INIT_RESOURCE(resources);
  if (argc > 1)
  {
    screenshotFolder = argv[1];
    QDir().mkpath(screenshotFolder);
  }

  {
    FormSimStagecraftMenu form;
    form.show();
    Save(&form, "menu");
  }
  {
    FormSimStagecraftSelect form;
    form.show();
    PressKey(&form, Qt::Key_Right);
    PressKey(&form, Qt::Key_Right);
    Save(&form, "select");
  }
  {
    FormSimStagecraftAbout form;
    form.show();
    Save(&form, "about");
  }
  {
    FormSimStagecraftWhatsNew form;
    form.show();
    Save(&form, "whatsnew");
  }
  {
    FormSimStagecraftOtherLicences form;
    form.show();
    Save(&form, "otherlicences");
  }
  //Levels 1 to 13 have machines, other levels are empty
  for (int level = 1; level <= 14; ++level)
  {
    std::cout << "Testing level " << level << std::endl;
    TestLevel(level);
  }
  std::cout << "All tests passed" << std::endl;
  return 0;
}
//---------------------------------------------------------------------------
