#ifndef DOMAINITEM_H
#define DOMAINITEM_H

#include <QObject>
#include <QGraphicsItem>

class DomainItem : public QGraphicsItem
{
public:
    DomainItem();

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // DOMAINITEM_H
