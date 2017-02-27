#ifndef UMLMAINWIDGET_H
#define UMLMAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QGraphicsView>

#include "components/scenes/domainscene.h"
#include "ui_umlmainform.h"
#include "umlapi.h"

class UmlMainWidget : public QWidget, Ui_Form
{
    Q_OBJECT

    DomainScene* _scene;

public:
    explicit UmlMainWidget(QWidget *parent = 0);
    ~UmlMainWidget();

    UmlApi* api;
    bool savePicture(QString fileName);

signals:

public slots:
    bool onAddRectangle();
    bool onSaveAsPicture();
    void onAddLine();
    bool onLineCreated(DomainArrow* arrow);
    void onBinarySave();
    void onBinaryLoad();
    void onDeleteItem();
};

#endif // UMLMAINWIDGET_H
