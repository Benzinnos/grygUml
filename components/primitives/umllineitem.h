#ifndef UMLLINEITEM_H
#define UMLLINEITEM_H

#include <QObject>
#include <QGraphicsLineItem>
#include <QPen>

#include "umltypes.h"

namespace UmlDesigner {
namespace UmlPrimitives {

class UmlLineItem : public QGraphicsLineItem
{
  //FIXME Friend functions почему то не получают доступ к private класса? Возможно из-за nsmespace
  friend QDataStream &operator<<(QDataStream &out, const UmlLineItem &lineItem);
  friend QDataStream &operator>>(QDataStream &in, UmlLineItem &lineItem);

public:
  enum { Type = UMLLINE_TYPE };

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

  enum {
    LINE_WIDTH = 1
  };

protected:
  virtual QPolygonF createArrow(QPointF p1, qreal size);
  QPen _linePen;
  bool _fillArrowHead;
};

QDataStream &operator<<(QDataStream &out, const UmlLineItem &lineItem);
QDataStream &operator>>(QDataStream &in, UmlLineItem &lineItem);

}
}

#endif // UMLLINEITEM_H
