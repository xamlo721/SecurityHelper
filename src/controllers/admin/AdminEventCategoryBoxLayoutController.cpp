#include "AdminEventCategoryBoxLayoutController.h"

/**
 *  @brief AdminEventCategoryBoxLayoutController - не изменяемый конструктор по умолчанию
 *  @param parent - родительский объект в иерархии Qt.
 */
AdminEventCategoryBoxLayoutController::AdminEventCategoryBoxLayoutController(QObject *parent) : QObject{parent} {

}

/**
 *  @brief init - метод, инициализирующий бокс категорий в данном классе
 *  из бокса категорий уже находящегося в AdminEditMenuWidget для его управления
 *  данным классом.
 *  @param boxLayout - бокс категорий, находящийся в AdminEditMenuWidget.
 */
void AdminEventCategoryBoxLayoutController::init(QVBoxLayout *editMenuBoxLayoutCategories) {
    /// Выделяем память под бокс категорий
    this->boxLayoutCategories = new AdminEventCategoryBoxLayout();
    /// Инициализируем бокс категорий тем боксом, который уже находится в AdminEditMenuWidget
    this->boxLayoutCategories->init(editMenuBoxLayoutCategories);

    /// Блок связи сигналов, поступающих в меню редактирования из не редактируемого виджета
    QObject::connect(this->boxLayoutCategories, &AdminEventCategoryBoxLayout::signalEditCategory, this, &AdminEventCategoryBoxLayoutController::makeCategoryEditable);

    /// Блок связи сигналов, поступающих в меню редактирования из редактируемого виджета
    QObject::connect(this->boxLayoutCategories, &AdminEventCategoryBoxLayout::editingFinished, this, &AdminEventCategoryBoxLayoutController::makeCategoryUneditable);
}

/**
 *  @brief setCategoryList - публичный слот, устанавливающий список виджетов категорий в
 *  боксе категорий.
 *  @param categories - список категорий.
 *      Срабатывает при получении сигнала от ядра программы, по которому передается
 *    список категорий.
 */
void AdminEventCategoryBoxLayoutController::setCategoryList(QList<SecurityEventCategory> categories) {
    /// Сохраняем список категорий
    this->categories = categories;
    /// Очищаем список категорий в боксе для исключения неточностей
    this->boxLayoutCategories->clearCategories();
    /// Проходим по списку категорий, инициализируя и добавляя виджеты в бокс
    for (SecurityEventCategory cat : categories) {
        UneditableEventCategoryWidget *categoryWidget = new UneditableEventCategoryWidget(cat.getId(), cat.getText());
        //QObject::connect(categoryWidget, &UneditableEventCategoryWidget::signalOpenIncident, this, &AdminEditMenuController::signalOpenCategory);

        this->boxLayoutCategories->addCategory(categoryWidget);
    }
}

/**
 *  @brief makeCategoryEditable - приватный слот для изменения не редактируемого виджета на редактируемый
 *  для возможности изменения имени категории.
 *  @param uneditableCategory - не редактируемый виджет категории, который необходимо изменить.
 *      Срабатывает при получении сигнала от не редактируемого виджета о запросе администратора.
 */
void AdminEventCategoryBoxLayoutController::makeCategoryEditable(UneditableEventCategoryWidget *uneditableCategory) {
    this->boxLayoutCategories->makeCategoryEditable(uneditableCategory);
}

/**
 *  @brief makeCategoryUneditable - приватный слот для изменения редактируемого виджета на не редактируемый
 *  при завершении редактирования администратором.
 *  @param editableCategory - редактируемый виджет категории, который необходимо изменить.
 *      Срабатывает при получении сигнала от редактируемого виджета о завершении редактирования
 *    администратором .
 */
void AdminEventCategoryBoxLayoutController::makeCategoryUneditable(EditableEventCategoryWidget *editableCategory) {
    this->boxLayoutCategories->makeCategoryUneditable(editableCategory);
}
