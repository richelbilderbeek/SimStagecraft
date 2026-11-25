//---------------------------------------------------------------------------

#include <cassert>
#include <stdexcept>
#include "UnitControllerControl.h"
#include "UnitConnectorControl.h"
#include "UnitMachine.h"
#include "UnitOctlet.h"
#include "UnitImage.h"
#include "UnitFormOctlet.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
FormOctlet::FormOctlet(FormSimStagecraftMain * const formParent)
  : FormMachine(formParent,DesignClientWidth,DesignClientHeight),
    mOctlet(std::shared_ptr<Octlet>(new Octlet))
{
  mImageSockets220.push_back(ImageSocket220_1);
  mImageSockets220.push_back(ImageSocket220_2);
  mImageSockets220.push_back(ImageSocket220_3);
  mImageSockets220.push_back(ImageSocket220_4);
  mImageSockets220.push_back(ImageSocket220_5);
  mImageSockets220.push_back(ImageSocket220_6);
  mImageSockets220.push_back(ImageSocket220_7);
  mImageSockets220.push_back(ImageSocket220_8);
  assert(mImageSockets220.size() == 8);


  //Control
  mTwoSwitchPower = std::shared_ptr<TwoSwitchControl>(
    new TwoSwitchControl(this,mOctlet->mPowerSwitch,ImageTwoSwitchPower));
  //Connect
  mPlug220 = std::shared_ptr<Plug220Control>(
    new Plug220Control(this,mOctlet->mPlug,ImagePlug220));
  mSocket220Controls = this->CreateSocket220Controls();

  CreateWatermark(ImageView,ImageWatermark);

  Resize();

  //Turn power off by default
  mTwoSwitchPower->OnMouseDown(0,0); //Top of powerswitch turns off
}
//---------------------------------------------------------------------------
void FormOctlet::UpdateBuffer()
{
  switch (mDisplayMode)
  {
    case modeView:
      DrawImage(ImageBuffer,0,0,ImageView);
      break;
    case modeUse:
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      DrawOnBuffer(ImageTwoSwitchPower);
      break;
    case modeConnect:
      DrawImage(ImageBuffer,0,0,ImageWatermark);
      DrawOnBuffer(ImagePlug220);
      {
        const int nSockets = mSocket220Controls.size();
        for (int i=0; i!=nSockets; ++i)
        {
          DrawOnBuffer(mImageSockets220[i]);
        }
      }
      break;
    default: assert(!"Should not get here");
  }

  DrawBorderAroundBuffer();
}
//---------------------------------------------------------------------------
void FormOctlet::OnMouseDown(const int x, const int y)
{
  switch (mDisplayMode)
  {
    case modeView:
      break;
    case modeUse:
      if (OnImage(x,y,ImageTwoSwitchPower))
      {
        mTwoSwitchPower->OnMouseDown(
          x - ImageTwoSwitchPower->left,
          y - ImageTwoSwitchPower->top);
      }
      break;
    case modeConnect:
      if (OnImage(x,y,ImagePlug220)) mFormParent->OnConnectorClick(mPlug220.get());
      {
        const int nSockets = mSocket220Controls.size();
        for (int i=0; i!=nSockets; ++i)
        {
          if (OnImage(x,y,mImageSockets220[i]))
            mFormParent->OnConnectorClick(mSocket220Controls[i].get());

        }
      }
      break;
  }
}
//---------------------------------------------------------------------------
void FormOctlet::OnAfterResize()
{
  const std::vector<QRect> v(GetRectsHorizontal(ClientRect(),5));
  const std::vector<QRect> v0(GetRectsVertical(v[0],2));
  const std::vector<QRect> v1(GetRectsVertical(v[1],2));
  const std::vector<QRect> v2(GetRectsVertical(v[2],2));
  const std::vector<QRect> v3(GetRectsVertical(v[3],2));
  PlaceInCenter(mImageSockets220[0],v0[0]);
  PlaceInCenter(mImageSockets220[1],v1[0]);
  PlaceInCenter(mImageSockets220[2],v2[0]);
  PlaceInCenter(mImageSockets220[3],v3[0]);
  PlaceInCenter(mImageSockets220[4],v0[1]);
  PlaceInCenter(mImageSockets220[5],v1[1]);
  PlaceInCenter(mImageSockets220[6],v2[1]);
  PlaceInCenter(mImageSockets220[7],v3[1]);
  PlaceInCenter(ImagePlug220    ,v[4]);

  PlaceInCenter(ImageTwoSwitchPower,ClientRect());
}
//---------------------------------------------------------------------------
const std::vector<std::shared_ptr<Socket220Control> >
  FormOctlet::CreateSocket220Controls()
{
  std::vector<std::shared_ptr<Socket220Control> > sockets;

  const int nSockets = mImageSockets220.size();
  assert(mOctlet->mSockets220.size() == mImageSockets220.size() );

  for (int i=0; i!=nSockets; ++i)
  {
    std::shared_ptr<Socket220Control> socket(new Socket220Control(
      this, mOctlet->mSockets220[i], mImageSockets220[i] ));
    sockets.push_back(socket);

  }

  assert(sockets.size() == 8);

  return sockets;
}
//---------------------------------------------------------------------------


