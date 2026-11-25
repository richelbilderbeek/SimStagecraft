//---------------------------------------------------------------------------
#include "UnitFormSimStagecraftOtherLicences.h"
#include "UnitTextDialog.h"
//---------------------------------------------------------------------------
FormSimStagecraftOtherLicences::FormSimStagecraftOtherLicences(QWidget * const parent)
  : QDialog(parent)
{
  SetupTextDialog(this, "Other licences",
    ":/FormSimStagecraftOtherLicences/RichEdit.txt");
}
//---------------------------------------------------------------------------
