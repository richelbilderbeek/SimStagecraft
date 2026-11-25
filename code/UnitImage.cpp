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
#include "UnitImage.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <QPainter>
#include <QPen>

#include "UnitFunctions.h"
//---------------------------------------------------------------------------
namespace {

//Like the Windows GDI Rectangle and Ellipse: (x2,y2) is excluded
QRect GdiRect(const int x1, const int y1, const int x2, const int y2)
{
  return QRect(x1, y1, std::max(0, x2 - x1 - 1), std::max(0, y2 - y1 - 1));
}

void PreparePainter(QPainter& painter, const QColor& penColor,
  const int penWidth, const QColor& brushColor)
{
  painter.setRenderHint(QPainter::Antialiasing, false);
  QPen pen(penColor);
  pen.setWidth(penWidth);
  painter.setPen(pen);
  painter.setBrush(brushColor);
}

} //~namespace
//---------------------------------------------------------------------------
Image::Image(const QString& name_, const QString& resource,
  const int left_, const int top_, const int width_, const int height_,
  const bool transparent_, const bool visible_, const bool autoSize_)
  : name(name_),
    left(left_), top(top_), width(width_), height(height_),
    transparent(transparent_), visible(visible_), autoSize(autoSize_)
{
  if (!resource.isEmpty())
  {
    picture = QImage(resource).convertToFormat(QImage::Format_RGB32);
    assert(!picture.isNull() && "Resource must exist");
  }
}
//---------------------------------------------------------------------------
void Image::AssignPicture(const Image * const other)
{
  assert(other);
  picture = other->picture;
  transparentColor = other->transparentColor;
  PictureChanged();
}
//---------------------------------------------------------------------------
void Image::PictureChanged()
{
  if (autoSize && !picture.isNull())
  {
    width = picture.width();
    height = picture.height();
  }
}
//---------------------------------------------------------------------------
QImage Image::Graphic() const
{
  if (!transparent || picture.isNull()) return picture;
  const QRgb key
    = (transparentColor ? *transparentColor : picture.pixel(0, picture.height() - 1))
    & 0x00FFFFFF;
  QImage result = picture.convertToFormat(QImage::Format_ARGB32);
  const int maxx = result.width();
  const int maxy = result.height();
  for (int y = 0; y != maxy; ++y)
  {
    QRgb * const line = reinterpret_cast<QRgb*>(result.scanLine(y));
    for (int x = 0; x != maxx; ++x)
    {
      if ((line[x] & 0x00FFFFFF) == key) line[x] = 0;
    }
  }
  return result;
}
//---------------------------------------------------------------------------
Image * ImageStore::Add(const char * const name, const char * const resource,
  const int left, const int top, const int width, const int height,
  const bool transparent, const bool visible, const bool autoSize)
{
  mImages.push_back(std::make_unique<Image>(
    QString::fromUtf8(name), QString::fromUtf8(resource),
    left, top, width, height, transparent, visible, autoSize));
  return mImages.back().get();
}
//---------------------------------------------------------------------------
//Makes all red pixels even, except when there's a message pixel
//From http://www.richelbilderbeek.nl/CppAddMessageRed.htm
void AddMessageRed(
  const Image * const original,
  const Image * const message,
  Image * const result)
{
  assert(original!=0 && "Image is NULL");
  assert(message!=0 && "Image is NULL");
  assert(result!=0 && "Image is NULL");
  //Get sizes and set size
  const int widthOriginal = original->picture.width();
  const int widthMessage  = message->picture.width();
  const int width = std::min(widthOriginal, widthMessage);
  const int heightOriginal = original->picture.height();
  const int heightMessage  = message->picture.height();
  const int height = std::min(heightOriginal, heightMessage);
  SetPictureSize(result,width,height);
  //Get the pixel offsets
  const int dx1 = (widthOriginal  - width ) / 2;
  const int dx2 = (widthMessage   - width ) / 2;
  const int dy1 = (heightOriginal - height) / 2;
  const int dy2 = (heightMessage  - height) / 2;
  for (int y=0; y!=height; ++y)
  {
    for(int x=0; x!=width; ++x)
    {
      unsigned char r = 0;
      unsigned char g = 0;
      unsigned char b = 0;
      //Get original's pixel
      GetPixel(original,dx1 + x,dy1 + y,r,g,b);
      //Make colors even by increment, watch out for 256
      if (r%2 != 0)
      {
        if (r == 255) {--r;}
        else { ++r; }
      }
      assert(r%2 == 0);
      //Add message
      if (IsWhite(message,dx2 + x,dy2 + y)) ++r;
      //Write to result image
      SetPixel(result,x,y,r,g,b);
    }
  }
}
//---------------------------------------------------------------------------
void Blacken(Image * const image, const double intensity)
{
  assert(image != 0);
  const int maxx = image->picture.width();
  const int maxy = image->picture.height();
  for (int y = 0; y != maxy; ++y)
  {
    QRgb * const line = reinterpret_cast<QRgb*>(image->picture.scanLine(y));
    for (int x = 0; x != maxx; ++x)
    {
      const int r = static_cast<int>(qRed(line[x])   * (1.0 - intensity));
      const int g = static_cast<int>(qGreen(line[x]) * (1.0 - intensity));
      const int b = static_cast<int>(qBlue(line[x])  * (1.0 - intensity));
      line[x] = qRgb(r,g,b);
    }
  }
}
//---------------------------------------------------------------------------
void CreateWatermark(
  const Image * const original,
  Image * const image)
{
  assert(original != 0);
  assert(image != 0);
  const int maxx = original->picture.width();
  const int maxy = original->picture.height();
  image->picture = QImage(maxx, maxy, QImage::Format_RGB32);
  for (int y = 0; y != maxy; ++y)
  {
    const QRgb * const lineRead
      = reinterpret_cast<const QRgb*>(original->picture.constScanLine(y));
    QRgb * const lineWrite
      = reinterpret_cast<QRgb*>(image->picture.scanLine(y));
    for (int x = 0; x != maxx; ++x)
    {
      //The original code used blue + red + red, keep it as it was
      const int grey = ( qBlue(lineRead[x]) + qRed(lineRead[x])
        + qRed(lineRead[x]) ) / 3;
      const int c = std::min(255, (grey + 256) / 2);
      lineWrite[x] = qRgb(c,c,c);
    }
  }
  image->PictureChanged();
}
//---------------------------------------------------------------------------
void DrawAudioSignal(Image * const image, const double intensity)
{
  assert(image!=0);
  const int height = image->picture.height();
  const int width  = image->picture.width();
  const int dy = height / 10;
  const QColor white(Qt::white);
  const QColor red(255,0,0);
  const QColor orange(255,127,0);
  const QColor lime(0,255,0);
  //From top to bottom: the threshold and the color
  const double thresholds[10]
    = { 1.500, 1.333, 1.167, 1.000, 0.833, 0.667, 0.500, 0.333, 0.167, 0.000 };
  const QColor colors[10]
    = { red, orange, orange, orange, lime, lime, lime, lime, lime, lime };
  QPainter painter(&image->picture);
  for (int i=0; i!=10; ++i)
  {
    PreparePainter(painter, Qt::black, 1,
      intensity > thresholds[i] ? colors[i] : white);
    painter.drawRect(GdiRect(0,i*dy,width,(i+1)*dy));
  }
}
//---------------------------------------------------------------------------
void DrawDial(Image * const image, const int x, const int y,
  const QColor& color)
{
  assert(image!=0);
  const int width  = image->picture.width();
  const int height = image->picture.height();
  //Clear image
  image->transparentColor = qRgb(0,255,0);
  Paint(image,0,255,0);
  QPainter painter(&image->picture);
  //Draw knob
  PreparePainter(painter, Qt::black, 1, color);
  painter.drawEllipse(GdiRect(0,0,width,height));
  //Draw pointer
  const int midX = width / 2;
  const int midY = height / 2;
  const double ray = static_cast<double>(std::min( midX, midY ));
  const double angle
    = GetAngle( static_cast<double>(x - midX),
        static_cast<double>(y - midY));
  const int pointerX
    = static_cast<int>( static_cast<double>(midX) + (std::sin(angle) * ray) );
  const int pointerY
    = static_cast<int>( static_cast<double>(midY) - (std::cos(angle) * ray) );
  PreparePainter(painter, Qt::black, 4, color);
  painter.drawLine(midX,midY,pointerX,pointerY);
}
//---------------------------------------------------------------------------
void DrawFader(Image * const image, const int faderY)
{
  assert(image!=0);
  assert(faderY >= 0);
  const int width  = image->picture.width();
  const int height = image->picture.height();
  assert(faderY < height);
  const int trenchWidth = 4;
  const int trenchMidX = width / 2;
  const int faderHeight = width / 2;
  const int faderMidY = (faderY < (faderHeight / 2) ? (faderHeight / 2) :
    (faderY + (faderHeight / 2) > height ? height - (faderHeight / 2)   :
    faderY));
  //Clear image
  image->transparentColor = qRgb(0,255,0);
  Paint(image,0,255,0);
  QPainter painter(&image->picture);
  //Draw vertical trench
  PreparePainter(painter, Qt::black, trenchWidth, QColor(128,128,128));
  painter.drawLine(trenchMidX, 0, trenchMidX, height);
  //Draw fader
  PreparePainter(painter, Qt::black, 1, QColor(128,128,128));
  painter.drawRect(GdiRect(
    0,
    faderMidY  - (faderHeight / 2),
    width - 1,
    faderMidY  + (faderHeight / 2)));
}
//---------------------------------------------------------------------------
void DrawImage(Image * const target, const int x, const int y,
  const Image * const source)
{
  assert(target);
  assert(source);
  if (source->picture.isNull() || target->picture.isNull()) return;
  QPainter painter(&target->picture);
  painter.drawImage(x, y, source->Graphic());
}
//---------------------------------------------------------------------------
namespace {

//Draw the background of a lamp or LED, with an inverted color,
//so that it can be made transparent
void PaintInverted(Image * const image,
  const int red, const int green, const int blue)
{
  if (red == 255 && green == 255 && blue == 255)
  {
    Paint(image,0,255,0);
  }
  else
  {
    Paint(image, 255 - red, 255 - green, 255 - blue);
  }
}

QColor ShadeRgb(const double fR, const double fG, const double fB,
  const double brightness,
  const double minBrightness, const double maxBrightness)
{
  const int r = static_cast<int>(
    minBrightness + (fR * brightness * (maxBrightness - minBrightness) ) );
  const int g = static_cast<int>(
    minBrightness + (fG * brightness * (maxBrightness - minBrightness) ) );
  const int b = static_cast<int>(
    minBrightness + (fB * brightness * (maxBrightness - minBrightness) ) );
  assert( r >= 0 ); assert( r < 256);
  assert( g >= 0 ); assert( g < 256);
  assert( b >= 0 ); assert( b < 256);
  return QColor(r,g,b);
}

} //~namespace
//---------------------------------------------------------------------------
void DrawLamp(Image * const image,
  const double brightness,
  const int red, const int green, const int blue)
{
  assert(image!=0);
  assert(brightness >= 0.0);
  assert(brightness <= 1.0);
  //Create transparent background with inverted color
  PaintInverted(image,red,green,blue);
  const int width  = image->picture.width();
  const int height = image->picture.height();
  //Fraction red/green/blue
  const double fR = static_cast<double>(red  ) / 255.0;
  const double fG = static_cast<double>(green) / 255.0;
  const double fB = static_cast<double>(blue ) / 255.0;
  //Draw circle
  const double maxBrightness = 1.00* 255.0;
  const double minBrightness = 0.00 * maxBrightness;
  QPainter painter(&image->picture);
  PreparePainter(painter, Qt::black, 1 + (std::min(width,height) / 25),
    ShadeRgb(fR,fG,fB,brightness,minBrightness,maxBrightness));
  painter.drawEllipse(GdiRect(0,0,width,height));
}
//---------------------------------------------------------------------------
void DrawLed(Image * const image,
  const double ledBrightness,
  const int red, const int green, const int blue)
{
  assert(image!=0);
  assert(ledBrightness >= 0.0);
  assert(ledBrightness <= 1.0);
  //Create transparent background with inverted color
  PaintInverted(image,red,green,blue);
  const int width  = image->picture.width();
  const int height = image->picture.height();
  //Fraction red/green/blue
  const double fR = static_cast<double>(red  ) / 255.0;
  const double fG = static_cast<double>(green) / 255.0;
  const double fB = static_cast<double>(blue ) / 255.0;
  QPainter painter(&image->picture);
  {
    //Draw circle and major surface
    const double maxBrightness = 0.66 * 255.0;
    const double minBrightness = 0.25 * maxBrightness;
    PreparePainter(painter, Qt::black, 1 + (std::min(width,height) / 25),
      ShadeRgb(fR,fG,fB,ledBrightness,minBrightness,maxBrightness));
    painter.drawEllipse(GdiRect(0,0,width,height));
  }
  {
    //Draw topleft smaller lighter surface
    const double maxBrightness = 1.00 * 255.0;
    const double minBrightness = 0.25 * maxBrightness;
    const QColor c
      = ShadeRgb(fR,fG,fB,ledBrightness,minBrightness,maxBrightness);
    PreparePainter(painter, c, 1, c);
    const int x1 = (width  / 2) - (0.707 * static_cast<double>(width ) * 0.5);
    const int y1 = (height / 2) - (0.707 * static_cast<double>(height) * 0.5);
    const int x2 = width / 2;
    const int y2 = height / 2;
    painter.drawEllipse(GdiRect(x1,y1,x2,y2));
  }
  {
    //Draw bottomright smaller darker surface
    const double maxBrightness = 0.33 * 255.0;
    const double minBrightness = 0.25 * maxBrightness;
    const QColor c
      = ShadeRgb(fR,fG,fB,ledBrightness,minBrightness,maxBrightness);
    PreparePainter(painter, c, 1, c);
    const int x1 = (width  / 2) - 1;
    const int y1 = (height / 2) - 1;
    const int x2 = (width  / 2) + (0.707 * static_cast<double>(width ) * 0.5);
    const int y2 = (height / 2) + (0.707 * static_cast<double>(height) * 0.5);
    painter.drawEllipse(GdiRect(x1,y1,x2,y2));
  }
}
//---------------------------------------------------------------------------
//Get a pixel's RGB values
//From http://www.richelbilderbeek.nl/CppGetPixel.htm
void GetPixel(
  const Image * const image,
  const int x,
  const int y,
  unsigned char& red,
  unsigned char& green,
  unsigned char& blue)
{
  assert(image!=0 && "Image is NULL");
  assert( x >= 0 && "x coordinat is below zero");
  assert( y >= 0 && "y coordinat is below zero");
  assert( x < image->picture.width()  && "x coordinat is beyond image width");
  assert( y < image->picture.height() && "y coordinat is beyond image height");
  const QRgb p = image->picture.pixel(x,y);
  red   = qRed(p);
  green = qGreen(p);
  blue  = qBlue(p);
}
//---------------------------------------------------------------------------
const std::vector<QRect> GetRectsHorizontal(const QRect& rect, const int nRects)
{
  assert(nRects > 0);
  std::vector<QRect> rects;
  const int dx = rect.width() / nRects;
  for (int i=0; i!=nRects; ++i)
  {
    rects.push_back(QRect(rect.left() + (i * dx), rect.top(), dx, rect.height()));
  }
  return rects;
}
//---------------------------------------------------------------------------
const std::vector<QRect> GetRectsVertical(const QRect& rect, const int nRects)
{
  assert(nRects > 0);
  std::vector<QRect> rects;
  const int dy = rect.height() / nRects;
  for (int i=0; i!=nRects; ++i)
  {
    rects.push_back(QRect(rect.left(), rect.top() + (i * dy), rect.width(), dy));
  }
  return rects;
}
//---------------------------------------------------------------------------
//Y-X-ordered
const std::vector<std::vector<QRect> > GetRectsGrid(
  const QRect& rect, const int nCols, const int nRows)
{
  assert(nCols > 0);
  assert(nRows > 0);
  const std::vector<QRect> rowRects = GetRectsVertical(rect,nRows);
  assert(nRows == static_cast<int>(rowRects.size()));
  std::vector<std::vector<QRect> > rects(nRows,std::vector<QRect>(nCols));
  for (int i=0; i!=nRows; ++i)
  {
    rects[i] = GetRectsHorizontal(rowRects[i],nCols);
  }
  assert(nRows == static_cast<int>(rects.size()));
  assert(nCols == static_cast<int>(rects[0].size()));
  return rects;
}
//---------------------------------------------------------------------------
const bool IsWhite(const Image * const image, const int x, const int y)
{
  unsigned char r = 0;
  unsigned char g = 0;
  unsigned char b = 0;
  GetPixel(image,x,y,r,g,b);
  const int sum = static_cast<int>(r)
    + static_cast<int>(g)
    + static_cast<int>(b);
  return (sum / 3 > 127);
}
//---------------------------------------------------------------------------
const bool OnImage(const int x, const int y,
  const Image * const image)
{
  return ( x >= image->left
    && x < image->left + image->width
    && y >= image->top
    && y < image->top + image->height);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void Paint(Image * const image,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue  )
{
  assert(image!=0);
  image->picture.fill(qRgb(red,green,blue));
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppPaint.htm
void Paint(Image * const image, const QColor& color)
{
  assert(image!=0);
  image->picture.fill(color.rgb());
}
//---------------------------------------------------------------------------
void PaintWavyBackground(Image * const image)
{
  assert(image!=0);
  const int maxx = image->picture.width();
  const int maxy = image->picture.height();
  for (int y = 0; y != maxy; ++y)
  {
    QRgb * const line = reinterpret_cast<QRgb*>(image->picture.scanLine(y));
    const double yD = static_cast<double>(y);
    for (int x = 0; x != maxx; ++x)
    {
      const double xD = static_cast<double>(x);
      //Range z: -3 , +3
      const double zD
        = std::cos(xD / 30.0)
        + std::sin(yD / 45.0)
        - std::sin( (xD + yD) / 60.0);
      const int grey = std::min(255,
        static_cast<int>( (zD + 3.0) * (256.0 / 6.0) ));
      assert(grey >=   0);
      line[x] = qRgb(grey,grey,grey);
    }
  }
}
//---------------------------------------------------------------------------
void TickBackground(Image * const image)
{
  assert(image!=0);
  const int maxx = image->picture.width();
  const int maxy = image->picture.height();
  for (int y = 0; y != maxy; ++y)
  {
    QRgb * const line = reinterpret_cast<QRgb*>(image->picture.scanLine(y));
    for (int x = 0; x != maxx; ++x)
    {
      //Overflow is intended: the colors cycle from white to black
      line[x] = qRgb(
        (qRed(line[x])   + 1) % 256,
        (qGreen(line[x]) + 1) % 256,
        (qBlue(line[x])  + 1) % 256);
    }
  }
}
//---------------------------------------------------------------------------
void PlaceInCenter(Image * const image, const QRect& rect)
{
  assert(image!=0);
  image->left = rect.left() + (rect.width()  / 2) - (image->picture.width()  / 2);
  image->top  = rect.top()  + (rect.height() / 2) - (image->picture.height() / 2);
}
//---------------------------------------------------------------------------
const QRect MergeRects(const QRect& r1, const QRect& r2)
{
  return r1.united(r2);
}
//---------------------------------------------------------------------------
//Set a pixel's RGB values
//From http://www.richelbilderbeek.nl/CppSetPixel.htm
void SetPixel(
  Image * const image,
  const int x,
  const int y,
  const unsigned char red,
  const unsigned char green,
  const unsigned char blue)
{
  assert(image!=0 && "Image is NULL");
  assert( x >= 0 && "x coordinat is below zero");
  assert( y >= 0 && "y coordinat is below zero");
  assert( x < image->picture.width()  && "x coordinat is beyond image width");
  assert( y < image->picture.height() && "y coordinat is beyond image height");
  image->picture.setPixel(x,y,qRgb(red,green,blue));
}
//---------------------------------------------------------------------------
void SetPictureSize(Image * const image, const int width, const int height)
{
  assert(image);
  if (image->picture.width() == width && image->picture.height() == height) return;
  QImage resized(std::max(0,width), std::max(0,height), QImage::Format_RGB32);
  resized.fill(Qt::white);
  if (!image->picture.isNull())
  {
    QPainter painter(&resized);
    painter.drawImage(0,0,image->picture);
  }
  image->picture = resized;
  image->PictureChanged();
}
//---------------------------------------------------------------------------
void SetPictureSize(Image * const image, const QRect& rect)
{
  SetPictureSize(image, rect.width(), rect.height());
}
//---------------------------------------------------------------------------
void SetPictureWidth(Image * const image, const int width)
{
  SetPictureSize(image, width, image->picture.height());
}
//---------------------------------------------------------------------------
void SetPictureHeight(Image * const image, const int height)
{
  SetPictureSize(image, image->picture.width(), height);
}
//---------------------------------------------------------------------------
