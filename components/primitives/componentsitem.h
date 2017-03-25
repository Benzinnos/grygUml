#ifndef COMPONENTSITEM_H
#define COMPONENTSITEM_H

#include <QObject>

#include "abstractumlitem.h"

namespace UmlDesigner {
namespace UmlPrimitives {

class ComponentsItem : public AbstractUmlItem
{
  enum {
    BORDER_OFFSET = 5
  };
  QRectF _topRect;

public:
  enum { Type = COMPONENTSITEM_TYPE };

  ComponentsItem();

  // QGraphicsItem interface
public:
  virtual QRectF boundingRect() const override;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  virtual int type() const override;
};

}
}

#endif // COMPONENTSITEM_H
