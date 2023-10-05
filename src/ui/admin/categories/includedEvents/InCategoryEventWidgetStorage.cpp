#include "InCategoryEventWidgetStorage.h"

InCategoryEventWidgetStorage::InCategoryEventWidgetStorage() {}

void InCategoryEventWidgetStorage::sortWidgetNumbers() {
    this->widgetNumbers.clear();

    for(quint32 i = 0; i < eventWidgets.size(); i++)
        this->widgetNumbers.append(i + 1);
}

void InCategoryEventWidgetStorage::appendWidget(InCategoryEventWidget *eventWidget) {
    this->eventWidgets.append(eventWidget);
    this->widgetNumbers.append(this->widgetNumbers.size() + 1);
}

void InCategoryEventWidgetStorage::removeWidget(quint32 widgetID) {
    for(InCategoryEventWidget *eventWidget : eventWidgets) {
        if(eventWidget->getID() == widgetID) {

            quint32 widgetPosition = this->eventWidgets.indexOf(eventWidget);

            this->eventWidgets.removeAt(widgetPosition);
            this->widgetNumbers.removeAt(widgetPosition);

            this->sortWidgetNumbers();
        }
    }
}

void InCategoryEventWidgetStorage::clear() {
    this->eventWidgets.clear();
    this->widgetNumbers.clear();
}

InCategoryEventWidget *InCategoryEventWidgetStorage::getEventWidget(quint32 widgetID) {
    for(InCategoryEventWidget *eventWidget : eventWidgets) {
        if(eventWidget->getID() == widgetID)
            return eventWidget;
    }
    return nullptr;
}
