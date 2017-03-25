#include "umllineitem.h"

#include <QPainter>
#include <QInputDialog>
#include <math.h>

using namespace UmlDesigner;
using namespace UmlDesigner::UmlPrimitives;

UmlLineItem::UmlLineItem(QGraphicsItem *startItem, QGraphicsItem *endItem, QGraphicsItem *parent)
  : QGraphicsLineItem(parent),
    _myStartItem(startItem),
    _myEndItem(endItem),
    _containedText("Text"),
    _linePen(Qt::black, LINE_WIDTH, Qt::SolidLine),
    _fillArrowHead(true)
{
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setZValue(-1000.0);
  setPen(_linePen);
}

void UmlLineItem::updatePosition()
{
  QLineF line(mapFromItem(_myStartItem, 0, 0), mapFromItem(_myEndItem, 0, 0));
  setLine(line);
}

QString UmlLineItem::containedText() const
{
  return _containedText;
}

void UmlLineItem::setContainedText(const QString &containedText)
{
  _containedText = containedText;
}

QRectF UmlLineItem::boundingRect() const
{
  qreal extra = (pen().width() + 20) / 2.0;
  QRectF retRect = QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                     line().p2().y() - line().p1().y()))
       .normalized()
       .adjusted(-extra, -extra, extra, extra);

  return retRect.united(_textRect);
}

QPainterPath UmlLineItem::shape() const
{
  QPainterPath path = QGraphicsLineItem::shape();
  path.addPolygon(_arrowHead);
  return path;
}

void UmlLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option);
  Q_UNUSED(widget);

   _startItemPosition = _myStartItem->pos();
   _endItemPosition = _myEndItem->pos();

  if (_myStartItem->collidesWithItem(_myEndItem))
      return;

  /* Line */
  QLineF centerLine(QRectF(_myStartItem->pos(), _myStartItem->boundingRect().size()).center(),
                    QRectF(_myEndItem->pos(), _myEndItem->boundingRect().size()).center());

  QPolygonF endPolygon = QPolygonF(_myEndItem->boundingRect());
  QPointF p1 = endPolygon.first() + _myEndItem->pos();
  QPointF p2;
  QPointF intersectPoint;
  QLineF polyLine;
  for (int i = 1; i < endPolygon.count(); ++i) {
      p2 = endPolygon.at(i) + _myEndItem->pos();
      polyLine = QLineF(p1, p2);
      QLineF::IntersectType intersectType =
          polyLine.intersect(centerLine, &intersectPoint);
      if (intersectType == QLineF::BoundedIntersection)
          break;
      p1 = p2;
  }

  setLine(QLineF(intersectPoint, QRectF(_myStartItem->pos(), _myStartItem->boundingRect().size()).center()));

  /* Arrow */
  _arrowHead = createArrow(line().p1(), _arrowSize);

  /* Paint */
  painter->drawLine(line());

  if (_fillArrowHead) {
    QPainterPath tmpPath;
    tmpPath.addPolygon(_arrowHead);
    painter->fillPath(tmpPath, QBrush (QColor ("black")));
  }
  else {
    painter->drawPolygon(_arrowHead);
  }

  /* On selected */
  if (isSelected()) {
      painter->setPen(QPen(Qt::black, LINE_WIDTH, Qt::DashLine));
      QLineF myLine = line();
      myLine.translate(0, 4.0);
      painter->drawLine(myLine);
      myLine.translate(0,-8.0);
      painter->drawLine(myLine);
  }

  _textRect = painter->fontMetrics().boundingRect(boundingRect().toRect(), Qt::AlignCenter,  _containedText);
  QPointF textPoint(_textRect.topLeft());

  _textRect = painter->fontMetrics().boundingRect(QRect(textPoint.toPoint(), QSize()), Qt::AlignCenter, _containedText);

  painter->drawText(_textRect, _containedText);
}

QPolygonF UmlLineItem::createArrow(QPointF p1, qreal size)
{
  double angle = ::acos(line().dx() / line().length());
  if (line().dy() >= 0)
      angle = (M_PI * 2) - angle;

  QPointF arrowP1 = p1 + QPointF(sin(angle + M_PI / 3) * size,
                                  cos(angle + M_PI / 3) * size);
  QPointF arrowP2 = p1 + QPointF(sin(angle + M_PI - M_PI / 3) * size,
                                  cos(angle + M_PI - M_PI / 3) * size);

  return QPolygonF() << p1 << arrowP1 << arrowP2;
}

int UmlLineItem::type() const
{
  return Type;
}

void UmlLineItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
  Q_UNUSED(event)

  bool ok(false);
  QString str = QInputDialog::getMultiLineText(nullptr, QString("Введите текст"), QString("Текст"), _containedText, &ok);
  if (ok) {
    _containedText = str;
  }
}


/* Related non-member */

QDataStream &operator<<(QDataStream &out, const UmlLineItem &lineItem)
{
  //FIXME Костыль с геттерами вместо friend funtions
  out << lineItem.startItem()->pos()
      << lineItem.endItem()->pos()
      << lineItem.containedText();

  return out;
}

QDataStream &operator>>(QDataStream &in, UmlLineItem &lineItem)
{
  QString containedText;

  /* Позиции начального и конечного элементов считываются при создании объекта */
  in >> containedText;

  //FIXME Костыль с сеттерами вместо friend funtions
  lineItem.setContainedText(containedText);

  return in;
}
