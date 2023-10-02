#include "EventWidgetStorage.h"

EventWidgetStorage::EventWidgetStorage() {}

void EventWidgetStorage::sortWidgetNumbers() {
    this->widgetNumbers.clear();

    for(quint32 i = 0; i < uneditableWidgets.size(); i++)
        this->widgetNumbers.append(i + 1);
}

void EventWidgetStorage::appendWidget(UneditableEventWidget *uneditableWidget, EditableEventWidget *editableWidget) {
    /// Если у виджетов не одинаковое айди, бросаем исключение
    //if(uneditableWidget->getId() != editableWidget->getId())
        // throw

    this->uneditableWidgets.append(uneditableWidget);
    this->editableWidgets.append(editableWidget);
    this->widgetNumbers.append(this->widgetNumbers.size() + 1);
}

void EventWidgetStorage::removeWidget(quint32 widgetID) {
    for(UneditableEventWidget *uneditableWidget : uneditableWidgets) {
        if(uneditableWidget->getID() == widgetID) {
            quint32 widgetPosition = this->uneditableWidgets.indexOf(uneditableWidget);

            this->uneditableWidgets.removeAt(widgetPosition);
            this->editableWidgets.removeAt(widgetPosition);
            this->widgetNumbers.removeAt(widgetPosition);

            this->sortWidgetNumbers();
        }
    }
}

UneditableEventWidget *EventWidgetStorage::getUneditableWidget(quint32 widgetID) {
    for(UneditableEventWidget *uneditableWidget : uneditableWidgets) {
        if(uneditableWidget->getID() == widgetID)
            return uneditableWidget;
    }
    return nullptr;
}

EditableEventWidget *EventWidgetStorage::getEditableWidget(quint32 widgetID) {
    for(EditableEventWidget *editableWidget : editableWidgets) {
        if(editableWidget->getID() == widgetID)
            return editableWidget;
    }
    return nullptr;
}
