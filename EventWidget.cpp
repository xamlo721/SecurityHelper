#include "EventWidget.h"
#include "ui_EventWidget.h"

EventWidget::EventWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EventWidget)
{
    ui->setupUi(this);
}

EventWidget::~EventWidget()
{
    delete ui;
}
