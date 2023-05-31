#include "ScenarioMenuWidget.h"
#include "ui_ScenarioMenuWidget.h"

ScenarioMenuWidget::ScenarioMenuWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ScenarioMenuWidget) {
    ui->setupUi(this);
}

ScenarioMenuWidget::~ScenarioMenuWidget() {
    delete ui;
}
