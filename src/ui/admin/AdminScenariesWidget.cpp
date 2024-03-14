#include "AdminScenariesWidget.h"
#include "ui_AdminScenariesWidget.h"

AdminScenariesWidget::AdminScenariesWidget(QWidget *parent) : QWidget(parent), ui(new Ui::AdminScenariesWidget) {
    ui->setupUi(this);
    QObject::connect(this->ui->pushButton_addScenario, &QPushButton::clicked, this, &AdminScenariesWidget::onAddScenaryButtonPressed);
    QObject::connect(this->ui->pushButton_editScenario, &QPushButton::clicked, this, &AdminScenariesWidget::onEditScenaryButtonPressed);
    QObject::connect(this->ui->pushButton_deleteScenario, &QPushButton::clicked, this, &AdminScenariesWidget::onDelScenaryButtonPressed);

    QObject::connect(this->ui->pushButton_saveScenario, &QPushButton::clicked, this, &AdminScenariesWidget::onSaveScenaryButtonPressed);
}


void AdminScenariesWidget::clearScenaries() {
    this->ui->scrollArea_scenaries->clear();
}

void AdminScenariesWidget::addScenary(SelectedWidget *scenary) {
    QObject::connect(scenary, &SelectedWidget::signalSelected, this, &AdminScenariesWidget::signalScenaryClicked);
    this->ui->scrollArea_scenaries->addWidget(scenary->getId(), scenary);
}

void AdminScenariesWidget::clearAvailableIncidents() {
    this->ui->scrollArea_scenaries_freeIncidents->clear();
}

void AdminScenariesWidget::addAvalilableIncident(SelectedWidget * incident) {
    QObject::connect(incident, &SelectedWidget::signalSelected, this, &AdminScenariesWidget::signaAvailableIncidentClicked);
    this->ui->scrollArea_scenaries_freeIncidents->addWidget(incident->getId(), incident);
}

void AdminScenariesWidget::clearSelectedIncidents() {
    this->ui->scrollArea_scenaries_includedIncidents->clear();

}

void AdminScenariesWidget::addSelectedIncident(SelectedWidget * incident) {
    QObject::connect(incident, &SelectedWidget::signalSelected, this, &AdminScenariesWidget::signalSelectedIncidentClicked);
    this->ui->scrollArea_scenaries_includedIncidents->addWidget(incident->getId(), incident);

}

void AdminScenariesWidget::onAddScenaryButtonPressed() {
    this->ui->scrollArea_scenaries->unselect();
    emit signalAddScenaryClicked();
}

void AdminScenariesWidget::onEditScenaryButtonPressed() {
    //TODO: Оставить возможность редактировать только если выбран сценарий
    emit signaEditScenaryClicked(this->ui->scrollArea_scenaries->getSelectedWidgetID());
}

void AdminScenariesWidget::onDelScenaryButtonPressed() {
    emit signalDelScenaryClicked(this->ui->scrollArea_scenaries->getSelectedWidgetID());
}

void AdminScenariesWidget::onSaveScenaryButtonPressed() {
    SelectedWidget * selected =  this->ui->scrollArea_scenaries->getSelectedWidget();
    emit signaSaveScenaryClicked(selected->getId(), selected->getText());
}

AdminScenariesWidget::~AdminScenariesWidget() {
    delete ui;
}
