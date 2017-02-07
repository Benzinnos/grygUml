#ifndef DOMAINARROW_H
#define DOMAINARROW_H

#include <QObject>
#include <QGraphicsLineItem>

class DomainArrow : public QGraphicsLineItem
{
public:
  enum { Type = UserType + 2 };
  explicit DomainArrow(QGraphicsItem* startItem, QGraphicsItem* endItem, QGraphicsItem* parent = nullptr);

  // QGraphicsItem interface
public:
  virtual QRectF boundingRect() const override;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  virtual QPainterPath shape() const override;

  QGraphicsItem* startItem() const { return _myStartItem; }
  QGraphicsItem* endItem() const { return _myEndItem; }
  void updatePosition();

  QString containedText() const;
  void setContainedText(const QString &containedText);

protected:
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
  QGraphicsItem* _myStartItem;
  QGraphicsItem* _myEndItem;
  QPolygonF _arrowHead;
  QString _containedText;
  qreal _arrowSize = 10;


  // QGraphicsItem interface
public:
  virtual int type() const override;
};

#endif // DOMAINARROW_H
