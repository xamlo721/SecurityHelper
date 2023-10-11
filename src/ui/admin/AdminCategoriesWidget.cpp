#include "AdminCategoriesWidget.h"
#include "ui_AdminCategoriesWidget.h"

AdminCategoriesWidget::AdminCategoriesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminCategoriesWidget)
{
    ui->setupUi(this);
}

AdminCategoriesWidget::~AdminCategoriesWidget()
{
    delete ui;
}
