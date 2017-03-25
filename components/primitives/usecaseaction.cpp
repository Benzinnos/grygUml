#include "usecaseaction.h"

#include <QPainter>
#include <QBrush>
#include <QLinearGradient>

using namespace UmlDesigner;
using namespace UmlDesigner::UmlPrimitives;

UseCaseAction::UseCaseAction()
  : AbstractUmlItem()
{
  _containedText = "UseCase Action";
}

QRectF UseCaseAction::boundingRect() const
{
  return QRectF(0, 0, _textRect.width() + BORDER_OFFSET, _textRect.height() + BORDER_OFFSET);
}

void UseCaseAction::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option) Q_UNUSED(widget);

  _textRect = painter->fontMetrics().boundingRect(QRect(), Qt::AlignCenter, _containedText);

  //Paint
  if (isSelected()) {
    painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
  }

  QLinearGradient gradient(boundingRect().topLeft(), boundingRect().bottomRight()); // diagonal gradient from top-left to bottom-right
  gradient.setColorAt(0, Qt::yellow);
  gradient.setColorAt(1, Qt::white);
  painter->setBrush(QBrush(gradient));

  painter->drawEllipse(boundingRect());
  painter->drawText(boundingRect(), Qt::AlignCenter, _containedText);
}

int UseCaseAction::type() const
{
  return Type;
}
