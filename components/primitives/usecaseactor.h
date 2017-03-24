#ifndef USECASEACTOR_H
#define USECASEACTOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QFontMetrics>

#include "domainitem.h"

class UseCaseActor : public DomainItem
{
  QRectF _textRect;

public:
  UseCaseActor();
  enum { Type = DomainItem::Type + 2 };

  // QGraphicsItem interface
public:
  virtual QRectF boundingRect() const override;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:

  // QGraphicsItem interface
public:
  virtual int type() const override;
};

#endif // USECASEACTOR_H
