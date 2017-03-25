#ifndef DOMAINITEM_H
#define DOMAINITEM_H

#include <QObject>
#include <QGraphicsItem>

#include "abstractumlitem.h"

namespace UmlDesigner {
namespace UmlPrimitives {

class DomainItem : public AbstractUmlItem
{
public:
  enum { Type = DOMAINITEM_TYPE };
  DomainItem();

  // QGraphicsItem interface
public:
  virtual QRectF boundingRect() const override;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:

private:
  enum {
    BORDER_OFFSET = 5
  };

  // QGraphicsItem interface
public:
  virtual int type() const override;
};

}
}

#endif // DOMAINITEM_H
