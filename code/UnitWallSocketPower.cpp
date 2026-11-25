//---------------------------------------------------------------------------

#include <cassert>
#include "UnitConnector.h"
#include "UnitWallSocketPower.h"
//---------------------------------------------------------------------------
WallSocketPower::WallSocketPower()
  : mSocketPower(std::shared_ptr<SocketPowerFemale>(new SocketPowerFemale(this)))
{
  assert(mSocketPower.get() != 0);
}
//---------------------------------------------------------------------------
