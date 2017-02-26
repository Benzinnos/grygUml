#ifndef DOMAINITEM_H
#define DOMAINITEM_H

#include <QObject>
#include <QGraphicsItem>

#include "domainarrow.h"

class DomainItem : public QGraphicsItem
{
public:
    enum { Type = UserType + 1 };
    DomainItem();
    ~DomainItem();

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QGraphicsItem interface
    QString containedText() const;
    void setContainedText(const QString &containedText);
    void addArrow(DomainArrow* arrow);
    void removeArrow(DomainArrow* arrow);
    void removeArrows();

protected:
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<DomainArrow*> _arrows;
    QString _containedText;

    // QGraphicsItem interface
protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    // QGraphicsItem interface
public:
    virtual int type() const override;
};

QDataStream &operator<<(QDataStream &out, const DomainItem &domainItem);
QDataStream &operator>>(QDataStream &in, DomainItem &domainItem);

#endif // DOMAINITEM_H
