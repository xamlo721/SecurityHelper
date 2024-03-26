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
    QObject::connect(scenary, &SelectedWidget::signalSelected, this, &AdminScenariesWidget::signalScenarySelected);
    QObject::connect(scenary, &SelectedWidget::signalUnselected, this, &AdminScenariesWidget::signalScenaryUnselected);
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

/**
 * @brief enableEditButton - включить доступность кнопки
 * "Редактировать" на пакели событий
 */
void AdminScenariesWidget::enableEditButton() {
    this->ui->pushButton_editScenario->setEnabled(true);
}

/**
 * @brief disableEditButton - выключить доступность кнопки
 * "Редактировать" на пакели событий
 */
void AdminScenariesWidget::disableEditButton() {
    this->ui->pushButton_editScenario->setEnabled(false);
}

/**
 * @brief enableSaveButton - включить доступность кнопки
 * "Сохранить" на пакели событий
 */
void AdminScenariesWidget::enableSaveButton() {
    this->ui->pushButton_saveScenario->setEnabled(true);
}

/**
 * @brief disableSaveButton - выключить доступность кнопки
 * "Сохранить" на пакели событий
 */
void AdminScenariesWidget::disableSaveButton() {
    this->ui->pushButton_saveScenario->setEnabled(false);
}

/**
 * @brief enableDeleteButton - включить доступность кнопки
 * "Удалить" на пакели событий
 */
void AdminScenariesWidget::enableDeleteButton() {
    this->ui->pushButton_deleteScenario->setEnabled(true);
}

/**
 * @brief disableDeleteButton - выключить доступность кнопки
 * "Удалить" на пакели событий
 */
void AdminScenariesWidget::disableDeleteButton() {
    this->ui->pushButton_deleteScenario->setEnabled(false);
}

AdminScenariesWidget::~AdminScenariesWidget() {
    delete ui;
}
