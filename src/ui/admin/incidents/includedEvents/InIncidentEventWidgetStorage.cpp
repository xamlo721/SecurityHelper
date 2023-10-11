#include "InIncidentEventWidgetStorage.h"

InIncidentEventWidgetStorage::InIncidentEventWidgetStorage() {}

void InIncidentEventWidgetStorage::sortWidgetNumbers() {
    this->widgetNumbers.clear();

    for(qint32 i = 0; i < eventWidgets.size(); i++)
        this->widgetNumbers.append(i + 1);
}

void InIncidentEventWidgetStorage::appendWidget(SelectedWidget *eventWidget) {
    this->eventWidgets.append(eventWidget);
    this->widgetNumbers.append(this->widgetNumbers.size() + 1);
}

void InIncidentEventWidgetStorage::removeWidget(quint32 widgetID) {
    for(SelectedWidget *eventWidget : eventWidgets) {
        if(eventWidget->getId() == widgetID) {

            quint32 widgetPosition = this->eventWidgets.indexOf(eventWidget);

            this->eventWidgets.removeAt(widgetPosition);
            this->widgetNumbers.removeAt(widgetPosition);

            this->sortWidgetNumbers();
        }
    }
}

void InIncidentEventWidgetStorage::clear() {
    this->eventWidgets.clear();
    this->widgetNumbers.clear();
}

SelectedWidget *InIncidentEventWidgetStorage::getEventWidget(quint32 widgetID) {
    for(SelectedWidget *eventWidget : eventWidgets) {
        if(eventWidget->getId() == widgetID)
            return eventWidget;
    }
    return nullptr;
}
