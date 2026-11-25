//---------------------------------------------------------------------------
#ifndef UnitShowModalH
#define UnitShowModalH
//---------------------------------------------------------------------------
#include <functional>

#include <QDialog>
//---------------------------------------------------------------------------
//Show a dialog modally, without blocking: the dialog deletes itself
//when it is closed, after which onClosed is called.
//
//QDialog::exec cannot be used, as nested event loops do not work
//in the WebAssembly version
inline void ShowModal(QDialog * const dialog, QObject * const context,
  const std::function<void()>& onClosed = std::function<void()>())
{
  dialog->setAttribute(Qt::WA_DeleteOnClose);
  if (onClosed)
  {
    QObject::connect(dialog, &QDialog::finished, context,
      [onClosed](int) { onClosed(); });
  }
  dialog->open();
}
//---------------------------------------------------------------------------
#endif
