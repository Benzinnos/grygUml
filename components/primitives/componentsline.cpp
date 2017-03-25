#include "componentsline.h"

using namespace UmlDesigner;
using namespace UmlDesigner::UmlPrimitives;

ComponentsLine::ComponentsLine(QGraphicsItem *startItem, QGraphicsItem *endItem, QGraphicsItem *parent)
  : UmlLineItem(startItem, endItem, parent)
{
  _fillArrowHead = false;
}


int UmlDesigner::UmlPrimitives::ComponentsLine::type() const
{
  return Type;
}
