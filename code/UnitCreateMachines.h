//---------------------------------------------------------------------------

#ifndef UnitCreateMachinesH
#define UnitCreateMachinesH
//---------------------------------------------------------------------------
#include <vector>
#include <memory>
class FormMachine;
class FormSimStagecraftMain;
//---------------------------------------------------------------------------
std::vector<std::shared_ptr<FormMachine> > CreateMachines(
  FormSimStagecraftMain * const formParent,
  const int level);
//---------------------------------------------------------------------------
#endif
