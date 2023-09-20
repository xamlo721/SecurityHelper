#include "EditableEventCategoryWidget.h"
#include "ui_EditableEventCategoryWidget.h"

EditableEventCategoryWidget::EditableEventCategoryWidget(EventCategoryWidget * categoryWidget, QWidget * parent) : QWidget(parent), ui(new Ui::EditableEventCategoryWidget) {
    ui->setupUi(this);
    this->ui->lineEdit->setMinimumSize(200, 60);
    this->ui->lineEdit->setEnabled(true);
    this->ui->lineEdit->setText(categoryWidget->getText());
    this->id = categoryWidget->getId();
}

EditableEventCategoryWidget::~EditableEventCategoryWidget() {
    delete ui;
}
