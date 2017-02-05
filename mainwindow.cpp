#include "mainwindow.h"
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _umlWidget = new UmlMainWidget;
    setCentralWidget(_umlWidget);
}

MainWindow::~MainWindow()
{

}
