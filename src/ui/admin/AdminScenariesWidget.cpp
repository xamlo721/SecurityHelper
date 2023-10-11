#include "AdminScenariesWidget.h"
#include "ui_AdminScenariesWidget.h"

AdminScenariesWidget::AdminScenariesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminScenariesWidget)
{
    ui->setupUi(this);
}

AdminScenariesWidget::~AdminScenariesWidget()
{
    delete ui;
}
