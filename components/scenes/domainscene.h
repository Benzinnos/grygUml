#ifndef DOMAINSCENE_H
#define DOMAINSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include "../primitives/domainitem.h"
#include "../primitives/domainarrow.h"

class DomainScene : public QGraphicsScene
{
  Q_OBJECT

public:
  enum Mode { InsertItem, InsertLine, MoveItem };
  DomainScene();
  void setMode(int mode);

public slots:
  bool saveImage(const QString &fileName, const char *fileFormat);

  // QGraphicsScene interface
protected:
  virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
  int _mode;
  QGraphicsItem* _firstItem;
  QGraphicsItem* _seccondItem;

signals:
  void lineCreated(DomainArrow* arrow);
};

#endif // DOMAINSCENE_H
