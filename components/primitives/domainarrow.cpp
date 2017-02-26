#include "domainarrow.h"
#include <math.h>
#include <QPen>
#include <QPainter>
#include <QInputDialog>

DomainArrow::DomainArrow(QGraphicsItem *startItem, QGraphicsItem *endItem, QGraphicsItem *parent)
  : QGraphicsLineItem(parent), _containedText("Text")
{
  _myStartItem = startItem;
  _myEndItem = endItem;
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setZValue(-1000.0);
}


QRectF DomainArrow::boundingRect() const
{
  qreal extra = (pen().width() + 20) / 2.0;
//  return QRectF(0, 0, _containedText.size()*7/* Типо fontSize */, 15 /* Высота шрифта + смещение? */);

  QRectF retRect = QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                     line().p2().y() - line().p1().y()))
       .normalized()
       .adjusted(-extra, -extra, extra, extra);

  QRectF textRect(line().pointAt(0.5).x(), line().pointAt(0.5).y(), _containedText.size()*7/* Типо fontSize */, 15 /* Высота шрифта + смещение? */);

  return retRect.united(textRect);

//  return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
//                                    line().p2().y() - line().p1().y()))
//      .normalized()
//      .adjusted(-extra, -extra, extra, extra);
}

void DomainArrow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option);
  Q_UNUSED(widget);

   _startItemPosition = _myStartItem->pos();
   _endItemPosition = _myEndItem->pos();

  if (_myStartItem->collidesWithItem(_myEndItem))
      return;

//  QLineF centerLine(_myStartItem->pos(), _myEndItem->pos());
//  QPolygonF endPolygon = _myEndItem->boundingRect();
//  QPointF p1 = endPolygon.first() + _myEndItem->pos();
//  QPointF p2;
//  QPointF intersectPoint;
//  QLineF polyLine;
//  for (int i = 1; i < endPolygon.count(); ++i) {
//      p2 = endPolygon.at(i) + _myEndItem->pos();
//      polyLine = QLineF(p1, p2);
//      QLineF::IntersectType intersectType =
//          polyLine.intersect(centerLine, &intersectPoint);
//      if (intersectType == QLineF::BoundedIntersection)
//          break;
//      p1 = p2;
//  }

//  setLine(QLineF(intersectPoint, _myStartItem->pos()));

  QRectF rectStart(_myStartItem->pos(), _myStartItem->boundingRect().size());
  QPointF p1 = rectStart.center();
  QRectF rectEnd(_myEndItem->pos(), _myEndItem->boundingRect().size());
  QPointF p2 = rectEnd.center();
  setLine(QLineF(p1, p2));

  double angle = ::acos(line().dx() / line().length());
  if (line().dy() >= 0)
      angle = (M_PI * 2) - angle;

  QPointF arrowP1 = line().pointAt(0.5) + QPointF(sin(angle + M_PI / 3) * _arrowSize,
                                  cos(angle + M_PI / 3) * _arrowSize);
  QPointF arrowP2 = line().pointAt(0.5) + QPointF(sin(angle + M_PI - M_PI / 3) * _arrowSize,
                                  cos(angle + M_PI - M_PI / 3) * _arrowSize);

  _arrowHead.clear();
  _arrowHead << line().pointAt(0.5) << arrowP1 << arrowP2;

  painter->drawLine(line());
  painter->setPen(QPen(Qt::black, 5, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
  painter->drawPolygon(_arrowHead);

//  _arrowHead.fill();

  if (isSelected()) {
      painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
      QLineF myLine = line();
      myLine.translate(0, 4.0);
      painter->drawLine(myLine);
      myLine.translate(0,-8.0);
      painter->drawLine(myLine);
  }

//  QGraphicsTextItem text(_containedText);
//  painter->draw
//  painter->drawTextItem(line().pointAt(0.5), text);

  QPointF textPoint(line().pointAt(0.5));
  textPoint.setX(textPoint.x() + 15);
  textPoint.setY(textPoint.y() - 3);
  painter->drawText(textPoint, _containedText);
}

void DomainArrow::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
  Q_UNUSED(event)

  bool ok(false);
  QString str = QInputDialog::getText(nullptr, "Введите текст", "Текст", QLineEdit::Normal, _containedText, &ok);
  if (ok) {
    _containedText = str;
  }
}


QString DomainArrow::containedText() const
{
  return _containedText;
}

void DomainArrow::setContainedText(const QString &containedText)
{
  _containedText = containedText;
}


QPainterPath DomainArrow::shape() const
{
  QPainterPath path = QGraphicsLineItem::shape();
  path.addPolygon(_arrowHead);
  return path;
}


void DomainArrow::updatePosition()
{
    QLineF line(mapFromItem(_myStartItem, 0, 0), mapFromItem(_myEndItem, 0, 0));
    setLine(line);
}


int DomainArrow::type() const
{
    return Type;
}


QDataStream &operator<<(QDataStream &out, const DomainArrow &domainArrow)
{
  out << domainArrow._myStartItem->pos()
      << domainArrow._myEndItem->pos()
      << domainArrow.containedText();

  return out;
}


QDataStream &operator>>(QDataStream &in, DomainArrow &domainArrow)
{
  QString containedText;

  /* Позиции начального и конечного элементов считываются при создании объекта */
  in >> containedText;

  domainArrow._containedText = containedText;

  return in;
}
