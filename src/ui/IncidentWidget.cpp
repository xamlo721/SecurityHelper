#include "IncidentWidget.h"
#include "ui_IncidentWidget.h"

IncidentWidget::IncidentWidget(QWidget *parent) :  QWidget(parent), ui(new Ui::IncidentWidget) {
    ui->setupUi(this);
}

IncidentWidget::~IncidentWidget() {
    delete ui;
}
