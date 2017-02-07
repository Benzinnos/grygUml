#include "umlmainwidget.h"
#include <QFileDialog>
#include <QInputDialog>

UmlMainWidget::UmlMainWidget(QWidget *parent) : QWidget(parent)
{
  setupUi(this);

  _scene = new DomainScene();
  _item = new DomainItem();

  graphicsView->setScene(_scene);

  connect(addRectangleButton, &QPushButton::clicked, this, &UmlMainWidget::onAddRectangle);
  connect(saveAsPictureButton, &QPushButton::clicked, this, &UmlMainWidget::onSaveAsPicture);
  connect(addLineButton, &QPushButton::clicked, this, &UmlMainWidget::onAddLine);
  connect(_scene, &DomainScene::lineCreated, this, &UmlMainWidget::onLineCreated);
}

UmlMainWidget::~UmlMainWidget()
{
  foreach (QGraphicsItem* item, _scene->items()) {
    delete item;
  }
}

bool UmlMainWidget::onAddRectangle()
{
  bool ok(false);
  QString str = QInputDialog::getText(this, "Введите текст", "Текст", QLineEdit::Normal, QString("New_domain_item %1").arg(_scene->items().size()), &ok);
  if (ok) {
    DomainItem* item = new DomainItem();
    item->setContainedText(str);
    _scene->addItem(item);
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
    QPixmap pixMap = this->graphicsView->grab();
    pixMap.save(fileName);
    return true;
  }
  return false;
}

void UmlMainWidget::onAddLine()
{
  _scene->setMode(DomainScene::InsertLine);
}

bool UmlMainWidget::onLineCreated(DomainArrow *arrow)
{
  bool ok(false);
  QString str = QInputDialog::getText(this, "Введите текст", "Текст", QLineEdit::Normal, QString("New_domain_item %1").arg(_scene->items().size()), &ok);
  if (ok) {
    arrow->setContainedText(str);
    _scene->addItem(arrow);
    return true;
  }
  else {
    qgraphicsitem_cast<DomainItem*>(arrow->startItem())->removeArrow(arrow);
    qgraphicsitem_cast<DomainItem*>(arrow->endItem())->removeArrow(arrow);
    delete arrow;

    return false;
  }
}
