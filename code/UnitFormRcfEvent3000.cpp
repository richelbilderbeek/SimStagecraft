//---------------------------------------------------------------------------

#include <cassert>
#include <cmath>
#include <stdexcept>
#include "UnitControllerControl.h"
#include "UnitConnectorControl.h"
#include "UnitDisplayControl.h"
#include "UnitMachine.h"
#include "UnitSpeaker.h"
#include "UnitImage.h"
#include "UnitFormRcfEvent3000.h"
#include "UnitFormMachine.h"
#include "UnitFormSprites.h"

#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
FormRcfEvent3000::FormRcfEvent3000(FormSimStagecraftMain * const formParent)
  : FormMachine(formParent,DesignClientWidth,DesignClientHeight),
    mSpeaker(std::shared_ptr<RcfEvent3000>(new RcfEvent3000))
{
  //Control
  //Connect
  mInput = std::shared_ptr<SpeakonFemaleControl>(
    new SpeakonFemaleControl(this,mSpeaker->mInput,ImageInput));
  mLink = std::shared_ptr<SpeakonFemaleControl>(
    new SpeakonFemaleControl(this,mSpeaker->mLink,ImageLink));
  //Display


  CreateWatermark(ImageView,ImageWatermark);

  Resize();
}
//---------------------------------------------------------------------------
void FormRcfEvent3000::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      DrawImage(ImageBuffer,0,0,ImageView);
      break;
    case modeUse:
      //Update all
      DrawAudioSignal(ImageSound,mSpeaker->GetSoundLevel());
      //Start drawing
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      //Labels
      //Controls
      DrawOnBuffer(ImageSound);
      break;
    case modeConnect:
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      //Labels
      //Connectors
      DrawOnBuffer(ImageInput);
      DrawOnBuffer(ImageLink);
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void FormRcfEvent3000::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      break;
    case modeConnect:
      if (OnImage(x,y,ImageInput)) mFormParent->OnConnectorClick(mInput.get());
      if (OnImage(x,y,ImageLink )) mFormParent->OnConnectorClick(mLink.get() );
      break;
  }
}
//---------------------------------------------------------------------------
void FormRcfEvent3000::OnAfterResize()
{
  //Use
  {
    //Get y-x-ordered vector of QRects
    const std::vector<std::vector<QRect> > v(GetRectsGrid(ClientRect(),1,1));
    //Resize bitmaps
    //Place bitmaps
    //Labels
    //Controls
    //Displays
    PlaceInCenter(ImageSound,v[0][0]);
  }
  //Connect
  {
    const std::vector<std::vector<QRect> > v(GetRectsGrid(ClientRect(),2,1));
    //Labels
    //Connectors
    PlaceInCenter(ImageInput,v[0][0]);
    PlaceInCenter(ImageLink ,v[0][1]);
  }
}
//---------------------------------------------------------------------------

