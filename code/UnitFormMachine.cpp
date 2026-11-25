//---------------------------------------------------------------------------
/*
  SimStagecraft, stagecraft simulation
  Copyright (C) 2008  Richel Bilderbeek

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
#include <cassert>

#include <QPainter>
#include <QPen>
#include <QTimer>

#include "UnitMachine.h"
#include "UnitConnectorControl.h"
#include "UnitFormMachine.h"
#include "UnitFormSimStagecraftMain.h"
//---------------------------------------------------------------------------
FormMachine::FormMachine(
    FormSimStagecraftMain * const formParent,
    const int clientWidth, const int clientHeight)
  : mFormParent(formParent),
    Left(0),
    Top(0),
    ClientWidth(clientWidth),
    ClientHeight(clientHeight),
    ImageBuffer(&mImageBuffer),
    mDisplayMode(modeView),
    mImageBuffer("ImageBuffer","",0,0,clientWidth,clientHeight,false,true)
{
  assert(mFormParent != 0 && "FormMachine must know its parent form");
}
//---------------------------------------------------------------------------
FormMachine::~FormMachine()
{
  for (const std::unique_ptr<QTimer>& timer: mTimers) timer->stop();
}
//---------------------------------------------------------------------------
void FormMachine::AddTimer(const int interval, const std::function<void()>& f)
{
  std::unique_ptr<QTimer> timer = std::make_unique<QTimer>();
  QObject::connect(timer.get(), &QTimer::timeout, f);
  timer->start(interval);
  mTimers.push_back(std::move(timer));
}
//---------------------------------------------------------------------------
void FormMachine::Resize()
{
  SetPictureSize(ImageBuffer,ClientWidth,ClientHeight);
  ImageBuffer->width = ClientWidth;
  ImageBuffer->height = ClientHeight;
  OnAfterResize();
}
//---------------------------------------------------------------------------
void FormMachine::OnControllerClick()
{
  mFormParent->OnControllerClick();
}
//---------------------------------------------------------------------------
void FormMachine::OnConnectorClick(ConnectorControl * const connectorControl)
{
  mFormParent->OnConnectorClick(connectorControl);
}
//---------------------------------------------------------------------------
void FormMachine::DrawOnBuffer(const Image * const image)
{
  DrawImage(ImageBuffer, image->left, image->top, image);
}
//---------------------------------------------------------------------------
void FormMachine::DrawOnBuffer(const std::vector<Image *>& images)
{
  for (const Image * const image: images)
  {
    DrawOnBuffer(image);
  }
}
//---------------------------------------------------------------------------
void FormMachine::DrawBorderAroundBuffer()
{
  QPainter painter(&ImageBuffer->picture);
  QPen pen(Qt::black);
  pen.setWidth(mBorderSize);
  painter.setPen(pen);
  painter.setBrush(Qt::NoBrush);
  painter.drawRect(0,0,ClientWidth,ClientHeight);
}
//---------------------------------------------------------------------------
