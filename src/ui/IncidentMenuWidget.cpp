#include "IncidentMenuWidget.h"
#include "ui_IncidentMenuWidget.h"

IncidentMenuWidget::IncidentMenuWidget(QWidget *parent) : QWidget(parent), ui(new Ui::IncidentMenuWidget) {
    ui->setupUi(this);
}

IncidentMenuWidget::~IncidentMenuWidget() {
    delete ui;
}
