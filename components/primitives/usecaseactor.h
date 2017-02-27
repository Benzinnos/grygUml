#ifndef USECASEACTOR_H
#define USECASEACTOR_H

#include <QObject>
#include <QGraphicsItem>

class UseCaseActor : public QGraphicsItem
{
public:
  enum { Type = UserType + 3 };
  UseCaseActor();

  // QGraphicsItem interface
public:
  virtual QRectF boundingRect() const override;
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
  virtual int type() const override;

protected:
  virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // USECASEACTOR_H
