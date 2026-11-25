//---------------------------------------------------------------------------

#include <cassert>
#include "UnitDisplay.h"
#include "UnitDisplayControl.h"
#include "UnitFormSprites.h"
#include "UnitImage.h"
//---------------------------------------------------------------------------
DisplayControl::DisplayControl(Image * const image)
  : mImage(image)
{
  assert(mImage!=0);
}
//---------------------------------------------------------------------------
AudioSignalControl::AudioSignalControl(
    const std::shared_ptr<AudioSignalDisplay> audioSignalDisplay,
    Image * const image)
  : DisplayControl(image), mAudioSignalDisplay(audioSignalDisplay)
{
  assert(mAudioSignalDisplay.get()!=0);
}
//---------------------------------------------------------------------------
void AudioSignalControl::Update()
{
  const double intensity = mAudioSignalDisplay->GetDisplayIntensity();
  DrawAudioSignal(mImage,intensity);
}
//---------------------------------------------------------------------------
LcdSymbolControl::LcdSymbolControl(const std::shared_ptr<LcdSymbol> lcdSymbol,
    Image * const image, Image * const imageLcdSymbol)
  : DisplayControl(image), mLcdSymbol(lcdSymbol), mImageLcdSymbol(imageLcdSymbol)
{
  assert(mLcdSymbol.get()!=0);
  assert(mImageLcdSymbol!=0);
}
//---------------------------------------------------------------------------
void LcdSymbolControl::Update()
{
  const double intensity = mLcdSymbol->GetDisplayIntensity();
  mImage->AssignPicture(mImageLcdSymbol);
  Blacken(mImage,1.0-intensity);
}
//---------------------------------------------------------------------------
LcdSymbolPlayControl::LcdSymbolPlayControl(const std::shared_ptr<LcdSymbol> lcdSymbol,
    Image * const image)
  : LcdSymbolControl(lcdSymbol,image,Sprites()->ImageLcdSymbolPlay)
{

}
//---------------------------------------------------------------------------
LcdSymbolRecControl::LcdSymbolRecControl(const std::shared_ptr<LcdSymbol> lcdSymbol,
    Image * const image)
  : LcdSymbolControl(lcdSymbol,image,Sprites()->ImageLcdSymbolRec)
{

}
//---------------------------------------------------------------------------
LedControl::LedControl(const std::shared_ptr<Led> led,
    Image * const image)
  : DisplayControl(image), mLed(led)
{
  assert(mLed.get()!=0);
}
//---------------------------------------------------------------------------
void LedControl::Update()
{
  const double intensity = mLed->GetDisplayIntensity();
  DrawLed(mImage,intensity,mLed->mRed,mLed->mGreen,mLed->mBlue);
}
//---------------------------------------------------------------------------
