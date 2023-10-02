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

    QObject::connect(uneditableCategory, &UneditableEventCategoryWidget::signalCategorySelected, this, &AdminEventCategoryBoxLayout::signalCategorySelected);
    QObject::connect(uneditableCategory, &UneditableEventCategoryWidget::signalCategoryUnselected, this, &AdminEventCategoryBoxLayout::signalCategoryUnselected);
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

void AdminEventCategoryBoxLayout::addCategoryWidget(UneditableEventCategoryWidget *uneditableWidget, EditableEventCategoryWidget *editableWidget) {
    /// Инициализируем меню для не редактируемого виджета
    uneditableWidget->initMenu();
    /// Инициализируем связь сигналов виджетов с данным классом
    this->initUneditableCategory(uneditableWidget);
    this->initEditableCategory(editableWidget);

    /// Создаем бокс для пар виджетов и добавляем в него виджеты
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(uneditableWidget);
    layout->addWidget(editableWidget);

    /// Скрываем редактируемый виджет
    editableWidget->hide();
    /// Добавляем в общий бокс бокс пар виджетов
    boxLayoutCategories->addLayout(layout);
    /// Добавляем в лист бокс пар виджетов
    widgetBoxLayout.append(layout);
}

/**
 *  @brief deleteCategoryWidget - Удаление виджета категории.
 *  @param uneditableCategory - не редактируемый виджет категории, предназначенный
 *  для удаления.
 */
void AdminEventCategoryBoxLayout::deleteCategoryWidget(UneditableEventCategoryWidget *uneditableWidget) {
    /// Проходим по листу боксов пар виджетов и удаляем бокс, который содержит в себе uneditableWidget
    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == uneditableWidget) {
            QLayoutItem* item;
                while ( ( item = layout->takeAt( 0 ) ) != NULL ) {
                    delete item->widget();
                    delete item;
                }
            this->widgetBoxLayout.removeOne(layout);
            this->boxLayoutCategories->removeItem(layout);
            layout->deleteLater();
        }
    }
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

void AdminEventCategoryBoxLayout::showEditableWidget(UneditableEventCategoryWidget *uneditableWidget, EditableEventCategoryWidget *editableWidget) {
    //  TODO: Исправить баг, с двойным срабатываем в EditableEventCategoryWidget сигнала editingFinished при потере виджетом фокуса


    /// Скрываем не редактируемый виджет
    uneditableWidget->hide();
    /// Показываем редактируемый виджет
    editableWidget->show();
    /// Устанавливаем редактируемому виджету фокус
    editableWidget->setFocus();
}

void AdminEventCategoryBoxLayout::showUneditableWidget(EditableEventCategoryWidget *editableWidget, UneditableEventCategoryWidget *uneditableWidget) {
    /// Скрываем не редактируемый виджет
    editableWidget->hide();
    /// Показываем не редактируемый виджет
    uneditableWidget->show();
}
