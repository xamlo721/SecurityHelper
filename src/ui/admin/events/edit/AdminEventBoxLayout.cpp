#include "AdminEventBoxLayout.h"

AdminEventBoxLayout::AdminEventBoxLayout(QObject *parent) : QObject{parent} {}

void AdminEventBoxLayout::init(QVBoxLayout *boxLayout) {
    ///  Инициализация бокса категорий данного класса боксом категорий из
    /// AdminMenuEditWidget, для управления им
    this->boxLayoutEvents = boxLayout;
}

void AdminEventBoxLayout::initUneditableWidget(UneditableEventWidget *uneditableWidget) {
    QObject::connect(uneditableWidget, &UneditableEventWidget::signalEditEvent, this, &AdminEventBoxLayout::signalEditEvent);
    QObject::connect(uneditableWidget, &UneditableEventWidget::signalDeleteEvent, this, &AdminEventBoxLayout::signalDeleteEvent);

    QObject::connect(uneditableWidget, &UneditableEventWidget::signalEventSelected, this, &AdminEventBoxLayout::signalEventSelected);
    QObject::connect(uneditableWidget, &UneditableEventWidget::signalEventUnselected, this, &AdminEventBoxLayout::signalEventUnselected);
}

void AdminEventBoxLayout::initEditableWidget(EditableEventWidget *editableWidget) {
    QObject::connect(editableWidget, &EditableEventWidget::editingFinished, this, &AdminEventBoxLayout::editingFinished);
    QObject::connect(editableWidget, &EditableEventWidget::emptyWidget, this, &AdminEventBoxLayout::emptyWidget);
}

void AdminEventBoxLayout::addEventWidget(UneditableEventWidget *uneditableWidget, EditableEventWidget *editableWidget) {
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
    this->boxLayoutEvents->addLayout(layout);
    /// Добавляем в лист бокс пар виджетов
    this->widgetBoxLayout.append(layout);
}

void AdminEventBoxLayout::deleteEventWidget(UneditableEventWidget *uneditableWidget) {
    /// Проходим по листу боксов пар виджетов и удаляем бокс, который содержит в себе uneditableWidget
    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == uneditableWidget) {
            QLayoutItem* item;
                while ( ( item = layout->takeAt( 0 ) ) != NULL ) {
                    delete item->widget();
                    delete item;
                }
            this->widgetBoxLayout.removeOne(layout);
            this->boxLayoutEvents->removeItem(layout);
            layout->deleteLater();
        }
    }
}

void AdminEventBoxLayout::clearEvents() {
    /// Проходимся по всем layout, которые не NULL и удаляем виджет вместе с итемом
    if(this->boxLayoutEvents->layout() != NULL) {
        QLayoutItem* item;
        while ( ( item = this->boxLayoutEvents->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
    }

}

void AdminEventBoxLayout::showEditableWidget(UneditableEventWidget *uneditableWidget, EditableEventWidget *editableWidget) {
    /// Скрываем не редактируемый виджет
    uneditableWidget->hide();
    /// Показываем редактируемый виджет
    editableWidget->show();
    /// Устанавливаем фокус редактируемому виджету
    editableWidget->setFocus();
}

void AdminEventBoxLayout::showUneditableWidget(EditableEventWidget *editableWidget, UneditableEventWidget *uneditableWidget) {
    /// Скрываем не редактируемый виджет
    editableWidget->hide();
    /// Показываем не редактируемый виджет
    uneditableWidget->show();
}

void AdminEventBoxLayout::unselectUneditableWidget(UneditableEventWidget *uneditableWidget) {
    uneditableWidget->setUnselected();
}

void AdminEventBoxLayout::enableUneditableWidget(UneditableEventWidget *uneditableWidget) {
    uneditableWidget->setEnabled(true);
}

void AdminEventBoxLayout::disableUneditableWidget(UneditableEventWidget *uneditableWidget) {
    uneditableWidget->setEnabled(false);
}
