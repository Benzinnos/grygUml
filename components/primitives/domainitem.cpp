#include "domainitem.h"
#include <QPainter>
#include <QLinearGradient>

using namespace UmlDesigner;
using namespace UmlDesigner::UmlPrimitives;

DomainItem::DomainItem()
  : AbstractUmlItem()
{
  _containedText = "Domain Item";
}

QRectF DomainItem::boundingRect() const
{
  return QRectF(0, 0, _textRect.width() + BORDER_OFFSET, _textRect.height() + BORDER_OFFSET);
}

void DomainItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option) Q_UNUSED(widget);

  _textRect = painter->fontMetrics().boundingRect(QRect(), Qt::AlignHCenter, _containedText);

  if (isSelected()) {
    painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
  }

  QLinearGradient gradient(boundingRect().topLeft(), boundingRect().bottomRight()); // diagonal gradient from top-left to bottom-right
  gradient.setColorAt(0, Qt::yellow);
  gradient.setColorAt(1, Qt::white);
  painter->fillRect(boundingRect(), gradient);
  painter->drawRect(boundingRect());

  painter->drawText(boundingRect(), Qt::AlignCenter, _containedText);
  setData(0, _containedText);
}

int DomainItem::type() const
{
  return Type;
}
