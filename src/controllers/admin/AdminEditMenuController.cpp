#include "AdminEditMenuController.h"

/**
*  @brief AdminEditMenuController - конструктор по умолчанию
*  @param parent - родительский объект в иерархии Qt.
*/
AdminEditMenuController::AdminEditMenuController(QObject *parent) : QObject{parent} {

}

/**
*  @brief init - метод инициализации меню редактирования
*  @param editMenu - объект AdminEditMenuWidget, находящийся в MainWindow.
*/
void AdminEditMenuController::init(AdminEditMenuWidget *editMenu) {
    /// Инициализируем объект меню редактирования в контроллере объектом из
    /// MainWindow, чтобы управлять им
    editMenuWidget = editMenu;

    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalAddCategoryButtonPressed, this, &AdminEditMenuController::signalAddCategoryButtonPressed);
    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalDeleteSelectedCategoriesButtonPressed, this, &AdminEditMenuController::signalDeleteSelectedCategoriesButtonPressed);

    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalAddToCategoryButtonPressed, this, &AdminEditMenuController::signalAddToCategoryButtonPressed);
    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalRemoveFromCategoryButtonPressed, this, &AdminEditMenuController::signalRemoveFromCategoryButtonPressed);



    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalAddEventButtonPressed, this, &AdminEditMenuController::signalAddEventButtonPressed);
    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalDeleteSelectedEventsButtonPressed, this, &AdminEditMenuController::signalDeleteSelectedEventsButtonPressed);



    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalAddIncidentButtonPressed, this, &AdminEditMenuController::signalAddIncidentButtonPressed);
    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalDeleteSelectedIncidentsButtonPressed, this, &AdminEditMenuController::signalDeleteSelectedIncidentsButtonPressed);

    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalAddToIncidentButtonPressed, this, &AdminEditMenuController::signalAddToIncidentButtonPressed);
    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalRemoveFromIncidentButtonPressed, this, &AdminEditMenuController::signalRemoveFromIncidentButtonPressed);



    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalAddScenarioButtonPressed, this, &AdminEditMenuController::signalAddScenarioButtonPressed);
    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalDeleteSelectedScenariesButtonPressed, this, &AdminEditMenuController::signalDeleteSelectedScenariesButtonPressed);

    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalAddToScenarioButtonPressed, this, &AdminEditMenuController::signalAddToScenarioButtonPressed);
    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalRemoveFromScenarioButtonPressed, this, &AdminEditMenuController::signalRemoveFromScenarioButtonPressed);


    /// Устанавливаем прокручиваемый список item'ов
    editMenuWidget->setupScrollAreas();

}


void AdminEditMenuController::slotSetAllTabsEnable() {
    this->editMenuWidget->setAllTabsEnable();
}

void AdminEditMenuController::slotSetCategoriesActive() {
    this->editMenuWidget->setCategoriesActive();
}

void AdminEditMenuController::slotSetEventsActive() {
    this->editMenuWidget->setEventsActive();
}

void AdminEditMenuController::slotSetIncidentsActive() {
    this->editMenuWidget->setIncidentsActive();
}

void AdminEditMenuController::slotSetScenariesActive() {
    this->editMenuWidget->setScenariesActive();
}

void AdminEditMenuController::slotSetRecommendtaionsActive() {
    this->editMenuWidget->setRecommendtaionsActive();
}


