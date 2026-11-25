//---------------------------------------------------------------------------

#include <cassert>
#include "UnitConnector.h"
#include "UnitWallSocket220.h"
//---------------------------------------------------------------------------
WallSocket220::WallSocket220()
  : mSocket220(std::shared_ptr<Socket220>(new Socket220(this)))
{
  assert(mSocket220.get() != 0);
}
//---------------------------------------------------------------------------
