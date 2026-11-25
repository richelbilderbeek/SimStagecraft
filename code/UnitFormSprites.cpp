//---------------------------------------------------------------------------
#include <vector>

#include "UnitFormSprites.h"
//---------------------------------------------------------------------------
FormSprites::FormSprites()
{
  //Set transparencies of some Images right
  const std::vector<Image*> images
    = {
      ImagePlug220Connected,
      ImagePlug220ConnectedSelected,
      ImageJackMaleConnected,
      ImageJackMaleConnectedSelected,
      ImageEuroFemaleConnected,
      ImageEuroFemaleConnectedSelected
    };
  for (Image * const image: images)
  {
    image->transparentColor = qRgb(0,255,0);
    image->transparent = true;
  }
}
//---------------------------------------------------------------------------
FormSprites * Sprites()
{
  static FormSprites sprites;
  return &sprites;
}
//---------------------------------------------------------------------------
