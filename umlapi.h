#ifndef UMLAPI_H
#define UMLAPI_H

#include <QObject>
#include "components/scenes/domainscene.h"

class UmlApi : public QObject
{
    Q_OBJECT
public:
    explicit UmlApi(DomainScene* scene, QObject *parent = 0);

signals:

public slots:
    void addDomainItem(QString itemText);
    void addDomainItem(QString itemText, QPointF pos);
    bool addDomainLine(QString startItemText, QString endItemText, QString lineText);
    bool moveDomainItem(QString itemText, QPointF newPos);
    void dumpScene();
    bool removeItem(QString itemText);
    bool saveSceneImage(QString fileName);

private:
    DomainScene* _scene;
    void recursiveShift(QGraphicsItem* item);

    QObject* _parent;

};

#endif // UMLAPI_H
