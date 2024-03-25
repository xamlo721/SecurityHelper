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
    QObject::connect(incident, &SelectedWidget::signalSelected, this, &AdminIncidentsWidget::signalIncidentSelected);
    QObject::connect(incident, &SelectedWidget::signalUnselected, this, &AdminIncidentsWidget::signalIncidentUnselected);
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
    //TODO: Оставить возможность редактировать только если выбран инцидент
    emit signaEditIncidentClicked(this->ui->scrollArea_incidents->getSelectedWidgetID());
}

void AdminIncidentsWidget::onDelIncidentButtonPressed() {
    emit signalDelIncidentClicked(this->ui->scrollArea_incidents->getSelectedWidgetID());
}

void AdminIncidentsWidget::onSaveIncidentButtonPressed() {
    SelectedWidget * selected =  this->ui->scrollArea_incidents->getSelectedWidget();
    emit signaSaveIncidentClicked(selected->getId(), selected->getText());
}


/**
 * @brief enableEditButton - включить доступность кнопки
 * "Редактировать" на пакели событий
 */
void AdminIncidentsWidget::enableEditButton() {
    this->ui->pushButton_editIncident->setEnabled(true);
}

/**
 * @brief disableEditButton - выключить доступность кнопки
 * "Редактировать" на пакели событий
 */
void AdminIncidentsWidget::disableEditButton() {
    this->ui->pushButton_editIncident->setEnabled(false);
}

/**
 * @brief enableDeleteButton - включить доступность кнопки
 * "Удалить" на пакели событий
 */
void AdminIncidentsWidget::enableDeleteButton() {
    this->ui->pushButton_deleteIncident->setEnabled(true);
}

/**
 * @brief disableDeleteButton - выключить доступность кнопки
 * "Удалить" на пакели событий
 */
void AdminIncidentsWidget::disableDeleteButton() {
    this->ui->pushButton_deleteIncident->setEnabled(false);
}

AdminIncidentsWidget::~AdminIncidentsWidget() {
    delete ui;
}
