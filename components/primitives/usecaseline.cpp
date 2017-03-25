#include "usecaseline.h"

using namespace UmlDesigner;
using namespace UmlDesigner::UmlPrimitives;

UseCaseLine::UseCaseLine(QGraphicsItem *startItem, QGraphicsItem *endItem, QGraphicsItem *parent)
  : UmlLineItem(startItem, endItem, parent)
{
}

QPolygonF UseCaseLine::createArrow(QPointF p1, qreal size)
{
  Q_UNUSED(p1);
  Q_UNUSED(size);

  return QPolygonF();
}
