#include "IncidentCategoryWidget.h"
#include "ui_IncidentCategoryWidget.h"

IncidentCategoryWidget::IncidentCategoryWidget(int id, QString title, QWidget *parent) : QWidget(parent), ui(new Ui::IncidentCategoryWidget) {
    ui->setupUi(this);
    this->ui->pushButton->setMinimumSize(200, 60);
}

IncidentCategoryWidget::~IncidentCategoryWidget() {
    delete ui;
}
