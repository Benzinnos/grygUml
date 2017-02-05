#ifndef DOMAINSCENE_H
#define DOMAINSCENE_H

#include <QObject>
#include <QGraphicsScene>

class DomainScene : public QGraphicsScene
{
public:
    DomainScene();
public slots:
    bool saveImage(const QString &fileName, const char *fileFormat);

    // QGraphicsScene interface
protected:
};

#endif // DOMAINSCENE_H
