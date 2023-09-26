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
    ///QObject::connect(uneditableCategory, &UneditableEventCategoryWidget::signalDeleteCategory, this, &AdminEditMenuWidget::signalDeleteCategory);
}

/**
 *  @brief initEditableCategory - метод, инициализирующий связь сигналов
 *  редактируемого виджета категории с данным классом, для сообщения о завершении
 *  редактирования.
 *  @param editableCategory - редактируемый виджет категории.
 */
void AdminEventCategoryBoxLayout::initEditableCategory(EditableEventCategoryWidget *editableCategory) {
    // TODO: Добавить сигнал об удалении, если при завершении редактирования виджет остался пуст
    QObject::connect(editableCategory, &EditableEventCategoryWidget::editingFinished, this, &AdminEventCategoryBoxLayout::editingFinished);
}

/**
 *  @brief addCategory - добавление категории событий в бокс категорий меню.
 *  @param uneditableCategory - не редактируемый виджет категории.
 *      Добавляется категория в качестве не редактируемого виджета, чтобы
 *  интерфейс был более удобным и понятным, если администратор ранее использовал
 *  какие-либо программы редактирования.
 */
void AdminEventCategoryBoxLayout::addCategory(UneditableEventCategoryWidget *uneditableCategory) {
    /// Инициализируем меню для виджета
    uneditableCategory->initMenu();
    /// Инициализируем связь сигналов виджета с данным классом
    this->initUneditableCategory(uneditableCategory);
    /// Добавляем виджет в boxLayout
    boxLayoutCategories->addWidget(uneditableCategory);
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
void AdminEventCategoryBoxLayout::makeCategoryEditable(UneditableEventCategoryWidget *uneditableCategory) {
    /// Берем номер позиции не редактируемого виджета
    quint32 widgetPosition = boxLayoutCategories->layout()->indexOf(uneditableCategory);
    /// Инициализируем редактируемый виджет из не редактируемого
    EditableEventCategoryWidget *editableCategory= new EditableEventCategoryWidget(uneditableCategory->getId(), uneditableCategory->getText());
    /// Инициализируем связь сигналов редактируемого виджета с данным меню
    this->initEditableCategory(editableCategory);


    ///     Удаляем не редактируемый виджет из box_layout и удаляем переменную
    /// данного виджета, чтобы не было добавляющихся фантомных виджетов
    boxLayoutCategories->removeWidget(uneditableCategory);
    delete uneditableCategory;
    /// Вставляем на ту же позицию редактируемый виджет
    boxLayoutCategories->insertWidget(widgetPosition, editableCategory);
}

/**
 *  @brief makeCategoryUneditable - изменение редактируемого виджета на не редактируемый
 *  при завершении редактирования администратором.
 *  @param editableCategory - редактируемый виджет категории, который необходимо изменить.
 */
void AdminEventCategoryBoxLayout::makeCategoryUneditable(EditableEventCategoryWidget *editableCategory) {
    /// Берем номер позиции редактируемого виджета
    quint32 widgetPosition = boxLayoutCategories->layout()->indexOf(editableCategory);
    /// Инициализируем не редактируемый виджет из редактируемого
    UneditableEventCategoryWidget *uneditableCategory= new UneditableEventCategoryWidget(editableCategory->getId(), editableCategory->getText());
    /// Инициализируем контекстное меню не редактируемого виджета
    uneditableCategory->initMenu();
    /// Инициализируем связь сигналов не редактируемого виджета с данным меню
    this->initUneditableCategory(uneditableCategory);


    ///     Удаляем редактируемый виджет из box_layout и удаляем переменную
    /// данного виджета, чтобы не было добавляющихся фантомных виджетов
    boxLayoutCategories->removeWidget(editableCategory);
    delete editableCategory;
    /// Вставляем на ту же позицию не редактируемый виджет
    boxLayoutCategories->insertWidget(widgetPosition, uneditableCategory);
}
