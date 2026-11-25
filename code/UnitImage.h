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
#ifndef UnitImageH
#define UnitImageH
//---------------------------------------------------------------------------
#include <memory>
#include <optional>
#include <vector>

#include <QColor>
#include <QImage>
#include <QRect>
#include <QString>
//---------------------------------------------------------------------------
// An Image is a positioned bitmap. It replaces the VCL TImage that the
// original version used: the forms of SimStagecraft are never shown as
// widgets themselves, instead their images are drawn on a buffer
//
// The picture is always a 32-bit RGB QImage.
// When 'transparent' is true, the transparent color is either the
// fixed 'transparentColor', or (if not set) the color of the
// bottom-left pixel, just like a VCL TBitmap with TransparentMode tmAuto
struct Image
{
  Image(const QString& name, const QString& resource,
    const int left, const int top, const int width, const int height,
    const bool transparent, const bool visible, const bool autoSize = false);

  QString name;
  QImage picture;
  int left;
  int top;
  int width;
  int height;
  bool transparent;
  bool visible;
  //If true, width and height follow the size of the picture
  bool autoSize;
  std::optional<QRgb> transparentColor;

  //Copy the picture (and its transparent color) of another Image
  void AssignPicture(const Image * const other);

  //The picture with its transparency applied, ready to be drawn
  QImage Graphic() const;

  //Call this after changing the picture, to update the size if autoSize
  void PictureChanged();
};
//---------------------------------------------------------------------------
// ImageStore owns Images. The generated Ui headers (in the ui folder,
// generated from the original .dfm files) derive from it
struct ImageStore
{
  ImageStore() = default;
  ImageStore(const ImageStore&) = delete;
  ImageStore& operator=(const ImageStore&) = delete;
  Image * Add(const char * const name, const char * const resource,
    const int left, const int top, const int width, const int height,
    const bool transparent, const bool visible, const bool autoSize);
  private:
  std::vector<std::unique_ptr<Image>> mImages;
};
//---------------------------------------------------------------------------
//Makes all red pixels even, except when there's a message pixel
//From http://www.richelbilderbeek.nl/CppAddMessageRed.htm
void AddMessageRed(
  const Image * const original,
  const Image * const message,
  Image * const result);

void Blacken(Image * const image, const double intensity);

void CreateWatermark(const Image * const original,
  Image * const image);

void DrawAudioSignal(Image * const image, const double intensity);

void DrawDial(Image * const image, const int x, const int y,
  const QColor& color = QColor(128,128,128));

void DrawFader(Image * const image, const int faderY);

//Draw an Image on another Image, at position (x,y)
void DrawImage(Image * const target, const int x, const int y,
  const Image * const source);

void DrawLamp(Image * const image,
  const double brightness,
  const int red, const int green, const int blue);

void DrawLed(Image * const image,
  const double ledBrightness,
  const int red, const int green, const int blue);

//Get a pixel's RGB values
//From http://www.richelbilderbeek.nl/CppGetPixel.htm
void GetPixel(
  const Image * const image,
  const int x,
  const int y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue);

const std::vector<QRect> GetRectsHorizontal(const QRect& rect, const int nRects);
const std::vector<QRect> GetRectsVertical(const QRect& rect, const int nRects);
//Y-X-ordered
const std::vector<std::vector<QRect> > GetRectsGrid(
  const QRect& rect, const int nCols, const int nRows);

const bool IsWhite(const Image * const image, const int x, const int y);

const bool OnImage(const int x, const int y,
  const Image * const image);

//From http://www.richelbilderbeek.nl/CppPaint.htm
void Paint(Image * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  );

//From http://www.richelbilderbeek.nl/CppPaint.htm
void Paint(Image * const image, const QColor& color);

//Paint the moving grey background used in the menus
void PaintWavyBackground(Image * const image);

//Make the image one shade lighter, used in the menus
void TickBackground(Image * const image);

void PlaceInCenter(Image * const image, const QRect& rect);

const QRect MergeRects(const QRect& r1, const QRect& r2);

//Set a pixel's RGB values
//From http://www.richelbilderbeek.nl/CppSetPixel.htm
void SetPixel(
  Image * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue);

//Resize the picture of an image, keeping the current content
void SetPictureSize(Image * const image, const int width, const int height);
void SetPictureSize(Image * const image, const QRect& rect);
void SetPictureWidth(Image * const image, const int width);
void SetPictureHeight(Image * const image, const int height);
//---------------------------------------------------------------------------
#endif
