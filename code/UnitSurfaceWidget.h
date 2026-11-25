//---------------------------------------------------------------------------
#ifndef UnitSurfaceWidgetH
#define UnitSurfaceWidgetH
//---------------------------------------------------------------------------
#include <functional>

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

#include "UnitImage.h"
//---------------------------------------------------------------------------
//A widget that shows an Image (its buffer) and passes its
//mouse and resize events on.
//It replaces drawing directly on a VCL TForm its Canvas
class SurfaceWidget : public QWidget
{
public:
  explicit SurfaceWidget(QWidget * const parent = nullptr)
    : QWidget(parent)
  {
    setMouseTracking(true);
    setAttribute(Qt::WA_OpaquePaintEvent);
  }

  //The Image to draw on the widget, at (left,top) of the Image
  const Image * buffer = nullptr;

  std::function<void(int,int)> onMouseDown;
  std::function<void(int,int)> onMouseMove;
  std::function<void(int,int)> onMouseUp;
  std::function<void()> onResize;

protected:
  void paintEvent(QPaintEvent *) override
  {
    QPainter painter(this);
    painter.fillRect(rect(), palette().window());
    if (buffer) painter.drawImage(buffer->left, buffer->top, buffer->picture);
  }
  void mousePressEvent(QMouseEvent * e) override
  {
    if (onMouseDown) onMouseDown(e->position().toPoint().x(), e->position().toPoint().y());
  }
  void mouseMoveEvent(QMouseEvent * e) override
  {
    if (onMouseMove) onMouseMove(e->position().toPoint().x(), e->position().toPoint().y());
  }
  void mouseReleaseEvent(QMouseEvent * e) override
  {
    if (onMouseUp) onMouseUp(e->position().toPoint().x(), e->position().toPoint().y());
  }
  void resizeEvent(QResizeEvent *) override
  {
    if (onResize) onResize();
  }
};
//---------------------------------------------------------------------------
#endif
