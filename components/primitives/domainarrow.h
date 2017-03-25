#ifndef DOMAINARROW_H
#define DOMAINARROW_H

#include <QObject>

#include "umllineitem.h"

namespace UmlDesigner {
namespace UmlPrimitives {

class DomainArrow : public UmlLineItem
{
public:
  enum { Type = DOMAINARROW_TYPE };
  explicit DomainArrow(QGraphicsItem* startItem, QGraphicsItem* endItem, QGraphicsItem* parent = nullptr);

  // QGraphicsItem interface
public:
  virtual int type() const override { return Type; }

  // UmlLineItem interface
protected:
  virtual QPolygonF createArrow(QPointF p1, qreal size) override;
};

}
}

#endif // DOMAINARROW_H
