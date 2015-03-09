#include <QMouseEvent>
#include <QPainter>

#include "canvas.h"
#include "canvas_actions.h"

Canvas::Canvas(QWidget *parent) : QWidget(parent) {}

void Canvas::setSpline(Spline *value) { spline = value; }

void Canvas::mouseDoubleClickEvent(QMouseEvent *event) {
  QPointF pos = event->localPos();
  QPointF localPos = QPointF(pos.x() / width(), pos.y() / height());
  spline->undoStack->push(new AddPointCmd(localPos, spline));
  repaint();
}

void Canvas::paintEvent(QPaintEvent *) {
  QPainter painter(this);
  painter.setPen(QPen(Qt::red, 1, Qt::DashLine));
  for (size_t i = 0; i < spline->size() - 1; ++i) {
    QPointF a = spline->at(i), b = spline->at(i + 1);
    painter.drawLine(a.x() * width(), a.y() * height(), b.x() * width(),
                     b.y() * height());
  }
}

void Canvas::undoCmd() {
  spline->undoStack->undo();
  repaint();
}