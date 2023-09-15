#include "EditableEventWidget.h"
#include "ui_EditableEventWidget.h"

EditableEventWidget::EditableEventWidget(EventWidget * eventWidget, QWidget *parent) : QWidget(parent), ui(new Ui::EditableEventWidget) {
    ui->setupUi(this);
    this->ui->lineEdit->setMinimumSize(200, 60);
    this->ui->lineEdit->setEnabled(true);
    this->ui->lineEdit->setText(eventWidget->getText());
    this->id = id;

}

EditableEventWidget::~EditableEventWidget() {
    delete ui;
}
