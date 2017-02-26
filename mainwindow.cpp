#include "mainwindow.h"
#include <QHBoxLayout>
#include <qDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  _umlWidget = new UmlMainWidget;
  setCentralWidget(_umlWidget);

  // API Examples
//  _umlWidget->api->addDomainItem("API: Item 1");
//  _umlWidget->api->addDomainItem("API: Item 2");
//  _umlWidget->api->addDomainItem("API: Item 3");
//  _umlWidget->api->addDomainItem("API: Item 4");
//  _umlWidget->api->addDomainItem("API: Item 5", QPointF(100.0, -100.0));
//  _umlWidget->api->moveDomainItem("API: Item 4", QPointF(-100.0, -100.0));
//  _umlWidget->api->addDomainLine("API: Item 1", "API: Item 5", "API: Line 1");
//  _umlWidget->api->removeItem("API: Item 3");
//  _umlWidget->api->dumpScene();
//  _umlWidget->api->saveSceneImage("C:/userfld/testImage.PNG");
//  _umlWidget->api->saveDomainFile("C:/userfld/testDomain");
//  _umlWidget->api->loadDomainFile("C:/userfld/testDomain");
}

MainWindow::~MainWindow()
{

}
