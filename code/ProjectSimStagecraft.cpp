//---------------------------------------------------------------------------
#include <QApplication>

#include "UnitFormSimStagecraftMenu.h"
//---------------------------------------------------------------------------
int main(int argc, char * argv[])
{
  QApplication app(argc, argv);
  QApplication::setApplicationName("SimStagecraft");
  Q_INIT_RESOURCE(resources);
  FormSimStagecraftMenu menu;
#ifdef Q_OS_WASM
  //In the browser, use the whole canvas
  menu.showMaximized();
#else
  menu.show();
#endif
  return app.exec();
}
//---------------------------------------------------------------------------
