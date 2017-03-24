#include "abstractumlitem.h"

#include <QInputDialog>
#include <QGraphicsScene>

using namespace UmlDesigner;
using namespace UmlDesigner::UmlPrimitives;

AbstractUmlItem::AbstractUmlItem()
{
  setFlag(QGraphicsItem::ItemIsMovable, true);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
  setFlag(QGraphicsItem::ItemIsFocusable, true);
}

QString AbstractUmlItem::containedText() const
{
  return _containedText;
}

void AbstractUmlItem::setContainedText(const QString &containedText)
{
  _containedText = containedText;
}

QString AbstractUmlItem::itemDiscription() const
{
  return _itemDiscription;
}

void AbstractUmlItem::setItemDiscription(const QString &itemDiscription)
{
  _itemDiscription = itemDiscription;
}

void AbstractUmlItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
  Q_UNUSED(event)

  bool ok(false);
  QString str = QInputDialog::getMultiLineText(nullptr, QString("Введите текст"), QString("Текст"), _containedText, &ok);
  if (ok) {
    _containedText = str;
  }
}

void AbstractUmlItem::addUmlLine(UmlLineItem *umlLine)
{
  _umlLines.append(umlLine);
}

void AbstractUmlItem::removeUmlLine(UmlLineItem *umlLine)
{
  int index = _umlLines.indexOf(umlLine);

  if (index != -1)
    _umlLines.removeAt(index);
}

void AbstractUmlItem::removeUmlLines()
{
  foreach (UmlLineItem* umlLine, _umlLines) {
    AbstractUmlItem* startItem = dynamic_cast<AbstractUmlItem*>(umlLine->startItem());
    Q_ASSERT(startItem);
    startItem->removeUmlLine(umlLine);

    AbstractUmlItem* endItem = dynamic_cast<AbstractUmlItem*>(umlLine->endItem());
    Q_ASSERT(endItem);
    endItem->removeUmlLine(umlLine);

    scene()->removeItem(umlLine);
    delete umlLine;
  }
}

QVariant AbstractUmlItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
  if (change == QGraphicsItem::ItemPositionChange) {
    foreach (UmlLineItem* umlLine, _umlLines) {
      umlLine->updatePosition();
    }
  }

  return value;
}

/* Related non-members */

QDataStream &operator<<(QDataStream &out, const AbstractUmlItem &item)
{
  out << item.pos()
      << item.containedText()
      << item.itemDiscription();

  return out;
}


QDataStream &operator>>(QDataStream &in, AbstractUmlItem &item)
{
  QPointF position;
  QString containedText;
  QString itemDiscripton;

  in  >> position
      >> containedText
      >> itemDiscripton;

  item.setPos(position);
  item.setContainedText(containedText);
  item.setItemDiscription(itemDiscripton);

  return in;
}
