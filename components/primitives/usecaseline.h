#ifndef USECASELINE_H
#define USECASELINE_H

#include <QObject>

#include "umllineitem.h"

namespace UmlDesigner {
namespace UmlPrimitives {

class UseCaseLine : public UmlLineItem
{
public:
  enum { Type = USECASELINE_TYPE };

  UseCaseLine(QGraphicsItem* startItem, QGraphicsItem* endItem, QGraphicsItem* parent = nullptr);

  // QGraphicsItem interface
public:
  virtual int type() const override { return Type; }

  // UmlLineItem interface
protected:
  virtual QPolygonF createArrow(QPointF p1, qreal size) override;
};

}
}

#endif // USECASELINE_H
