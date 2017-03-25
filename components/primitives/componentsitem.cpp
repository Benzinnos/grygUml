#include "componentsitem.h"

#include <QPainter>
#include <QLinearGradient>

using namespace UmlDesigner;
using namespace UmlDesigner::UmlPrimitives;

ComponentsItem::ComponentsItem()
{
  _containedText = "Components Item";
}


QRectF ComponentsItem::boundingRect() const
{
  return QRectF(0, 0, _textRect.width() + BORDER_OFFSET, _textRect.height() + BORDER_OFFSET);/*.united(_topRect);*/
}

void ComponentsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option) Q_UNUSED(widget);

  _textRect = painter->fontMetrics().boundingRect(QRect(), Qt::AlignHCenter, _containedText);

  //Paint
  if (isSelected()) {
    painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
  }

  QLinearGradient gradient(boundingRect().topLeft(), boundingRect().bottomRight()); // diagonal gradient from top-left to bottom-right
  gradient.setColorAt(0, Qt::yellow);
  gradient.setColorAt(1, Qt::white);
  painter->fillRect(boundingRect(), gradient);
  painter->drawRect(boundingRect());

  painter->drawText(boundingRect(), Qt::AlignCenter, _containedText);

  //Top rectangle
  QRectF addRect(0, 0, _textRect.width() + BORDER_OFFSET, _textRect.height() + BORDER_OFFSET);

  QPointF topRectStartPoint = boundingRect().topLeft();
  topRectStartPoint += QPointF(boundingRect().width()/2, -boundingRect().height()/2);
  _topRect = QRectF(topRectStartPoint, boundingRect().size()/2);
  painter->fillRect(_topRect, gradient);
  painter->drawRect(_topRect);

  painter->drawRect(boundingRect());
}

int ComponentsItem::type() const
{
  return Type;
}
