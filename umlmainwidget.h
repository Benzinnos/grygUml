#ifndef UMLMAINWIDGET_H
#define UMLMAINWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QGraphicsView>

#include "components/scenes/domainscene.h"
#include "components/primitives/domainitem.h"
#include "ui_umlmainform.h"

class UmlMainWidget : public QWidget, Ui_Form
{
    Q_OBJECT

    DomainScene* _scene;
    DomainItem* _item;

public:
    explicit UmlMainWidget(QWidget *parent = 0);
    ~UmlMainWidget();

signals:

public slots:
    bool onAddRectangle();
    bool onSaveAsPicture();
    void onAddLine();
    bool onLineCreated(DomainArrow* arrow);
};

#endif // UMLMAINWIDGET_H
