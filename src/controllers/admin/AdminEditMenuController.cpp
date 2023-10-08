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



// Блок управления кнопками вкладки Категории событий

/// Блок управления кнопками категорий событий
void AdminEditMenuController::slotSetAddCategoryButtonEnabled() {
    this->editMenuWidget->setAddCategoryButtonEnabled();
}

void AdminEditMenuController::slotSetAddCategoryButtonDisabled() {
    this->editMenuWidget->setAddCategoryButtonDisabled();
}

void AdminEditMenuController::slotSetDeleteSelectedCategoriesButtonEnabled() {
    this->editMenuWidget->setDeleteSelectedCategoriesButtonEnabled();
}

void AdminEditMenuController::slotSetDeleteSelectedCategoriesButtonDisabled() {
    this->editMenuWidget->setDeleteSelectedCategoriesButtonDisabled();
}

/// Блок управления кнопками событий в категориях событий
void AdminEditMenuController::slotSetAddToCategoryButtonEnabled() {
    this->editMenuWidget->setAddToCategoryButtonEnabled();
}

void AdminEditMenuController::slotSetAddToCategoryButtonDisabled() {
    this->editMenuWidget->setAddToCategoryButtonDisabled();
}

void AdminEditMenuController::slotSetRemoveFromCategoryButtonEnabled() {
    this->editMenuWidget->setRemoveFromCategoryButtonEnabled();
}

void AdminEditMenuController::slotSetRemoveFromCategoryButtonDisabled() {
    this->editMenuWidget->setRemoveFromCategoryButtonDisabled();
}



// Блок управления кнопками вкладки События
void AdminEditMenuController::slotSetAddEventButtonEnabled() {
    this->editMenuWidget->setAddEventButtonEnabled();
}

void AdminEditMenuController::slotSetAddEventButtonDisabled() {
    this->editMenuWidget->setAddEventButtonDisabled();
}

void AdminEditMenuController::slotSetDeleteSelectedEventsButtonEnabled() {
    this->editMenuWidget->setDeleteSelectedEventsButtonEnabled();
}

void AdminEditMenuController::slotSetDeleteSelectedEventsButtonDisabled() {
    this->editMenuWidget->setDeleteSelectedEventsButtonDisabled();
}



// Блок управления кнопками вкладки Инциденты

/// Блок управления кнопками инцидентов
void AdminEditMenuController::slotSetAddIncidentButtonEnabled() {
    this->editMenuWidget->setAddIncidentButtonEnabled();
}

void AdminEditMenuController::slotSetAddIncidentButtonDisabled() {
    this->editMenuWidget->setAddIncidentButtonDisabled();
}

void AdminEditMenuController::slotSetDeleteSelectedIncidentsButtonEnabled() {
    this->editMenuWidget->setDeleteSelectedIncidentsButtonEnabled();
}

void AdminEditMenuController::slotSetDeleteSelectedIncidentsButtonDisabled() {
    this->editMenuWidget->setDeleteSelectedIncidentsButtonDisabled();
}

/// Блок управления кнопками событий в инцидентах
void AdminEditMenuController::slotSetAddToIncidentButtonEnabled() {
    this->editMenuWidget->setAddToIncidentButtonEnabled();
}

void AdminEditMenuController::slotSetAddToIncidentButtonDisabled() {
    this->editMenuWidget->setAddToIncidentButtonDisabled();
}

void AdminEditMenuController::slotSetRemoveFromIncidentButtonEnabled() {
    this->editMenuWidget->setRemoveFromIncidentButtonEnabled();
}

void AdminEditMenuController::slotSetRemoveFromIncidentButtonDisabled() {
    this->editMenuWidget->setRemoveFromIncidentButtonDisabled();
}



// Блок управления кнопками вкладки Сценарии

/// Блок управления кнопками сценариев
void AdminEditMenuController::slotSetAddScenarioButtonEnabled() {
    this->editMenuWidget->setAddScenarioButtonEnabled();
}

void AdminEditMenuController::slotSetAddScenarioButtonDisabled() {
    this->editMenuWidget->setAddScenarioButtonDisabled();
}

void AdminEditMenuController::slotSetDeleteSelectedScenariesButtonEnabled() {
    this->editMenuWidget->setDeleteSelectedScenariesButtonEnabled();
}

void AdminEditMenuController::slotSetDeleteSelectedScenariesButtonDisabled() {
    this->editMenuWidget->setDeleteSelectedScenariesButtonDisabled();
}

/// Блок управления кнопками инцидентов в сценариях
void AdminEditMenuController::slotSetAddToScenarioButtonEnabled() {
    this->editMenuWidget->setAddToScenarioButtonEnabled();
}

void AdminEditMenuController::slotSetAddToScenarioButtonDisabled() {
    this->editMenuWidget->setAddToScenarioButtonDisabled();
}

void AdminEditMenuController::slotSetRemoveFromScenarioButtonEnabled() {
    this->editMenuWidget->setRemoveFromScenarioButtonEnabled();
}

void AdminEditMenuController::slotSetRemoveFromScenarioButtonDisabled() {
    this->editMenuWidget->setRemoveFromScenarioButtonDisabled();
}
