#include "umlapi.h"
#include <qDebug>
#include "umlmainwidget.h"
#include <QFile>
#include <QDataStream>

UmlApi::UmlApi(DomainScene *scene, QObject *parent)
    : _scene(scene), _parent(parent)
{
}

void UmlApi::recursiveShift(QGraphicsItem* item)
{
    foreach (QGraphicsItem* it, _scene->items()) {
//        if (it->type() != DomainItem::Type) continue;
        if (it == item) continue;
        if (item->collidesWithItem(it)) {
            item->moveBy(30.0, 0);
        }
        if (item->collidesWithItem(it)) {
            item->moveBy(0, 30.0);
            recursiveShift(item);
        }
    }
}

void UmlApi::addDomainItem(QString itemText)
{
//    DomainItem* item = new DomainItem();
//    item->setContainedText(itemText);
//    _scene->addItem(item);
    /*
     * TODO Тут должен быть менеджер компоновки
     * А пока тут просто сдвиг айтема при коллизии
     */
//    recursiveShift(item);
}

void UmlApi::addDomainItem(QString itemText, QPointF pos)
{
//    DomainItem* item = new DomainItem();
//    item->setContainedText(itemText);
//    _scene->addItem(item);
//    item->setPos(pos);
}

bool UmlApi::addDomainLine(QString startItemText, QString endItemText, QString lineText)
{
    if (startItemText == endItemText) {
        return false;
    }
    QGraphicsItem* startItem = nullptr;
    QGraphicsItem* endItem = nullptr;
    foreach (QGraphicsItem* it, _scene->items()) {
//        if (it->type() != DomainItem::Type) continue;
//        DomainItem* domainIt = qgraphicsitem_cast<DomainItem*>(it);
//        if (domainIt->containedText() == startItemText) {
//            startItem = it;
//        }
//        if (domainIt->containedText() == endItemText) {
//            endItem = it;
//        }
//        if ((startItem != nullptr) && (endItem != nullptr)) {
//            break;
//        }
    }
    if ((startItem != nullptr) && (endItem != nullptr)) {
        DomainArrow* arrow = new DomainArrow(startItem, endItem);
        arrow->setContainedText(lineText);
        _scene->addItem(arrow);
        return true;
    }
    else {
        return false;
    }
}

bool UmlApi::moveDomainItem(QString itemText, QPointF newPos)
{
//    foreach (QGraphicsItem* it, _scene->items()) {
//        if (it->type() != DomainItem::Type) continue;
//        DomainItem* domainIt = qgraphicsitem_cast<DomainItem*>(it);
//        if (domainIt->containedText() == itemText) {
//            domainIt->setPos(newPos);
//            return true;
//        }
//    }
    return false;
}

void UmlApi::dumpScene()
{
    foreach (QGraphicsItem* it, _scene->items()) {
        qDebug() << "---------------------------------";
        qDebug() << "Item type: " << it->type();
        qDebug() << QString("Item position: x=%1, y=%2").arg(it->scenePos().x()).arg(it->scenePos().y());
        if (it->type() == DomainArrow::Type) {
            DomainArrow* arrow = qgraphicsitem_cast<DomainArrow*>(it);
            qDebug() << QString("Arrow contained text: %1").arg(arrow->containedText());
//            DomainItem* item = qgraphicsitem_cast<DomainItem*>(arrow->startItem());
//            qDebug() << QString("Arrow start item: %1, x=%2, y=%3").arg(item->containedText()).arg(item->scenePos().x()).arg(item->scenePos().y());
//            item = qgraphicsitem_cast<DomainItem*>(arrow->endItem());
//            qDebug() << QString("Arrow end item: %1, x=%2, y=%3").arg(item->containedText()).arg(item->scenePos().x()).arg(item->scenePos().y());
        }
//        if (it->type() == DomainItem::Type) {
//            DomainItem* domainIt = qgraphicsitem_cast<DomainItem*>(it);
//            qDebug() << QString("Item contained text: %1").arg(domainIt->containedText());
//            // TODO Также можно вывести айтемы, связанные стрелкой, так как стрелка имеет указатели на айтемы.
//        }
    }
}

bool UmlApi::removeItem(QString itemText)
{
    foreach (QGraphicsItem* it, _scene->items()) {
        if (it->type() == DomainArrow::Type) {
            DomainArrow* arrow = qgraphicsitem_cast<DomainArrow*>(it);
            if (arrow->containedText() == itemText) {
              _scene->deleteGraphicsItem(it);
              return true;
            }
        }
//        if (it->type() == DomainItem::Type) {
//            DomainItem* domainIt = qgraphicsitem_cast<DomainItem*>(it);
//            if (domainIt->containedText() == itemText) {
//                _scene->deleteGraphicsItem(it);
//                return true;
//            }
//        }
    }
    return false;
}

bool UmlApi::saveSceneImage(QString fileName)
{
    if (!_parent) return false;
    UmlMainWidget* wgt = static_cast<UmlMainWidget*>(_parent);
    return wgt->savePicture(fileName);
}

bool UmlApi::saveDomainFile(QString fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
    return false;
  }

  QDataStream stream(&file);
  _scene->writeItemsToBinaryStream(stream);
  file.close();
  return true;
}

bool UmlApi::loadDomainFile(QString fileName)
{
  QFile file(fileName);
  if (!file.open(QIODevice::ReadOnly)) {
    return false;
  }

  QDataStream stream(&file);
  _scene->readItemsFromBinaryStream(stream);
  file.close();
  return true;
}
