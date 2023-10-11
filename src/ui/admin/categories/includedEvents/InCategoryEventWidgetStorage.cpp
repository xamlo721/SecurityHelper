#include "InCategoryEventWidgetStorage.h"

InCategoryEventWidgetStorage::InCategoryEventWidgetStorage() {}

void InCategoryEventWidgetStorage::sortWidgetNumbers() {
    this->widgetNumbers.clear();

    for(qint32 i = 0; i < eventWidgets.size(); i++)
        this->widgetNumbers.append(i + 1);
}

void InCategoryEventWidgetStorage::appendWidget(SelectedWidget *eventWidget) {
    this->eventWidgets.append(eventWidget);
    this->widgetNumbers.append(this->widgetNumbers.size() + 1);
}

void InCategoryEventWidgetStorage::removeWidget(quint32 widgetID) {
    for(SelectedWidget *eventWidget : eventWidgets) {
        if(eventWidget->getId() == widgetID) {

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

SelectedWidget *InCategoryEventWidgetStorage::getEventWidget(quint32 widgetID) {
    for(SelectedWidget *eventWidget : eventWidgets) {
        if(eventWidget->getId() == widgetID)
            return eventWidget;
    }
    return nullptr;
}
