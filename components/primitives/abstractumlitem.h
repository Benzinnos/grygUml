#ifndef ABSTRACTUMLITEM_H
#define ABSTRACTUMLITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QDataStream>

#include "umllineitem.h"

namespace UmlDesigner {
namespace UmlPrimitives {

class AbstractUmlItem : public QGraphicsItem
{
  friend QDataStream &operator<<(QDataStream &out, const AbstractUmlItem &item);
  friend QDataStream &operator>>(QDataStream &in, AbstractUmlItem &item);

public:
  AbstractUmlItem();

  QString containedText() const;
  void setContainedText(const QString &containedText);

  QString itemDiscription() const;
  void setItemDiscription(const QString &itemDiscription);
  void addUmlLine(UmlLineItem *umlLine);
  void removeUmlLine(UmlLineItem *umlLine);
  void removeUmlLines();

protected:
  QString _containedText; // Текст внутри айтема
  QString _itemDiscription; // TODO Описание -> property
  QRectF _textRect; // Область вокруг _containedText
  QList<UmlLineItem*> _umlLines;

  QVariant itemChange(GraphicsItemChange change, const QVariant &value);

  // QGraphicsItem interface
protected:
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

}
}

#endif // ABSTRACTUMLITEM_H
