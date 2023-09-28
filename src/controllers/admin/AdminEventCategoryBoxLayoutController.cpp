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
    QObject::connect(this->boxLayoutCategories, &AdminEventCategoryBoxLayout::signalEditCategory, this, &AdminEventCategoryBoxLayoutController::slotMakeCategoryEditable);
    QObject::connect(this->boxLayoutCategories, &AdminEventCategoryBoxLayout::signalDeleteCategory, this, &AdminEventCategoryBoxLayoutController::slotDeleteCategory);
    /// Блок связи сигналов, поступающих в меню редактирования из редактируемого виджета
    QObject::connect(this->boxLayoutCategories, &AdminEventCategoryBoxLayout::editingFinished, this, &AdminEventCategoryBoxLayoutController::slotMakeCategoryUneditableable);
    QObject::connect(this->boxLayoutCategories, &AdminEventCategoryBoxLayout::emptyWidget, this, &AdminEventCategoryBoxLayoutController::slotEmptyWidget);
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

        this->boxLayoutCategories->addCategoryWidget(categoryWidget);
    }
}

/**
 *  @brief makeCategoryEditable - приватный слот для изменения не редактируемого виджета на редактируемый
 *  для возможности изменения имени категории.
 *  @param uneditableCategory - не редактируемый виджет категории, который необходимо изменить.
 *      Срабатывает при получении сигнала от не редактируемого виджета о запросе администратора.
 */
void AdminEventCategoryBoxLayoutController::slotMakeCategoryEditable(UneditableEventCategoryWidget *uneditableCategory) {
    this->boxLayoutCategories->makeCategoryEditable(uneditableCategory);
}

/**
 *  @brief makeCategoryUneditable - приватный слот для изменения редактируемого виджета на не редактируемый
 *  при завершении редактирования администратором.
 *  @param editableCategory - редактируемый виджет категории, который необходимо изменить.
 *      Срабатывает при получении сигнала от редактируемого виджета о завершении редактирования
 *    администратором .
 */
void AdminEventCategoryBoxLayoutController::slotMakeCategoryUneditableable(EditableEventCategoryWidget *editableCategory) {
    /// Делаем виджет не редактируемым
    UneditableEventCategoryWidget *tempCategory = this->boxLayoutCategories->makeCategoryUneditable(editableCategory);
    /// Переименовываем категорию в списке в соответствии с переименованием виджета администратором
    this->renameCategory(tempCategory);
}

void AdminEventCategoryBoxLayoutController::addCategory() {
    ///     Создаем новую категорию с id большим на 1, чем у последней категории, именем Новая категория и
    /// пустым списком событий
    SecurityEventCategory newCategory(categories.last().getId() + 1, "Новая категория", QList<quint32>());
    /// Добавляем новую категорию в список категорий контроллера
    categories.append(newCategory);
}

/**
 *  @brief deleteCategory - метод для удаления категорий из списка контроллера
 *  @param uneditableCategory - не редактируемый виджет категории, категорию которого
 *  нужно удалить из списка.
 *      Внутренний метод, вызывается в slotEmptyWidget и slotDeleteCategory.
 */
void AdminEventCategoryBoxLayoutController::deleteCategory(UneditableEventCategoryWidget * uneditableCategory) {
    /// Удаление из списка категорий контроллера необходимой категории
    /// ( удаление не изменяет айди других категорий )
    for(SecurityEventCategory &category : categories) {
        if(category.getId() == uneditableCategory->getId()) {
            categories.removeOne(category);
            category.deleteLater();
        }
    }
}

/**
 *  @brief renameCategory - метод для переименования категорий из списка контроллера
 *  @param uneditableCategory - не редактируемый виджет категории, категорию которого
 *  нужно переименовать в списке.
 *      Внутренний метод, вызывается в slotMakeCategoryUneditable.
 */
void AdminEventCategoryBoxLayoutController::renameCategory(UneditableEventCategoryWidget * uneditableCategory) {
    /// Переименование в списке контроллера необходимой категории
    for(SecurityEventCategory &category : categories) {
        if(category.getId() == uneditableCategory->getId()) {
            category.setText(uneditableCategory->getText());
        }
    }
}

/**
 *  @brief slotEmptyWidget - приватный слот для удаления пустого редактируемого виджета.
 *  @param editableCategory - редактируемый виджет категории, который необходимо удалить.
 *      Срабатывает при получении сигнала от редактируемого виджета о том, что при завершении
 *     редактирования виджета он остался пустым.
 */
void AdminEventCategoryBoxLayoutController::slotEmptyWidget(EditableEventCategoryWidget * editableCategory) {
    /// Превращаем виджет категории в не редактируемый
    UneditableEventCategoryWidget *undetitableCategoryTemp = this->boxLayoutCategories->makeCategoryUneditable(editableCategory);
    /// Удаляем категорию из списка контроллера
    this->deleteCategory(undetitableCategoryTemp);
    /// Удаляем виджет категории из бокса категорий
    this->boxLayoutCategories->deleteCategoryWidget(undetitableCategoryTemp);
}

/**
 *  @brief slotDeleteCategory - приватный слот для удаления не редактируемого виджета по
 *  запросу администратора через контекстное меню.
 *  @param uneditableCategory - не редактируемый виджет категории, который необходимо удалить.
 *      Срабатывает при получении сигнала от не редактируемого виджета о выборе действия Удалить в
 *     контекстном меню.
 */
void AdminEventCategoryBoxLayoutController::slotDeleteCategory(UneditableEventCategoryWidget * uneditableCategory) {
    /// Удаляем категорию из списка контроллера
    this->deleteCategory(uneditableCategory);
    /// Удаляем виджет из категории бокса категорий
    this->boxLayoutCategories->deleteCategoryWidget(uneditableCategory);
}

void AdminEventCategoryBoxLayoutController::slotAddCategoryButtonPressed() {
    /// Добавляем в список категорий новую категорию
    this->addCategory();
    /// Создаем из неё виджет
    UneditableEventCategoryWidget *newCategoryWidget = new UneditableEventCategoryWidget(categories.last().getId(), categories.last().getText());
    /// Добавляем новый виджет в бокс
    this->boxLayoutCategories->addCategoryWidget(newCategoryWidget);
}

void AdminEventCategoryBoxLayoutController::slotDeleteCategoryButtonPressed() {

}
