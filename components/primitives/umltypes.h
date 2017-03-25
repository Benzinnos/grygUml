#ifndef UMLTYPES_H
#define UMLTYPES_H

#include <QGraphicsItem>

namespace UmlDesigner {
namespace UmlPrimitives {

enum {
  DOMAINITEM_TYPE     = QGraphicsItem::UserType + 1,
  DOMAINARROW_TYPE    = QGraphicsItem::UserType + 2,
  UMLLINE_TYPE        = QGraphicsItem::UserType + 3,
  USECASEACTOR_TYPE   = QGraphicsItem::UserType + 4,
  USECASELINE_TYPE    = QGraphicsItem::UserType + 5,
  USECASEACTION_TYPE  = QGraphicsItem::UserType + 6,
  COMPONENTSITEM_TYPE = QGraphicsItem::UserType + 7,
  COMPONENTSLINE_TYPE = QGraphicsItem::UserType + 8
};

}
}


#endif // UMLTYPES_H
