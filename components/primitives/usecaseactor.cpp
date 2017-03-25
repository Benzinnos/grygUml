#include "usecaseactor.h"

#include <QLinearGradient>
#include <QPainter>

using namespace UmlDesigner;
using namespace UmlDesigner::UmlPrimitives;

UseCaseActor::UseCaseActor()
  : AbstractUmlItem()
{
  _containedText = "Usecase Actor";
}

QRectF UseCaseActor::boundingRect() const
{
  int lines = _containedText.count('\n') + 1;

  return QRectF(_textRect.width()/lines >= 24 ? 0 - _textRect.width()/2*lines : -12, // Начальная точка центрирована для больших строк
                -8,
                _textRect.width()/lines >= 24 ? _textRect.width()/lines : 24, // Скейлинг относительно ширины текста
                50 + _textRect.height() * lines);
}

void UseCaseActor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
  Q_UNUSED(option)
  Q_UNUSED(widget)

  _textRect = painter->fontMetrics().boundingRect(QRect(0, 45, 0, 0), Qt::TextWordWrap | Qt::AlignHCenter, _containedText);
  painter->drawText(_textRect, Qt::AlignHCenter, _containedText);

  // Залив башки
  QLinearGradient gradient(QPointF(-10, 0), QPointF(10,0));
  gradient.setColorAt(0, Qt::yellow);
  gradient.setColorAt(1, Qt::white);
  painter->setBrush(QBrush(gradient));

  // Башка
  painter->drawEllipse(QPointF(0, 0), 10, 8);

  QVector<QPointF> points {
    QPointF(0, 8), QPointF(0, 12), // Шея
        QPointF(-12, 12), QPointF(12, 12), // Руки
        QPointF(0, 12), QPointF(0, 30), // Тело
        QPointF(0, 30), QPointF(-10, 40), // Левая нога
        QPointF(0, 30), QPointF(10, 40) //Правая нога
  };

  // Paint
  if (isSelected()) {
    painter->setPen(QPen(Qt::black, 1, Qt::DashLine));
  }

  painter->drawLines(points);
}


int UseCaseActor::type() const
{
  return Type;
}
