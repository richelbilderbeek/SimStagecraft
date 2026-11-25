//---------------------------------------------------------------------------

#ifndef UnitDisplayControlH
#define UnitDisplayControlH
//---------------------------------------------------------------------------
#include <memory>
struct AudioSignalDisplay;
struct LcdSymbol;
struct Led;
struct Image;
//---------------------------------------------------------------------------
struct DisplayControl
{
  DisplayControl(Image * const image);
  virtual void Update() = 0;

  protected:
  Image * const mImage;

  public:
  virtual ~DisplayControl() {}
  protected:
};
//---------------------------------------------------------------------------
struct AudioSignalControl : public DisplayControl
{
  AudioSignalControl(
    const std::shared_ptr<AudioSignalDisplay> audioSignalDisplay,
    Image * const image);

  void Update();

  private:
  const std::shared_ptr<AudioSignalDisplay> mAudioSignalDisplay;

  public:
  ~AudioSignalControl() {}
  private:
};
//---------------------------------------------------------------------------
struct LcdSymbolControl : public DisplayControl
{
  LcdSymbolControl(const std::shared_ptr<LcdSymbol> lcdSymbol,
    Image * const image,
    Image * const imageLcdSymbol);

  void Update();

  private:

  const std::shared_ptr<LcdSymbol> mLcdSymbol;
  Image * const mImageLcdSymbol;

  protected:
  public:
  virtual ~LcdSymbolControl() {}
  protected:
};
//---------------------------------------------------------------------------
struct LcdSymbolPlayControl : public LcdSymbolControl
{
  LcdSymbolPlayControl(const std::shared_ptr<LcdSymbol> lcdSymbol,
    Image * const image);

  private:
  public:
  ~LcdSymbolPlayControl() {}
  private:
};
//---------------------------------------------------------------------------
struct LcdSymbolRecControl : public LcdSymbolControl
{
  LcdSymbolRecControl(const std::shared_ptr<LcdSymbol> lcdSymbol,
    Image * const image);

  private:
  public:
  ~LcdSymbolRecControl() {}
  private:
};
//---------------------------------------------------------------------------
struct LedControl : public DisplayControl
{
  LedControl(const std::shared_ptr<Led> led,
    Image * const image);

  void Update();

  private:
  const std::shared_ptr<Led> mLed;

  public:
  ~LedControl() {}
  private:
};
//---------------------------------------------------------------------------

#endif
