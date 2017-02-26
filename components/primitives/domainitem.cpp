#include "domainitem.h"
#include <QPainter>
#include <QInputDialog>
#include <QGraphicsScene>
#include <QLinearGradient>
#include <QDataStream>

DomainItem::DomainItem()
  : _containedText("Text")
{
  setFlag(QGraphicsItem::ItemIsMovable, true);
  setFlag(QGraphicsItem::ItemIsSelectable, true);
  setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
  setFlag(QGraphicsItem::ItemIsFocusable, true);
}

DomainItem::~DomainItem()
{
  //  removeArrows();
}

QString DomainItem::containedText() const
{
  return _containedText;
}

void DomainItem::setContainedText(const QString &containedText)
{
  _containedText = containedText;
}

QRectF DomainItem::boundingRect() const
{
  //TODO Ультраговнокод. Переделать как fontSize*string->size()
  return QRectF(0, 0, _containedText.size()*7/* Типо fontSize */, 15 /* Высота шрифта + смещение? */);
}

void DomainItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option) Q_UNUSED(widget);

  if (isSelected()) {
      painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
    }

  //  painter->fillRect(boundingRect(), Qt::white);
  QLinearGradient gradient(boundingRect().topLeft(), boundingRect().bottomRight()); // diagonal gradient from top-left to bottom-right
  gradient.setColorAt(0, Qt::yellow);
  gradient.setColorAt(1, Qt::white);
  painter->fillRect(boundingRect(), gradient);
  painter->drawRect(boundingRect());

  painter->drawText(boundingRect(), Qt::AlignCenter, _containedText);
  setData(0, _containedText);
}


void DomainItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
  Q_UNUSED(event)

  bool ok(false);
  QString str = QInputDialog::getText(nullptr, "Введите текст", "Текст", QLineEdit::Normal, _containedText, &ok);
  if (ok) {
      _containedText = str;
    }
}

void DomainItem::addArrow(DomainArrow *arrow)
{
  _arrows.append(arrow);
}

void DomainItem::removeArrow(DomainArrow *arrow)
{
  int index = _arrows.indexOf(arrow);

  if (index != -1)
    _arrows.removeAt(index);
}

void DomainItem::removeArrows()
{
  foreach (DomainArrow* arrow, _arrows) {
      qgraphicsitem_cast<DomainItem*>(arrow->startItem())->removeArrow(arrow);
      qgraphicsitem_cast<DomainItem*>(arrow->endItem())->removeArrow(arrow);
      scene()->removeItem(arrow);
      delete arrow;
    }
}


QVariant DomainItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
  if (change == QGraphicsItem::ItemPositionChange) {
      foreach (DomainArrow *arrow, _arrows) {
          arrow->updatePosition();
        }
    }

  return value;
}


int DomainItem::type() const
{
  return Type;
}


QDataStream &operator<<(QDataStream &out, const DomainItem &domainItem)
{
  out << domainItem.pos()
      << domainItem.containedText();

  return out;
}


QDataStream &operator>>(QDataStream &in, DomainItem &domainItem)
{
  QPointF position;
  QString containedText;

  in  >> position
      >> containedText;

  domainItem.setPos(position);
  domainItem.setContainedText(containedText);

  return in;
}
