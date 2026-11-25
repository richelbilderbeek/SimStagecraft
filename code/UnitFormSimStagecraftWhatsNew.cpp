//---------------------------------------------------------------------------
#include "UnitFormSimStagecraftWhatsNew.h"
#include "UnitTextDialog.h"
//---------------------------------------------------------------------------
FormSimStagecraftWhatsNew::FormSimStagecraftWhatsNew(QWidget * const parent)
  : QDialog(parent)
{
  SetupTextDialog(this, "What's new?",
    ":/FormSimStagecraftWhatsNew/RichEdit.txt");
}
//---------------------------------------------------------------------------
