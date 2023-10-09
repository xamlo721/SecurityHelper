#include "InScenarioIncidentWidgetStorage.h"

InScenarioIncidentWidgetStorage::InScenarioIncidentWidgetStorage() {}

void InScenarioIncidentWidgetStorage::sortWidgetNumbers() {
    this->widgetNumbers.clear();

    for(quint32 i = 0; i < incidentWidgets.size(); i++)
        this->widgetNumbers.append(i + 1);
}

void InScenarioIncidentWidgetStorage::appendWidget(InScenarioIncidentWidget *incidentWidget) {
    this->incidentWidgets.append(incidentWidget);
    this->widgetNumbers.append(this->widgetNumbers.size() + 1);
}

void InScenarioIncidentWidgetStorage::removeWidget(quint32 widgetID) {
    for(InScenarioIncidentWidget *incidentWidget : incidentWidgets) {
        if(incidentWidget->getID() == widgetID) {

            quint32 widgetPosition = this->incidentWidgets.indexOf(incidentWidget);

            this->incidentWidgets.removeAt(widgetPosition);
            this->widgetNumbers.removeAt(widgetPosition);

            this->sortWidgetNumbers();
        }
    }
}

void InScenarioIncidentWidgetStorage::clear() {
    this->incidentWidgets.clear();
    this->widgetNumbers.clear();
}

InScenarioIncidentWidget *InScenarioIncidentWidgetStorage::getIncidentWidget(quint32 widgetID) {
    for(InScenarioIncidentWidget *incidentWidget : incidentWidgets) {
        if(incidentWidget->getID() == widgetID)
            return incidentWidget;
    }
    return nullptr;
}
