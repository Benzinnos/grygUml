#ifndef UMLLINEITEM_H
#define UMLLINEITEM_H

#include <QObject>
#include <QGraphicsLineItem>

namespace UmlDesigner {
namespace UmlPrimitives {

class UmlLineItem : public QGraphicsLineItem
{
public:
  enum { Type = UserType + 2 };

  UmlLineItem(QGraphicsItem* startItem, QGraphicsItem* endItem, QGraphicsItem* parent = nullptr);

  QGraphicsItem* startItem() const { return _myStartItem; }
  QGraphicsItem* endItem() const { return _myEndItem; }
  void updatePosition();
  QString containedText() const;
  void setContainedText(const QString &containedText);

  // QGraphicsItem interface
public:
  virtual QRectF boundingRect() const override;
  virtual QPainterPath shape() const override;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  virtual int type() const override;

private:
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
  QGraphicsItem* _myStartItem;
  QGraphicsItem* _myEndItem;
  QPolygonF _arrowHead;
  QString _containedText;
  qreal _arrowSize = 12;
  QPointF _startItemPosition;
  QPointF _endItemPosition;
  QRectF _textRect; // Область вокруг _containedText
};

}
}

#endif // UMLLINEITEM_H
