#include "UneditableItemMenu.h"

/**
 *      @brief UneditableItemMenu - конструктор по умолчанию,
 * в котором инициализируется меню.
 *  @param parent - родительский объект в иерархии Qt.
 */
UneditableItemMenu::UneditableItemMenu(QObject *parent) : QObject{parent} {
    menu = new QMenu();

    QString  menuStyle(
               "QMenu {"
               "background-color: #85c7c7;"
               "color: black;"
               "}"
               "QMenu::item:selected{"
               "background-color: #aaffff;"
               "color: black;"
               "}"
            );
    this->menu->setStyleSheet(menuStyle);
}

/**
 *  @brief setup - метод, устанавливающий действия (QAction) в меню.
 */
void UneditableItemMenu::setup() {
    /// Инициализация действий
    editAction = new QAction("Редактировать");
    deleteAction = new QAction("Удалить");

    /// Добавление действий в меню
    menu->addAction(editAction);
    menu->addAction(deleteAction);
}

/**
 *      @brief init - инициализация связи сигналов
 * действий (QAction) с сигналами класса UneditableItemMenu.
 * В данном случае, связываются слоты triggered класса QAction,
 * что позволит при нажатии на действии в меню отправить сигнал
 * вверх по иерархии интерфейса.
 */
void UneditableItemMenu::init() {
    QObject::connect(editAction, &QAction::triggered, this, &UneditableItemMenu::signalEditCategory);
    QObject::connect(deleteAction, &QAction::triggered, this, &UneditableItemMenu::signalDeleteCategory);
}

/**
 *      @brief call - публичный слот, который выполняет вызов
 * кастомизированного меню по позиции курсора.
 */
void UneditableItemMenu::call(QPoint mousePosition) {
    menu->popup(mousePosition);
}
