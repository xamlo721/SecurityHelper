#include "IncidentWidgetStorage.h"

IncidentWidgetStorage::IncidentWidgetStorage() {}

void IncidentWidgetStorage::sortWidgetNumbers() {
    this->widgetNumbers.clear();

    for(quint32 i = 0; i < uneditableWidgets.size(); i++)
        this->widgetNumbers.append(i + 1);
}

void IncidentWidgetStorage::appendWidget(UneditableIncidentWidget *uneditableWidget, EditableIncidentWidget *editableWidget) {
    /// Если у виджетов не одинаковое айди, бросаем исключение
    //if(uneditableWidget->getId() != editableWidget->getId())
        // throw

    this->uneditableWidgets.append(uneditableWidget);
    this->editableWidgets.append(editableWidget);
    this->widgetNumbers.append(this->widgetNumbers.size() + 1);
}

void IncidentWidgetStorage::removeWidget(quint32 widgetID) {
    for(UneditableIncidentWidget *uneditableWidget : uneditableWidgets) {
        if(uneditableWidget->getID() == widgetID) {
            quint32 widgetPosition = this->uneditableWidgets.indexOf(uneditableWidget);

            this->uneditableWidgets.removeAt(widgetPosition);
            this->editableWidgets.removeAt(widgetPosition);
            this->widgetNumbers.removeAt(widgetPosition);

            this->sortWidgetNumbers();
        }
    }
}

UneditableIncidentWidget *IncidentWidgetStorage::getUneditableWidget(quint32 widgetID) {
    for(UneditableIncidentWidget *uneditableWidget : uneditableWidgets) {
        if(uneditableWidget->getID() == widgetID)
            return uneditableWidget;
    }
    return nullptr;
}

EditableIncidentWidget *IncidentWidgetStorage::getEditableWidget(quint32 widgetID) {
    for(EditableIncidentWidget *editableWidget : editableWidgets) {
        if(editableWidget->getID() == widgetID)
            return editableWidget;
    }
    return nullptr;
}
