#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "umlmainwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    UmlMainWidget* _umlWidget;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
