#include "domainarrow.h"

using namespace UmlDesigner;
using namespace UmlDesigner::UmlPrimitives;

DomainArrow::DomainArrow(QGraphicsItem *startItem, QGraphicsItem *endItem, QGraphicsItem *parent)
  : UmlLineItem(startItem, endItem, parent)
{
}


QPolygonF UmlDesigner::UmlPrimitives::DomainArrow::createArrow(QPointF p1, qreal size)
{
  p1 = line().pointAt(0.5);

  double angle = ::acos(line().dx() / line().length());
  if (line().dy() >= 0)
      angle = (M_PI * 2) - angle;

  QPointF arrowP1 = p1 + QPointF(sin(angle + M_PI / 3) * size,
                                  cos(angle + M_PI / 3) * size);
  QPointF arrowP2 = p1 + QPointF(sin(angle + M_PI - M_PI / 3) * size,
                                  cos(angle + M_PI - M_PI / 3) * size);

  return QPolygonF() << p1 << arrowP1 << arrowP2;
}
