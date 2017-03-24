#include "umlmainwidget.h"
#include <QFileDialog>
#include <QInputDialog>

//#include"components/primitives/usecaseactor.h"
#include "components/primitives/domainitem.h"
#include "components/primitives/umllineitem.h"

using namespace UmlDesigner;

UmlMainWidget::UmlMainWidget(QWidget *parent) : QWidget(parent)
{
  _domainScene = new DomainScene();
  api = new UmlApi(_domainScene, this);
  setupUi(this);
  graphicsView->setScene(_domainScene);

  //DELL Debug
//  _domainScene->addItem(new UseCaseActor());

  UmlPrimitives::DomainItem *itemF = new UmlPrimitives::DomainItem();
  itemF->setContainedText("First");
  UmlPrimitives::DomainItem *itemL = new UmlPrimitives::DomainItem();
  itemL->setContainedText("Last");
  _domainScene->addItem(itemF);
  _domainScene->addItem(itemL);
  itemL->moveBy(50, 50);

  UmlPrimitives::UmlLineItem *line = new UmlPrimitives::UmlLineItem(itemF, itemL);
  _domainScene->addItem(line);



  connect(addRectangleButton, &QPushButton::clicked, this, &UmlMainWidget::onAddRectangle);
  connect(saveAsPictureButton, &QPushButton::clicked, this, &UmlMainWidget::onSaveAsPicture);
  connect(saveUsecaseAsPictureButton, &QPushButton::clicked, this, &UmlMainWidget::onSaveAsPicture);
  connect(addLineButton, &QPushButton::clicked, this, &UmlMainWidget::onAddLine);
  connect(_domainScene, &DomainScene::lineCreated, this, &UmlMainWidget::onLineCreated);
  connect(saveBinaryButton, &QPushButton::clicked, this, &UmlMainWidget::onBinarySave);
  connect(loadBinaryButton, &QPushButton::clicked, this, &UmlMainWidget::onBinaryLoad);
  connect(deleteItemButton, &QPushButton::clicked, this, &UmlMainWidget::onDeleteItem);
}

UmlMainWidget::~UmlMainWidget()
{
  foreach (QGraphicsItem* item, _domainScene->items()) {
    delete item;
  }
}

bool UmlMainWidget::onAddRectangle()
{
  bool ok(false);
  QString str = QInputDialog::getText(this, "Введите текст", "Текст", QLineEdit::Normal, QString("New_domain_item %1").arg(_domainScene->items().size()), &ok);
  if (ok) {
//    DomainItem* item = new DomainItem();
//    item->setContainedText(str);
//    _domainScene->addItem(item);
    return true;
  }
  else {
    return false;
  }
}

bool UmlMainWidget::onSaveAsPicture()
{
  QString fileName = QFileDialog::getSaveFileName(this, "Сохранить рисунок", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)");
  if (!fileName.isNull())
  {
    savePicture(fileName);
  }
  return false;
}

void UmlMainWidget::onAddLine()
{
  _domainScene->setMode(DomainScene::InsertLine);
}

bool UmlMainWidget::onLineCreated(DomainArrow *arrow)
{
  bool ok(false);
  QString str = QInputDialog::getText(this, "Введите текст", "Текст", QLineEdit::Normal, QString("New_domain_item %1").arg(_domainScene->items().size()), &ok);
  if (ok) {
    arrow->setContainedText(str);
    _domainScene->addItem(arrow);
    return true;
  }
  else {
//    qgraphicsitem_cast<DomainItem*>(arrow->startItem())->removeArrow(arrow);
//    qgraphicsitem_cast<DomainItem*>(arrow->endItem())->removeArrow(arrow);
    delete arrow;

    return false;
  }
}

void UmlMainWidget::onBinarySave()
{
  QString fileName = QFileDialog::getSaveFileName(this, "Сохранить диаграмму", QCoreApplication::applicationDirPath(), "Domain Diagram Files (*.ddf)");
  if (!fileName.isNull())
  {
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QDataStream stream(&file);
    _domainScene->writeItemsToBinaryStream(stream);
    file.close();
  }
}

void UmlMainWidget::onBinaryLoad()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Загрузить диаграмму", QCoreApplication::applicationDirPath(), "Domain Diagram Files (*.ddf)");
  if (!fileName.isNull())
  {
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QDataStream stream(&file);
    _domainScene->readItemsFromBinaryStream(stream);
    file.close();
  }
}

void UmlMainWidget::onDeleteItem()
{
  _domainScene->setMode(DomainScene::DeleteItem);
}

bool UmlMainWidget::savePicture(QString fileName)
{
  QPixmap pixMap = this->graphicsView->grab();
  return pixMap.save(fileName);
}
