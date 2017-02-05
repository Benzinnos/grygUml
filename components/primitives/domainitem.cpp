#include "domainitem.h"
#include <QPainter>

DomainItem::DomainItem()
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}


QRectF DomainItem::boundingRect() const
{
    //TODO Ультраговнокод. Переделать как fontSize*string->size()
    return QRectF(0, 0, this->data(0).toString().size()*7/* Типо fontSize */, 15 /* Высота шрифта + смещение? */);
}

void DomainItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option) Q_UNUSED(widget);

    painter->drawRect(boundingRect());
    painter->drawText(boundingRect(), this->data(0).toString()); //TODO Смещение текста по центру
}
