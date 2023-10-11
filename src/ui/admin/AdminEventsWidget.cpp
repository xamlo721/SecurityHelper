#include "AdminEventsWidget.h"
#include "ui_AdminEventsWidget.h"

AdminEventsWidget::AdminEventsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminEventsWidget)
{
    ui->setupUi(this);
}

AdminEventsWidget::~AdminEventsWidget()
{
    delete ui;
}
