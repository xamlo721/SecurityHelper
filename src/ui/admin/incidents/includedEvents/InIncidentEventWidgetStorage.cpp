#include "InIncidentEventWidgetStorage.h"

InIncidentEventWidgetStorage::InIncidentEventWidgetStorage() {}

void InIncidentEventWidgetStorage::sortWidgetNumbers() {
    this->widgetNumbers.clear();

    for(quint32 i = 0; i < eventWidgets.size(); i++)
        this->widgetNumbers.append(i + 1);
}

void InIncidentEventWidgetStorage::appendWidget(InIncidentEventWidget *eventWidget) {
    this->eventWidgets.append(eventWidget);
    this->widgetNumbers.append(this->widgetNumbers.size() + 1);
}

void InIncidentEventWidgetStorage::removeWidget(quint32 widgetID) {
    for(InIncidentEventWidget *eventWidget : eventWidgets) {
        if(eventWidget->getID() == widgetID) {

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

InIncidentEventWidget *InIncidentEventWidgetStorage::getEventWidget(quint32 widgetID) {
    for(InIncidentEventWidget *eventWidget : eventWidgets) {
        if(eventWidget->getID() == widgetID)
            return eventWidget;
    }
    return nullptr;
}
