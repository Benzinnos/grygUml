#ifndef USECASEACTION_H
#define USECASEACTION_H

#include <QObject>

#include "abstractumlitem.h"

namespace UmlDesigner {
namespace UmlPrimitives {

class UseCaseAction : public AbstractUmlItem
{
  enum {
    BORDER_OFFSET = 5
  };
public:
  enum { Type = USECASEACTION_TYPE };

  UseCaseAction();

  // QGraphicsItem interface
public:
  virtual QRectF boundingRect() const override;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  virtual int type() const override;
};

}
}

#endif // USECASEACTION_H
