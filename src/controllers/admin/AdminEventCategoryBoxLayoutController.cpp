#include "AdminEventCategoryBoxLayoutController.h"


/**
 *  @brief AdminEventCategoryBoxLayoutController - не изменяемый конструктор по умолчанию
 *  @param parent - родительский объект в иерархии Qt.
 */
AdminEventCategoryBoxLayoutController::AdminEventCategoryBoxLayoutController(QObject *parent) : QObject{parent} {}

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
    QObject::connect(this->boxLayoutCategories, &AdminEventCategoryBoxLayout::signalEditCategory, this, &AdminEventCategoryBoxLayoutController::slotShowEditableWidget);
    QObject::connect(this->boxLayoutCategories, &AdminEventCategoryBoxLayout::signalDeleteCategory, this, &AdminEventCategoryBoxLayoutController::slotDeleteCategory);

    QObject::connect(this->boxLayoutCategories, &AdminEventCategoryBoxLayout::signalCategorySelected, this, &AdminEventCategoryBoxLayoutController::onCategorySelected);
    QObject::connect(this->boxLayoutCategories, &AdminEventCategoryBoxLayout::signalCategoryUnselected, this, &AdminEventCategoryBoxLayoutController::onCategoryUnselected);

    /// Блок связи сигналов, поступающих в меню редактирования из редактируемого виджета
    QObject::connect(this->boxLayoutCategories, &AdminEventCategoryBoxLayout::editingFinished, this, &AdminEventCategoryBoxLayoutController::slotShowUneditableWidget);
    QObject::connect(this->boxLayoutCategories, &AdminEventCategoryBoxLayout::emptyWidget, this, &AdminEventCategoryBoxLayoutController::slotEmptyWidget);
}

/**
 *  @brief setCategoryList - публичный слот, устанавливающий список виджетов категорий в
 *  боксе категорий.
 *  @param categories - список категорий.
 *      Срабатывает при получении сигнала от ядра программы, по которому передается
 *    список категорий.
 */
void AdminEventCategoryBoxLayoutController::setCategoryList(const QList<SecurityEventCategory> categories) {
    /// Сохраняем список категорий
    this->categories = categories;
    /// Очищаем список категорий в боксе для исключения неточностей
    this->boxLayoutCategories->clearCategories();
    /// Проходим по списку категорий, инициализируя и добавляя виджеты в бокс
    for (SecurityEventCategory cat : categories) {
        UneditableEventCategoryWidget *uneditableWidget = new UneditableEventCategoryWidget(cat.getId(), cat.getText());
        EditableEventCategoryWidget *editableWidget = new EditableEventCategoryWidget(cat.getId(), cat.getText());
        this->widgetStorage.appendWidget(uneditableWidget, editableWidget);
        //QObject::connect(categoryWidget, &UneditableEventCategoryWidget::signalOpenIncident, this, &AdminEditMenuController::signalOpenCategory);

        this->boxLayoutCategories->addCategoryWidget(uneditableWidget, editableWidget);
    }
    /// Отправляем в ядро сигнал о завершении установки списка категорий
    emit categoriesSet();
}

void AdminEventCategoryBoxLayoutController::slotShowEditableWidget(UneditableEventCategoryWidget *uneditableWidget) {
    /// Берем редактируемый виджет из хранилища, по соответствующему ему не редактируемому виджету
    EditableEventCategoryWidget *editableWidget = this->widgetStorage.getEditableWidget(uneditableWidget->getID());
    /// Показываем редактируемый виджет
    this->boxLayoutCategories->showEditableWidget(uneditableWidget, editableWidget);
}

void AdminEventCategoryBoxLayoutController::slotShowUneditableWidget(EditableEventCategoryWidget *editableWidget) {
    /// Берем не редактируемый виджет из хранилища, по соответствующему ему редактируемому виджету
    UneditableEventCategoryWidget *uneditableWidget = this->widgetStorage.getUneditableWidget(editableWidget->getID());

    /// Переименовываем категорию в списке в соответствии с переименованием виджета администратором
    this->renameCategory(uneditableWidget->getID(), uneditableWidget->getText());

    /// Устанавливаем измененное администратором имя не редактируемому виджету
    uneditableWidget->setText(editableWidget->getText());

    /// Показываем не редактируемый виджет
    this->boxLayoutCategories->showUneditableWidget(editableWidget, uneditableWidget);
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
 *  @param categoryID - id категории.
 *      Внутренний метод, вызывается в slotEmptyWidget и slotDeleteCategory.
 */
void AdminEventCategoryBoxLayoutController::deleteCategory(const quint32 categoryID) {
    /// Удаление из списка категорий контроллера необходимой категории
    /// ( удаление не изменяет айди других категорий )
    for(SecurityEventCategory &category : categories) {
        if(category.getId() == categoryID) {
            categories.removeOne(category);
        }
    }
}

/**
 *  @brief renameCategory - метод для переименования категорий из списка контроллера
 *  @param widgetID - id виджета категории.
 *  @param widgetText - текст виджета категории.
 */
void AdminEventCategoryBoxLayoutController::renameCategory(const quint32 widgetID, const QString widgetText) {
    /// Переименование в списке контроллера необходимой категории
    for(SecurityEventCategory &category : categories) {
        if(category.getId() == widgetID) {
            category.setText(widgetText);
        }
    }
}

/**
 *  @brief slotEmptyWidget - приватный слот для удаления пустого редактируемого виджета.
 *  @param editableCategory - редактируемый виджет категории.
 *      Срабатывает при получении сигнала от редактируемого виджета о том, что при завершении
 *     редактирования виджета он остался пустым.
 */
void AdminEventCategoryBoxLayoutController::slotEmptyWidget(EditableEventCategoryWidget * editableWidget) {

    UneditableEventCategoryWidget *uneditableEmptyWidget = this->widgetStorage.getUneditableWidget(editableWidget->getID());
    /// Удаляем категорию из списка контроллера
    this->deleteCategory(uneditableEmptyWidget->getID());
    /// Удаляем виджет из хранилища
    this->widgetStorage.removeWidget(uneditableEmptyWidget->getID());
    /// Удаляем виджет категории из бокса категорий
    this->boxLayoutCategories->deleteCategoryWidget(uneditableEmptyWidget);
}

/**
 *  @brief slotDeleteCategory - приватный слот для удаления не редактируемого виджета по
 *  запросу администратора через контекстное меню.
 *  @param uneditableCategory - не редактируемый виджет категории.
 *      Срабатывает при получении сигнала от не редактируемого виджета о выборе действия Удалить в
 *     контекстном меню.
 */
void AdminEventCategoryBoxLayoutController::slotDeleteCategory(UneditableEventCategoryWidget * uneditableWidget) {
    /// Удаляем категорию из списка контроллера
    this->deleteCategory(uneditableWidget->getID());
    /// Удаляем виджет из категории бокса категорий
    this->boxLayoutCategories->deleteCategoryWidget(uneditableWidget);
}

void AdminEventCategoryBoxLayoutController::slotAddCategoryButtonPressed() {
    /// Добавляем в список категорий новую категорию
    this->addCategory();
    /// Создаем из неё виджет
    UneditableEventCategoryWidget *newUneditableCategoryWidget = new UneditableEventCategoryWidget(categories.last().getId(), categories.last().getText());
    EditableEventCategoryWidget *newEditableCategoryWidget = new EditableEventCategoryWidget(categories.last().getId(), categories.last().getText());
    /// Добавляем новый виджет в хранилище
    this->widgetStorage.appendWidget(newUneditableCategoryWidget, newEditableCategoryWidget);
    /// Добавляем новый виджет в бокс
    this->boxLayoutCategories->addCategoryWidget(newUneditableCategoryWidget, newEditableCategoryWidget);
}

void AdminEventCategoryBoxLayoutController::slotDeleteSelectedCategoriesButtonPressed() {
    /// Удаляем все выбранные категории
    for(SecurityEventCategory &category : selectedCategories) {

        /// Удаляем виджет категории из бокса
        UneditableEventCategoryWidget *tempUneditableCategoryWidget = this->widgetStorage.getUneditableWidget(category.getId());
        this->boxLayoutCategories->deleteCategoryWidget(tempUneditableCategoryWidget);

        /// Удаляем виджет из хранилища
        this->widgetStorage.removeWidget(category.getId());

        /// Удаляем категорию из списка выбранных категорий контроллера
        this->onCategoryUnselected(category.getId());
        /// Удаляем категорию из списка категорий контроллера
        this->deleteCategory(category.getId());

    }
}

void AdminEventCategoryBoxLayoutController::onCategorySelected(const quint32 categoryID) {
    /// Проверка, есть ли в списке категорий такая категория
    quint32 categoriesChecked = 0;
    for(SecurityEventCategory category : categories) {
        if(category.getId() != categoryID)
            categoriesChecked++;
    }
    //if(categoriesChecked == categories.size())
        // throw

    /// Находим и забрасываем категорию в список выбранных категорий
    for(quint32 i = 0; i < categories.size(); i++) {
        SecurityEventCategory category = this->categories.at(i);
        if(category.getId() == categoryID) {
            this->selectedCategories.append(category);

        }
    }
    if(!selectedCategories.isEmpty())
        emit signalSelectedCategoriesNotEmpty();
}

void AdminEventCategoryBoxLayoutController::onCategoryUnselected(const quint32 categoryID) {
    /// Проверка, есть ли в списке категорий такая категория
    quint32 categoriesChecked = 0;
    for(SecurityEventCategory category : categories) {
        if(category.getId() != categoryID)
            categoriesChecked++;
    }
    //if(categoriesChecked == categories.size())
        // throw

    /// Находим и удаляем категорию из списка выбранных категорий
    for(quint32 i = 0; i < selectedCategories.size(); i++) {
        SecurityEventCategory selectedCategory = this->selectedCategories.at(i);
        if(selectedCategory.getId() == categoryID)
            this->selectedCategories.removeOne(selectedCategory);
    }
    if(selectedCategories.isEmpty())
        emit signalSelectedCategoriesEmpty();
}
