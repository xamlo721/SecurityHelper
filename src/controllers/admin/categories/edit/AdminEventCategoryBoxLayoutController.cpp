#include "AdminEventCategoryBoxLayoutController.h"

#include "src/ui/admin/ItemDeletionMessageBox.h"
#include "src/ui/admin/EnumMessageBoxVariants.h"
#include "src/ui/admin/EnumMessageBoxItemVariants.h"

/**
 *  @brief AdminEventCategoryBoxLayoutController - не изменяемый конструктор по умолчанию
 *  @param parent - родительский объект в иерархии Qt.
 */
AdminEventCategoryBoxLayoutController::AdminEventCategoryBoxLayoutController(QObject *parent) : QObject{parent} {}

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

        this->addCategoryWidget(cat);
    }
    /// Отправляем в ядро сигнал о завершении установки списка категорий
    emit categoryListSet();
}

void AdminEventCategoryBoxLayoutController::slotShowEditableWidget(UneditableEventCategoryWidget *uneditableWidget) {
    /// Берем редактируемый виджет из хранилища, по соответствующему ему не редактируемому виджету
    EditableEventCategoryWidget *editableWidget = this->widgetStorage.getEditableWidget(uneditableWidget->getID());
    /// Показываем редактируемый виджет
    this->boxLayoutCategories->showEditableWidget(uneditableWidget, editableWidget);

    /// Делаем все категории не выбранными
    this->unselectAllCategories();
    /// Делаем все категории не доступными
    this->disableAllCategories();

    /// Отправляем сигнал о том, что появилась активная категория
    emit categoryIsActive();

    /// Отправляем сигнал о том, что категория открыта
    emit categoryIsOpened(editableWidget->getID());
}

void AdminEventCategoryBoxLayoutController::slotShowUneditableWidget(EditableEventCategoryWidget *editableWidget) {
    /// Берем не редактируемый виджет из хранилища, по соответствующему ему редактируемому виджету
    UneditableEventCategoryWidget *uneditableWidget = this->widgetStorage.getUneditableWidget(editableWidget->getID());

    /// Переименовываем категорию в списке в соответствии с переименованием виджета администратором
    this->renameCategory(editableWidget->getID(), editableWidget->getTitle());

    /// Устанавливаем измененное администратором имя не редактируемому виджету
    uneditableWidget->setTitle(editableWidget->getTitle());

    /// Сохраняем список категорий в бд
    emit categoriesMustBeSaved(this->categories);

    /// Показываем не редактируемый виджет
    this->boxLayoutCategories->showUneditableWidget(editableWidget, uneditableWidget);

    /// Делаем все категории доступными
    this->enableAllCategories();
    /// Отправляем сигнал о том, что активной категории больше нет
    emit categoryIsNotActive();

    /// Отправляем сигнал о том, что категория закрыта
    emit categoryIsClosed(editableWidget->getID());
}

SecurityEventCategory AdminEventCategoryBoxLayoutController::addCategory() {
    quint32 newCategoryId = 0;
    for(SecurityEventCategory category : categories) {
        if(newCategoryId < category.getId())
            newCategoryId = category.getId();
    }
    newCategoryId += 1;

    ///     Создаем новую категорию с id большим на 1, чем у последней категории, именем Новая категория и
    /// пустым списком событий
    SecurityEventCategory newCategory(newCategoryId, "Новая категория", QList<quint32>());
    /// Добавляем новую категорию в список категорий контроллера
    categories.append(newCategory);

    return newCategory;
}

void AdminEventCategoryBoxLayoutController::addCategoryWidget(const SecurityEventCategory category) {
    /// Создаем пару виджетов для категории
    UneditableEventCategoryWidget *newUneditableCategoryWidget = new UneditableEventCategoryWidget(category.getId(), category.getText());
    EditableEventCategoryWidget *newEditableCategoryWidget = new EditableEventCategoryWidget(category.getId(), category.getText());

    /// Добавляем новую пару виджетов в хранилище
    this->widgetStorage.appendWidget(newUneditableCategoryWidget, newEditableCategoryWidget);
    /// Добавляем новую пару виджетов в лайаут
    this->boxLayoutCategories->addCategoryWidget(newUneditableCategoryWidget, newEditableCategoryWidget);
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

            /// Если эта категория находится в списке выбранных, удаляем её из этого списка
            if(this->selectedCategories.contains(category))
                this->onCategoryUnselected(category.getId());

            /// Удаляем категорию из списка контроллера
            categories.removeOne(category);

        }
    }

    emit categoryIsDeleted(categoryID);

}

void AdminEventCategoryBoxLayoutController::deleteCategoryWidget(const quint32 categoryID) {
    UneditableEventCategoryWidget *tempWidget = this->widgetStorage.getUneditableWidget(categoryID);
    this->widgetStorage.removeWidget(categoryID);
    this->boxLayoutCategories->deleteCategoryWidget(tempWidget);
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

void AdminEventCategoryBoxLayoutController::unselectAllCategories() {
    for(SecurityEventCategory category : selectedCategories) {
        /// Берем не редактируемый виджет из хранилища по ID категории и делаем его не выбранным
        this->boxLayoutCategories->unselectUneditableWidget(this->widgetStorage.getUneditableWidget(category.getId()));
    }
}

void AdminEventCategoryBoxLayoutController::enableAllCategories() {
    for(SecurityEventCategory category : categories) {
        /// Берем не редактируемый виджет из хранилища по ID категории и делаем его доступным
        this->boxLayoutCategories->enableUneditableWidget(this->widgetStorage.getUneditableWidget(category.getId()));
    }
}

void AdminEventCategoryBoxLayoutController::disableAllCategories() {
    for(SecurityEventCategory category : categories) {
        /// Берем не редактируемый виджет из хранилища по ID категории и делаем его не доступным
        this->boxLayoutCategories->disableUneditableWidget(this->widgetStorage.getUneditableWidget(category.getId()));
    }
}

/**
 *  @brief slotDeleteCategory - приватный слот для удаления не редактируемого виджета по
 *  запросу администратора через контекстное меню.
 *  @param uneditableCategory - не редактируемый виджет категории.
 *      Срабатывает при получении сигнала от не редактируемого виджета о выборе действия Удалить в
 *     контекстном меню.
 */
void AdminEventCategoryBoxLayoutController::slotDeleteCategory(UneditableEventCategoryWidget * uneditableWidget) {
    /// Создаем окно сообщений
    ItemDeletionMessageBox messageBox;
    /// Вызываем его в режиме предупреждения, если администратор нажмет Да, то удаляем категорию
    if(messageBox.openWarning(EnumMessageBoxVariants::DeletionOneItem, EnumMessageBoxItemVariants::EventCategory) == ItemDeletionMessageBox::Yes) {

        /// Удаляем виджет
        this->deleteCategoryWidget(uneditableWidget->getID());
        /// Удаляем категорию
        this->deleteCategory(uneditableWidget->getID());

        /// Производим разблокировку интерфейса
        this->enableAllCategories();
        emit categoryIsNotActive();
    }
}

void AdminEventCategoryBoxLayoutController::slotAddCategoryButtonPressed() {
    /// Добавляем новую категорию и пару виджетов для неё
    this->addCategoryWidget(this->addCategory());
}

void AdminEventCategoryBoxLayoutController::slotDeleteSelectedCategoriesButtonPressed() {
    /// Создаем окно сообщений
    ItemDeletionMessageBox messageBox;
    /// Вызываем его в режиме предупреждения, если администратор нажмет Да, то удаляем выбранные категории
    if(messageBox.openWarning(EnumMessageBoxVariants::DeletionSeveralItems, EnumMessageBoxItemVariants::EventCategory) == ItemDeletionMessageBox::Yes) {
        /// Удаляем все выбранные категории
        for(SecurityEventCategory &category : selectedCategories) {

            /// Удаляем виджет
            this->deleteCategoryWidget(category.getId());
            /// Удаляем категорию
            this->deleteCategory(category.getId());

            /// Производим разблокировку интерфейса
            this->enableAllCategories();
            emit categoryIsNotActive();
        }
    }
}

void AdminEventCategoryBoxLayoutController::onCategorySelected(const quint32 categoryID) {
    /// Проверка, есть ли в списке категорий такая категория
    quint32 categoriesChecked = 0;
    for(SecurityEventCategory category : categories) {
        if(category.getId() != categoryID)
            categoriesChecked++;
    }

    /// Если категории нет в списке контроллера, то бросаем исключение
    /*if(categoriesChecked == categories.size()) {
        throw
    }*/


    /// Обнуляем счетчик для проверки по списку выбранных категорий
    categoriesChecked = 0;
    for(SecurityEventCategory selectedCategory : selectedCategories) {
        if(selectedCategory.getId() == categoryID)
            categoriesChecked++;
    }

    /// categoriesChecked будет равна 1, только если такая категория уже есть в списке выбранных
    /// Если такой категории в списке выбранных нет, то добавляем иначе бросаем исключение
    if(categoriesChecked != 1) {

        /// Находим и забрасываем категорию в список выбранных категорий
        for(quint32 i = 0; i < categories.size(); i++) {
            SecurityEventCategory category = this->categories.at(i);

            if(category.getId() == categoryID)
                this->selectedCategories.append(category);
        }
    }

    // else throw

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

    /// Если категории нет в списке контроллера, то бросаем исключение
    //if(categoriesChecked == categories.size())
        //throw


    /// Обнуляем счетчик для проверки по списку выбранных категорий
    categoriesChecked = 0;
    for(SecurityEventCategory selectedCategory : selectedCategories) {
        if(selectedCategory.getId() == categoryID)
            categoriesChecked++;
    }

    /// categoriesChecked будет равна 1, только если такая категория уже есть в списке выбранных
    /// Если такой категории нет в списке выбранных, то бросаем исключение иначе удаляем из списка
    if(categoriesChecked != 1) {
        // throw
    }

    else {
        /// Находим и удаляем категорию из списка выбранных категорий
        for(quint32 i = 0; i < selectedCategories.size(); i++) {
            SecurityEventCategory selectedCategory = this->selectedCategories.at(i);

            if(selectedCategory.getId() == categoryID)
                this->selectedCategories.removeOne(selectedCategory);
        }
    }

    if(selectedCategories.isEmpty())
        emit signalSelectedCategoriesEmpty();
}
