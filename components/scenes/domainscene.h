#ifndef DOMAINSCENE_H
#define DOMAINSCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QDataStream>
#include "../primitives/domainitem.h"
#include "../primitives/domainarrow.h"

class DomainScene : public QGraphicsScene
{
  Q_OBJECT

public:
  enum Mode { InsertItem, InsertLine, MoveItem, DeleteItem };
  DomainScene();
  void setMode(int mode);
  void deleteGraphicsItem(QGraphicsItem *item);

public slots:
  bool saveImage(const QString &fileName, const char *fileFormat);
  void writeItemsToBinaryStream(QDataStream &out);
  void readItemsFromBinaryStream(QDataStream &in);

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
