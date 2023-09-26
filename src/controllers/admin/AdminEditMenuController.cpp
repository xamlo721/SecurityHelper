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
    /// Устанавливаем прокручиваемый список item'ов
    editMenuWidget->setupScrollAreas();
}
