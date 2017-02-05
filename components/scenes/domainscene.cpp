#include "domainscene.h"
#include <QImage>
#include <QPainter>
#include <qDebug>

DomainScene::DomainScene()
{
}

bool DomainScene::saveImage(const QString &fileName, const char *fileFormat)
{
    clearSelection();
//    setSceneRect(itemsBoundingRect());
    QImage image(sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::white);

    QPainter painter(&image);
    render(&painter);

    if (image.save(fileName + ".png"))
    {
        qDebug()<<"SAVE SUCCESS!";
        return true;
    }
    else
        return false;
}
