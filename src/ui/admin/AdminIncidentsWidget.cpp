#include "AdminIncidentsWidget.h"
#include "ui_AdminIncidentsWidget.h"

AdminIncidentsWidget::AdminIncidentsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminIncidentsWidget)
{
    ui->setupUi(this);
}

AdminIncidentsWidget::~AdminIncidentsWidget()
{
    delete ui;
}
