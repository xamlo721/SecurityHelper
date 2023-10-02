#include "EventCategoryWidgetStorage.h"

EventCategoryWidgetStorage::EventCategoryWidgetStorage(QObject *parent) : QObject{parent} {

}

void EventCategoryWidgetStorage::sortWidgetNumbers() {
    this->widgetNumbers.clear();

    for(quint32 i = 0; i < uneditableWidgets.size(); i++)
        this->widgetNumbers.append(i + 1);
}

void EventCategoryWidgetStorage::appendWidget(UneditableEventCategoryWidget *uneditableWidget, EditableEventCategoryWidget *editableWidget) {
    /// Если у виджетов не одинаковое айди, бросаем исключение
    //if(uneditableWidget->getId() != editableWidget->getId())
        // throw

    this->uneditableWidgets.append(uneditableWidget);
    this->editableWidgets.append(editableWidget);
    this->widgetNumbers.append(this->widgetNumbers.size() + 1);
}

void EventCategoryWidgetStorage::removeWidget(quint32 widgetID) {
    for(UneditableEventCategoryWidget *uneditableWidget : uneditableWidgets) {
        if(uneditableWidget->getID() == widgetID) {
            quint32 widgetPosition = this->uneditableWidgets.indexOf(uneditableWidget);

            this->uneditableWidgets.removeAt(widgetPosition);
            this->editableWidgets.removeAt(widgetPosition);
            this->widgetNumbers.removeAt(widgetPosition);

            this->sortWidgetNumbers();
        }
    }
}

UneditableEventCategoryWidget *EventCategoryWidgetStorage::getUneditableWidget(quint32 widgetID) {
    for(UneditableEventCategoryWidget *uneditableWidget : uneditableWidgets) {
        if(uneditableWidget->getID() == widgetID)
            return uneditableWidget;
    }
    return nullptr;
}

EditableEventCategoryWidget *EventCategoryWidgetStorage::getEditableWidget(quint32 widgetID) {
    for(EditableEventCategoryWidget *editableWidget : editableWidgets) {
        if(editableWidget->getID() == widgetID)
            return editableWidget;
    }
    return nullptr;
}
