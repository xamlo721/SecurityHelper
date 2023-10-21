#include "AdminIncidentsWidget.h"
#include "ui_AdminIncidentsWidget.h"

AdminIncidentsWidget::AdminIncidentsWidget(QWidget *parent) : QWidget(parent), ui(new Ui::AdminIncidentsWidget) {
    ui->setupUi(this);
    QObject::connect(this->ui->pushButton_addIncident, &QPushButton::clicked, this, &AdminIncidentsWidget::onAddIncidentButtonPressed);
    QObject::connect(this->ui->pushButton_editIncident, &QPushButton::clicked, this, &AdminIncidentsWidget::onEditIncidentButtonPressed);
    QObject::connect(this->ui->pushButton_deleteIncident, &QPushButton::clicked, this, &AdminIncidentsWidget::onDelIncidentButtonPressed);

    QObject::connect(this->ui->pushButton_saveIncident, &QPushButton::clicked, this, &AdminIncidentsWidget::onSaveIncidentButtonPressed);

}

void AdminIncidentsWidget::clearIncidents() {
    this->ui->scrollArea_incidents->clear();
}

void AdminIncidentsWidget::addIncident(SelectedWidget *incident) {
    QObject::connect(incident, &SelectedWidget::signalSelected, this, &AdminIncidentsWidget::signalIncidentClicked);
    this->ui->scrollArea_incidents->addWidget(incident->getId(), incident);
}

void AdminIncidentsWidget::clearAvailableEvents() {
    this->ui->scrollArea_incidents_freeEvents->clear();
}

void AdminIncidentsWidget::addAvalilableEvent(SelectedWidget * event) {
    QObject::connect(event, &SelectedWidget::signalSelected, this, &AdminIncidentsWidget::signaAvailableEventClicked);
    this->ui->scrollArea_incidents_freeEvents->addWidget(event->getId(), event);
}

void AdminIncidentsWidget::clearSelectedEvents() {
    this->ui->scrollArea_incidents_includedEvent->clear();

}

void AdminIncidentsWidget::addSelectedEvent(SelectedWidget * event) {
    QObject::connect(event, &SelectedWidget::signalSelected, this, &AdminIncidentsWidget::signalSelectedEventClicked);
    this->ui->scrollArea_incidents_includedEvent->addWidget(event->getId(), event);

}

void AdminIncidentsWidget::onAddIncidentButtonPressed() {
    this->ui->scrollArea_incidents->unselect();
    emit signalAddIncidentClicked();
}

void AdminIncidentsWidget::onEditIncidentButtonPressed() {
    //TODO: открыть окно редактирования
}

void AdminIncidentsWidget::onDelIncidentButtonPressed() {
    emit signalDelIncidentClicked(this->ui->scrollArea_incidents->getSelectedWidgetID());
}

void AdminIncidentsWidget::onSaveIncidentButtonPressed() {
    SelectedWidget * selected =  this->ui->scrollArea_incidents->getSelectedWidget();
    emit signalEditIncidentClicked(selected->getId(), selected->getText());
}

AdminIncidentsWidget::~AdminIncidentsWidget() {
    delete ui;
}
