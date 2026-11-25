//---------------------------------------------------------------------------
#ifndef UnitTextDialogH
#define UnitTextDialogH
//---------------------------------------------------------------------------
#include <QDialog>
#include <QFile>
#include <QFont>
#include <QPlainTextEdit>
#include <QVBoxLayout>
//---------------------------------------------------------------------------
//Fill a dialog with a read-only text, read from a resource
inline void SetupTextDialog(QDialog * const dialog,
  const QString& caption, const QString& resource)
{
  dialog->setWindowTitle(caption);
  dialog->resize(462,296);
  QPlainTextEdit * const edit = new QPlainTextEdit(dialog);
  edit->setReadOnly(true);
  QFont font("Courier New");
  font.setStyleHint(QFont::Monospace);
  edit->setFont(font);
  QFile file(resource);
  if (file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    edit->setPlainText(QString::fromUtf8(file.readAll()));
  }
  QVBoxLayout * const layout = new QVBoxLayout(dialog);
  layout->setContentsMargins(0,0,0,0);
  layout->addWidget(edit);
}
//---------------------------------------------------------------------------
#endif
