#ifndef DOMAINARROW_H
#define DOMAINARROW_H

#include <QObject>
#include <QGraphicsLineItem>

class DomainArrow : public QGraphicsLineItem
{
  friend QDataStream &operator<<(QDataStream &out, const DomainArrow &domainArrow);
  friend QDataStream &operator>>(QDataStream &in, DomainArrow &domainArrow);

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
  QString startItemContainedText() const;
  QString endItemContainedText() const;
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
  qreal _arrowSize = 8;
  QPointF _startItemPosition;
  QPointF _endItemPosition;

  // QGraphicsItem interface
public:
  virtual int type() const override;
};

QDataStream &operator<<(QDataStream &out, const DomainArrow &domainArrow);
QDataStream &operator>>(QDataStream &in, DomainArrow &domainArrow);

#endif // DOMAINARROW_H
