#include "domainscene.h"
#include <QImage>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

DomainScene::DomainScene()
  : _mode(MoveItem), _firstItem(nullptr), _seccondItem(nullptr)
{
}

//bool DomainScene::saveImage(const QString &fileName, const char *fileFormat)
//{
//    clearSelection();
////    setSceneRect(itemsBoundingRect());
//    QImage image(sceneRect().size().toSize(), QImage::Format_ARGB32);
//    image.fill(Qt::white);

//    QPainter painter(&image);
//    render(&painter);

//    if (image.save(fileName + ".png"))
//    {
//        return true;
//    }
//    else
//        return false;
//}


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
     QGraphicsScene::mousePressEvent(event);
  }
}

void DomainScene::setMode(int mode)
{
  _mode = mode;
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
