#include "ScenarioWidget.h"
#include "ui_ScenarioWidget.h"

ScenarioWidget::ScenarioWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ScenarioWidget) {
    ui->setupUi(this);
}

ScenarioWidget::~ScenarioWidget() {
    delete ui;
}
