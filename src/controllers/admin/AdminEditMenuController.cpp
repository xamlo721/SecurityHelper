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

    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalAddEventButtonPressed, this, &AdminEditMenuController::signalAddEventButtonPressed);
    QObject::connect(this->editMenuWidget, &AdminEditMenuWidget::signalDeleteSelectedEventsButtonPressed, this, &AdminEditMenuController::signalDeleteSelectedEventsButtonPressed);

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

// Блок управления кнопками категорий
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

// Блок управления кнопками событий
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
