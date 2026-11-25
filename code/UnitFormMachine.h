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
#ifndef UnitFormMachineH
#define UnitFormMachineH
//---------------------------------------------------------------------------
#include <functional>
#include <memory>
#include <vector>

#include <QRect>

#include "UnitEnumDisplayMode.h"
#include "UnitImage.h"
//---------------------------------------------------------------------------
struct Machine;
class FormSimStagecraftMain;
class QTimer;
struct ConnectorControl;
//---------------------------------------------------------------------------
// Every FormMachine manages the GUI of one Machine
// A FormX manages a X
//
// A FormMachine is not a widget: it draws itself on its ImageBuffer,
// which is drawn by FormSimStagecraftMain at (Left,Top)
class FormMachine
{
public:
  FormMachine(FormSimStagecraftMain * const formParent,
    const int clientWidth, const int clientHeight);
  FormMachine(const FormMachine&) = delete;
  FormMachine& operator=(const FormMachine&) = delete;
  virtual ~FormMachine();

  void SetDisplayMode(const EnumDisplayMode mode) { mDisplayMode = mode; }
  virtual void UpdateBuffer() = 0;
  FormSimStagecraftMain * const mFormParent; //const, so it be public
  virtual void OnMouseDown(const int, const int) {}
  virtual void OnMouseMove(const int, const int) {}
  virtual void OnMouseUp(const int, const int) {}
  virtual void OnAfterResize() {};
  static const int mBorderSize = 8;
  void OnControllerClick();
  void OnConnectorClick(ConnectorControl * const connectorControl);
  void DrawOnBuffer(const Image * const image);
  void DrawOnBuffer(const std::vector<Image * >& images);
  void DrawBorderAroundBuffer();

  //Resize the buffer to the client size, then call OnAfterResize
  void Resize();

  const QRect ClientRect() const { return QRect(0,0,ClientWidth,ClientHeight); }

  //Position on the main screen
  int Left;
  int Top;
  //Size
  int ClientWidth;
  int ClientHeight;

  //The buffer the machine draws itself on
  Image * const ImageBuffer;

protected:
  EnumDisplayMode mDisplayMode;

  //Call a function every interval milliseconds,
  //replaces the TTimers on the VCL forms
  void AddTimer(const int interval, const std::function<void()>& f);

private:
  Image mImageBuffer;
  std::vector<std::unique_ptr<QTimer>> mTimers;
};
//---------------------------------------------------------------------------
#endif
