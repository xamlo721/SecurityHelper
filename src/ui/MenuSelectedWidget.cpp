#include "MenuSelectedWidget.h"
#include "ui_MenuSelectedWidget.h"

MenuSelectedWidget::MenuSelectedWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuSelectedWidget)
{
    ui->setupUi(this);
}

MenuSelectedWidget::~MenuSelectedWidget()
{
    delete ui;
}
