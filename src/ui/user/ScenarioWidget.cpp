#include "ScenarioWidget.h"
#include "ui_ScenarioWidget.h"

ScenarioWidget::ScenarioWidget(quint32 id, QString text, QString name, QWidget *parent) : QWidget(parent), ui(new Ui::ScenarioWidget) {
    ui->setupUi(this);
    this->id = id;
    this->ui->textEdit_scenario_decription->append(text);
    this->ui->label_scenario_title->setText(name);
    QObject::connect(this->ui->pushButton_recommendations, &QPushButton::clicked, this, &ScenarioWidget::onPuttonClicked);
    QObject::connect(this->ui->pushButton_clarify, &QPushButton::clicked, this, &ScenarioWidget::signalClarify);
}

void ScenarioWidget::onPuttonClicked() {
    emit signalScenarioOpen(this->id);
}

ScenarioWidget::~ScenarioWidget() {
    delete ui;
}
