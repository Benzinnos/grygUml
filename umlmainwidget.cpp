#include "umlmainwidget.h"
#include <QFileDialog>

UmlMainWidget::UmlMainWidget(QWidget *parent) : QWidget(parent)
{
    setupUi(this);

    _scene = new DomainScene();
    _item = new DomainItem();

    graphicsView->setScene(_scene);

    _scene->addItem(_item);

    _item->setData(0, "Text exampleqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq");

//    _scene->saveImage("C:/userfld/test", "jpeg");



//    QString fileName= QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
//    if (!fileName.isNull())
//    {
//        QPixmap pixMap = this->graphicsView->grab();
//        pixMap.save(fileName);
//    }

}
