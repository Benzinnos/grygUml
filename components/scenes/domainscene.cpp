#include "domainscene.h"
#include <QImage>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

DomainScene::DomainScene()
  : _mode(MoveItem), _firstItem(nullptr), _seccondItem(nullptr)
{
}

bool DomainScene::saveImage(const QString &fileName, const char *fileFormat)
{
  clearSelection();
  setSceneRect(itemsBoundingRect());
  QImage image(sceneRect().size().toSize(), QImage::Format_ARGB32);
  image.fill(Qt::white);

  QPainter painter(&image);
  render(&painter);

  if (image.save(fileName, fileFormat)) {
    return true;
  }
  else {
    return false;
  }
}

void DomainScene::writeItemsToBinaryStream(QDataStream &out)
{
  // TODO Шаблонный метод
  foreach (QGraphicsItem* it, items()) {
    out << static_cast<quint32>(it->type());
    switch (it->type()) {
    case DomainItem::Type:
      out << *qgraphicsitem_cast<DomainItem*>(it);
      break;
    case DomainArrow::Type:
      out << *qgraphicsitem_cast<DomainArrow*>(it);
      break;
    default:
      break;
    }
  }
}

void DomainScene::readItemsFromBinaryStream(QDataStream &in)
{
  clear();

  // TODO Шаблонный метод
  // Список должен быть отсортирован. Элементы типа DomainItem должны быть первыми для корректного создания DomainArrow.
  while(!in.atEnd()) {
    quint32 type;
    in >> type;
    switch (static_cast<int>(type)) {
    case DomainItem::Type: {
      DomainItem *domainItem = new DomainItem();
      in >> *domainItem;
      addItem(domainItem);
      break;
    }
    case DomainArrow::Type: {
      QPointF firstItemPosition;
      QPointF endItemPosition;
      in >> firstItemPosition
         >> endItemPosition;
      DomainArrow *domainArrow = new DomainArrow(itemAt(firstItemPosition, QTransform()), itemAt(endItemPosition, QTransform()));
      in >> *domainArrow;
      qgraphicsitem_cast<DomainItem*>(itemAt(firstItemPosition, QTransform()))->addArrow(domainArrow);
      qgraphicsitem_cast<DomainItem*>(itemAt(endItemPosition, QTransform()))->addArrow(domainArrow);
      addItem(domainArrow);
      break;
    }
    default:
      break;
    }
  }

}


void DomainScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
  if (event->button() != Qt::LeftButton)
    return;

  if (_mode == InsertLine) {
    QList<QGraphicsItem*> list = items(event->scenePos());
    if (!list.isEmpty()) {
      _firstItem = list.first();
    }
    else {
      _mode = MoveItem;
    }
  }
  else {
    if (_mode == DeleteItem) {
      QList<QGraphicsItem*> list = items(event->scenePos());
      if (!list.isEmpty()) {
        deleteGraphicsItem(list.first());
      }
      else {
        _mode = MoveItem;
      }
    }
    else
      QGraphicsScene::mousePressEvent(event);
  }
}

void DomainScene::setMode(int mode)
{
  _mode = mode;
}

void DomainScene::deleteGraphicsItem(QGraphicsItem *item)
{
  if (item->type() == DomainArrow::Type) {
      DomainArrow* arrow = qgraphicsitem_cast<DomainArrow*>(item);
      qgraphicsitem_cast<DomainItem*>(arrow->startItem())->removeArrow(arrow);
      qgraphicsitem_cast<DomainItem*>(arrow->endItem())->removeArrow(arrow);
      removeItem(arrow);
      delete arrow;
  }
  if (item->type() == DomainItem::Type) {
      DomainItem* domainIt = qgraphicsitem_cast<DomainItem*>(item);
      domainIt->removeArrows();
      removeItem(domainIt);
      delete domainIt;
  }
}


void DomainScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
  if (_mode == InsertLine) {
    QList<QGraphicsItem*> list = items(event->scenePos());
    if (!list.isEmpty()) {
      _seccondItem = list.first();
      DomainArrow* arrow = new DomainArrow(_firstItem, _seccondItem);
      qgraphicsitem_cast<DomainItem*>(_firstItem)->addArrow(arrow);
      qgraphicsitem_cast<DomainItem*>(_seccondItem)->addArrow(arrow);
      emit lineCreated(arrow);
    }
  }
  _mode = MoveItem;
  QGraphicsScene::mouseReleaseEvent(event);
}
