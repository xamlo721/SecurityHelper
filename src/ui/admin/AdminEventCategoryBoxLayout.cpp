#include "AdminEventCategoryBoxLayout.h"

/**
 *  @brief AdminEditMenuWidget - не изменяемый конструктор по умолчанию
 *  @param parent - родительский объект в иерархии Qt.
 */
AdminEventCategoryBoxLayout::AdminEventCategoryBoxLayout(QObject *parent) : QObject{parent} {

}

/**
 *  @brief init - метод, инициализирующий бокс категорий в данном классе
 *  из бокса категорий уже находящегося в AdminEditMenuWidget.
 *  @param boxLayout - бокс категорий, находящийся в AdminEditMenuWidget.
 */
void AdminEventCategoryBoxLayout::init(QVBoxLayout *boxLayout) {
    /// Инициализация бокса категорий данного класса боксом категорий из
    /// AdminMenuEditWidget, для управления им
    boxLayoutCategories = boxLayout;
}

/**
 *  @brief initUneditableCategory - метод, инициализирующий связь сигналов
 *  не редактируемого виджета категории с данным классом, для сообщения о запросе
 *  администратором на редактирование или удаление категории.
 *  @param uneditableCategory - не редактируемый виджет категории.
 */
void AdminEventCategoryBoxLayout::initUneditableCategory(UneditableEventCategoryWidget *uneditableCategory) {
    QObject::connect(uneditableCategory, &UneditableEventCategoryWidget::signalEditCategory, this, &AdminEventCategoryBoxLayout::signalEditCategory);
    QObject::connect(uneditableCategory, &UneditableEventCategoryWidget::signalDeleteCategory, this, &AdminEventCategoryBoxLayout::signalDeleteCategory);
}

/**
 *  @brief initEditableCategory - метод, инициализирующий связь сигналов
 *  редактируемого виджета категории с данным классом, для сообщения о завершении
 *  редактирования.
 *  @param editableCategory - редактируемый виджет категории.
 */
void AdminEventCategoryBoxLayout::initEditableCategory(EditableEventCategoryWidget *editableCategory) {
    QObject::connect(editableCategory, &EditableEventCategoryWidget::editingFinished, this, &AdminEventCategoryBoxLayout::editingFinished);
    QObject::connect(editableCategory, &EditableEventCategoryWidget::emptyWidget, this, &AdminEventCategoryBoxLayout::emptyWidget);
}

/**
 *  @brief addCategory - добавление категории событий в бокс категорий меню.
 *  @param uneditableCategory - не редактируемый виджет категории.
 *      Добавляется категория в качестве не редактируемого виджета, чтобы
 *  интерфейс был более удобным и понятным, если администратор ранее использовал
 *  какие-либо программы редактирования.
 */
void AdminEventCategoryBoxLayout::addCategoryWidget(UneditableEventCategoryWidget *uneditableCategory) {
    /// Инициализируем меню для виджета
    uneditableCategory->initMenu();
    /// Инициализируем связь сигналов виджета с данным классом
    this->initUneditableCategory(uneditableCategory);
    /// Добавляем виджет в boxLayout
    boxLayoutCategories->addWidget(uneditableCategory);
}

/**
 *  @brief deleteCategoryWidget - Удаление виджета категории.
 *  @param uneditableCategory - не редактируемый виджет категории, предназначенный
 *  для удаления.
 */
void AdminEventCategoryBoxLayout::deleteCategoryWidget(UneditableEventCategoryWidget *uneditableCategory) {
    /// Удаляем виджет из бокса
    this->boxLayoutCategories->removeWidget(uneditableCategory);
    /// Удаляем переменную виджета категории
    uneditableCategory->deleteLater();
}

/**
 *  @brief clearCategories - очистка списка виджетов категорий.
 */
void AdminEventCategoryBoxLayout::clearCategories() {
    /// Проходимся по всем layout, которые не NULL и удаляем виджет вместе с итемом
    if(boxLayoutCategories->layout() != NULL) {
        QLayoutItem* item;
        while ( ( item = boxLayoutCategories->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
    }

}

/**
 *  @brief makeCategoryEditable - изменение не редактируемого виджета на редактируемый
 *  для возможности изменения имени категории.
 *  @param uneditableCategory - не редактируемый виджет категории, который необходимо изменить.
 */
EditableEventCategoryWidget *AdminEventCategoryBoxLayout::makeCategoryEditable(UneditableEventCategoryWidget *uneditableCategory) {
    /// Берем номер позиции не редактируемого виджета
    quint32 widgetPosition = boxLayoutCategories->layout()->indexOf(uneditableCategory);
    /// Инициализируем редактируемый виджет из не редактируемого
    EditableEventCategoryWidget *editableCategory= new EditableEventCategoryWidget(uneditableCategory->getId(), uneditableCategory->getText());
    /// Инициализируем связь сигналов редактируемого виджета с данным меню
    this->initEditableCategory(editableCategory);


    /// Удаляем не редактируемый виджет из box_layout
    boxLayoutCategories->removeWidget(uneditableCategory);
    /// Удаляем сам виджет через deleteLater(), чтобы сохранился порядок указателей и не крашнулось приложение
    uneditableCategory->deleteLater();
    /// Вставляем на ту же позицию редактируемый виджет
    boxLayoutCategories->insertWidget(widgetPosition, editableCategory);
    /// Устанавливаем виджету фокус, чтобы активный редактируемый виджет был только один
    editableCategory->setFocus();
    /// Возвращаем измененный виджет
    return editableCategory;
}

/**
 *  @brief makeCategoryUneditable - изменение редактируемого виджета на не редактируемый
 *  при завершении редактирования администратором.
 *  @param editableCategory - редактируемый виджет категории, который необходимо изменить.
 */
UneditableEventCategoryWidget *AdminEventCategoryBoxLayout::makeCategoryUneditable(EditableEventCategoryWidget *editableCategory) {
    /// Берем номер позиции редактируемого виджета
    quint32 widgetPosition = boxLayoutCategories->layout()->indexOf(editableCategory);
    /// Инициализируем не редактируемый виджет из редактируемого
    UneditableEventCategoryWidget *uneditableCategory= new UneditableEventCategoryWidget(editableCategory->getId(), editableCategory->getText());
    /// Инициализируем контекстное меню не редактируемого виджета
    uneditableCategory->initMenu();
    /// Инициализируем связь сигналов не редактируемого виджета с данным меню
    this->initUneditableCategory(uneditableCategory);


    /// Удаляем редактируемый виджет из box_layout
    boxLayoutCategories->removeWidget(editableCategory);
    /// Удаляем сам виджет через deleteLater(), чтобы сохранился порядок указателей и не крашнулось приложение
    editableCategory->deleteLater();
    /// Вставляем на ту же позицию не редактируемый виджет
    boxLayoutCategories->insertWidget(widgetPosition, uneditableCategory);
    /// Возвращаем измененный виджет
    return uneditableCategory;
}
