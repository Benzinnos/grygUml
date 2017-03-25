#ifndef USECASEACTOR_H
#define USECASEACTOR_H

#include <QObject>

#include "abstractumlitem.h"

namespace UmlDesigner {
namespace UmlPrimitives {

class UseCaseActor : public AbstractUmlItem
{
public:
  UseCaseActor();
  enum { Type = USECASEACTOR_TYPE };

  // QGraphicsItem interface
public:
  virtual QRectF boundingRect() const override;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  virtual int type() const override;
};

}
}

#endif // USECASEACTOR_H
