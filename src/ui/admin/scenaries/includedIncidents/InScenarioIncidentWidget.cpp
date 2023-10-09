#include "InScenarioIncidentWidget.h"
#include "ui_InScenarioIncidentWidget.h"

InScenarioIncidentWidget::InScenarioIncidentWidget(const quint32 id, const QString text, const QString title, QWidget *parent) : QWidget(parent), ui(new Ui::InScenarioIncidentWidget) {
    ui->setupUi(this);

    this->ui->label_incidentTitle->setMinimumSize(200, 60);

    this->id = id;
    this->text = text;
    this->title = title;

    this->ui->checkBox->setChecked(false);

    this->ui->label_incidentTitle->setText(title);

    QObject::connect(this->ui->checkBox, &QCheckBox::clicked, this, &InScenarioIncidentWidget::onCheckBoxClicked);
}

InScenarioIncidentWidget::~InScenarioIncidentWidget() {
    delete ui;
}

void InScenarioIncidentWidget::onCheckBoxClicked() {
    switch (this->ui->checkBox->isChecked()) {
    case true:

        emit signalIncidentSelected(this->getID());
        break;

    case false:

        emit signalIncidentUnselected(this->getID());
        break;
    }
}

void InScenarioIncidentWidget::setTitle(const QString title) {
    this->title = title;
    this->ui->label_incidentTitle->setText(this->title);
}

void InScenarioIncidentWidget::setUnselected() {
    /// Делаем checkBox не выбранным
    this->ui->checkBox->setChecked(false);
    /// Отправляем сигнал о том, что выбор checkBox отменяется
    emit this->ui->checkBox->clicked();
}
