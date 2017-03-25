#ifndef COMPONENTSLINE_H
#define COMPONENTSLINE_H

#include <QObject>

#include "umllineitem.h"

namespace UmlDesigner {
namespace UmlPrimitives {

class ComponentsLine : public UmlLineItem
{
public:
  enum { Type = COMPONENTSLINE_TYPE };

  ComponentsLine(QGraphicsItem* startItem, QGraphicsItem* endItem, QGraphicsItem* parent = nullptr);

  // QGraphicsItem interface
public:
  virtual int type() const override;
};

}
}

#endif // COMPONENTSLINE_H
