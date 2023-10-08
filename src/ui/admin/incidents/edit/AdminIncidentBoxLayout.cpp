#include "AdminIncidentBoxLayout.h"

AdminIncidentBoxLayout::AdminIncidentBoxLayout(QObject *parent) : QObject{parent} {}

void AdminIncidentBoxLayout::init(QVBoxLayout *boxLayout) {
    ///  Инициализация бокса категорий данного класса боксом категорий из
    /// AdminMenuEditWidget, для управления им
    this->boxLayoutIncidents = boxLayout;
}

void AdminIncidentBoxLayout::initUneditableWidget(UneditableIncidentWidget *uneditableWidget) {
    QObject::connect(uneditableWidget, &UneditableIncidentWidget::signalEditIncident, this, &AdminIncidentBoxLayout::signalEditIncident);
    QObject::connect(uneditableWidget, &UneditableIncidentWidget::signalDeleteIncident, this, &AdminIncidentBoxLayout::signalDeleteIncident);

    QObject::connect(uneditableWidget, &UneditableIncidentWidget::signalIncidentSelected, this, &AdminIncidentBoxLayout::signalIncidentSelected);
    QObject::connect(uneditableWidget, &UneditableIncidentWidget::signalIncidentUnselected, this, &AdminIncidentBoxLayout::signalIncidentUnselected);
}

void AdminIncidentBoxLayout::initEditableWidget(EditableIncidentWidget *editableWidget) {
    QObject::connect(editableWidget, &EditableIncidentWidget::editingFinished, this, &AdminIncidentBoxLayout::editingFinished);
}

void AdminIncidentBoxLayout::addIncidentWidget(UneditableIncidentWidget *uneditableWidget, EditableIncidentWidget *editableWidget) {
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
    this->boxLayoutIncidents->addLayout(layout);
    /// Добавляем в лист бокс пар виджетов
    this->widgetBoxLayout.append(layout);
}

void AdminIncidentBoxLayout::deleteIncidentWidget(UneditableIncidentWidget *uneditableWidget) {
    /// Проходим по листу боксов пар виджетов и удаляем бокс, который содержит в себе uneditableWidget
    for(QVBoxLayout *layout : widgetBoxLayout){
        if(layout->itemAt(0)->widget() == uneditableWidget) {
            QLayoutItem* item;
                while ( ( item = layout->takeAt( 0 ) ) != NULL ) {
                    delete item->widget();
                    delete item;
                }
            this->widgetBoxLayout.removeOne(layout);
            this->boxLayoutIncidents->removeItem(layout);
            layout->deleteLater();
        }
    }
}

void AdminIncidentBoxLayout::clearIncidents() {
    /// Проходимся по всем layout, которые не NULL и удаляем виджет вместе с итемом
    if(this->boxLayoutIncidents->layout() != NULL) {
        QLayoutItem* item;
        while ( ( item = this->boxLayoutIncidents->layout()->takeAt( 0 ) ) != NULL ) {
            delete item->widget();
            delete item;
        }
    }

}

void AdminIncidentBoxLayout::showEditableWidget(UneditableIncidentWidget *uneditableWidget, EditableIncidentWidget *editableWidget) {
    /// Скрываем не редактируемый виджет
    uneditableWidget->hide();
    /// Показываем редактируемый виджет
    editableWidget->show();
    /// Устанавливаем фокус редактируемому виджету
    editableWidget->setFocus();
}

void AdminIncidentBoxLayout::showUneditableWidget(EditableIncidentWidget *editableWidget, UneditableIncidentWidget *uneditableWidget) {
    /// Скрываем не редактируемый виджет
    editableWidget->hide();
    /// Показываем не редактируемый виджет
    uneditableWidget->show();
}

void AdminIncidentBoxLayout::unselectUneditableWidget(UneditableIncidentWidget *uneditableWidget) {
    uneditableWidget->setUnselected();
}

void AdminIncidentBoxLayout::enableUneditableWidget(UneditableIncidentWidget *uneditableWidget) {
    uneditableWidget->setEnabled(true);
}

void AdminIncidentBoxLayout::disableUneditableWidget(UneditableIncidentWidget *uneditableWidget) {
    uneditableWidget->setEnabled(false);
}
