#include "AdminEventCategoryBoxLayout.h"

/**
 *  @brief AdminEditMenuWidget - не изменяемый конструктор по умолчанию
 *  @param parent - родительский объект в иерархии Qt.
 */
AdminEventCategoryBoxLayout::AdminEventCategoryBoxLayout(QObject *parent) : QObject{parent} {}


void AdminEventCategoryBoxLayout::init(QVBoxLayout *boxLayout) {
    this->boxLayoutCategories = boxLayout;
}

/**
 *  @brief initUneditableCategory - метод, инициализирующий связь сигналов
 *  не редактируемого виджета категории с данным классом, для сообщения о запросе
 *  администратором на редактирование или удаление категории.
 *  @param uneditableCategory - не редактируемый виджет категории.
 */
void AdminEventCategoryBoxLayout::initUneditableWidget(UneditableEventCategoryWidget *uneditableWidget) {
    QObject::connect(uneditableWidget, &UneditableEventCategoryWidget::signalEditCategory, this, &AdminEventCategoryBoxLayout::signalEditCategory);
    QObject::connect(uneditableWidget, &UneditableEventCategoryWidget::signalDeleteCategory, this, &AdminEventCategoryBoxLayout::signalDeleteCategory);

    QObject::connect(uneditableWidget, &UneditableEventCategoryWidget::signalCategorySelected, this, &AdminEventCategoryBoxLayout::signalCategorySelected);
    QObject::connect(uneditableWidget, &UneditableEventCategoryWidget::signalCategoryUnselected, this, &AdminEventCategoryBoxLayout::signalCategoryUnselected);
}

/**
 *  @brief initEditableCategory - метод, инициализирующий связь сигналов
 *  редактируемого виджета категории с данным классом, для сообщения о завершении
 *  редактирования.
 *  @param editableCategory - редактируемый виджет категории.
 */
void AdminEventCategoryBoxLayout::initEditableWidget(EditableEventCategoryWidget *editableWidget) {
    QObject::connect(editableWidget, &EditableEventCategoryWidget::editingFinished, this, &AdminEventCategoryBoxLayout::editingFinished);
    QObject::connect(editableWidget, &EditableEventCategoryWidget::emptyWidget, this, &AdminEventCategoryBoxLayout::emptyWidget);
}

void AdminEventCategoryBoxLayout::addCategoryWidget(UneditableEventCategoryWidget *uneditableWidget, EditableEventCategoryWidget *editableWidget) {
    /// Инициализируем меню для не редактируемого виджета
    uneditableWidget->initMenu();
    /// Инициализируем связь сигналов виджетов с данным классом
    this->initUneditableWidget(uneditableWidget);
    this->initEditableWidget(editableWidget);

    /// Создаем бокс для пар виджетов и добавляем в него виджеты
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(uneditableWidget);
    layout->addWidget(editableWidget);

    /// Скрываем редактируемый виджет
    editableWidget->hide();
    /// Добавляем в общий бокс бокс пар виджетов
    this->boxLayoutCategories->addLayout(layout);
    /// Добавляем в лист бокс пар виджетов
    this->widgetBoxLayouts.append(layout);
}

/**
 *  @brief deleteCategoryWidget - Удаление виджета категории.
 *  @param uneditableCategory - не редактируемый виджет категории, предназначенный
 *  для удаления.
 */
void AdminEventCategoryBoxLayout::deleteCategoryWidget(UneditableEventCategoryWidget *uneditableWidget) {
    /// Проходим по листу боксов пар виджетов и удаляем бокс, который содержит в себе uneditableWidget
    for(QVBoxLayout *layout : widgetBoxLayouts){
        if(layout->itemAt(0)->widget() == uneditableWidget) {
            QLayoutItem* item;
                while ( ( item = layout->takeAt( 0 ) ) != NULL ) {
                    delete item->widget();
                    delete item;
                }
            this->widgetBoxLayouts.removeOne(layout);
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
    if(this->boxLayoutCategories->layout() != NULL) {
        QLayoutItem* item;
        while ( ( item = this->boxLayoutCategories->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
    }

}

void AdminEventCategoryBoxLayout::showEditableWidget(UneditableEventCategoryWidget *uneditableWidget, EditableEventCategoryWidget *editableWidget) {
    /// Скрываем не редактируемый виджет
    uneditableWidget->hide();
    /// Показываем редактируемый виджет
    editableWidget->show();
    /// Устанавливаем фокус редактируемому виджету
    editableWidget->setFocus();
}

void AdminEventCategoryBoxLayout::showUneditableWidget(EditableEventCategoryWidget *editableWidget, UneditableEventCategoryWidget *uneditableWidget) {
    /// Скрываем не редактируемый виджет
    editableWidget->hide();
    /// Показываем не редактируемый виджет
    uneditableWidget->show();
}

void AdminEventCategoryBoxLayout::unselectUneditableWidget(UneditableEventCategoryWidget *uneditableWidget) {
    uneditableWidget->setUnselected();
}

void AdminEventCategoryBoxLayout::enableUneditableWidget(UneditableEventCategoryWidget *uneditableWidget) {
    uneditableWidget->setEnabled(true);
}

void AdminEventCategoryBoxLayout::disableUneditableWidget(UneditableEventCategoryWidget *uneditableWidget) {
    uneditableWidget->setEnabled(false);
}
