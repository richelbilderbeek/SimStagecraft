//---------------------------------------------------------------------------
#ifndef UnitFormSpritesH
#define UnitFormSpritesH
//---------------------------------------------------------------------------
#include "ui/UiFormSprites.h"
//---------------------------------------------------------------------------
//FormSprites holds all images that are shared between machines,
//for example the images of the connectors.
//It is created on first use by Sprites()
class FormSprites : public UiFormSprites
{
public:
  FormSprites();
};
//---------------------------------------------------------------------------
FormSprites * Sprites();
//---------------------------------------------------------------------------
#endif
