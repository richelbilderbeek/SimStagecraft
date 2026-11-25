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
  menu.show();
  return app.exec();
}
//---------------------------------------------------------------------------
