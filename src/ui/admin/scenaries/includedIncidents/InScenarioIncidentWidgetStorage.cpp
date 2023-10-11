#include "InScenarioIncidentWidgetStorage.h"

InScenarioIncidentWidgetStorage::InScenarioIncidentWidgetStorage() {}

void InScenarioIncidentWidgetStorage::sortWidgetNumbers() {
    this->widgetNumbers.clear();

    for(qint32 i = 0; i < incidentWidgets.size(); i++)
        this->widgetNumbers.append(i + 1);
}

void InScenarioIncidentWidgetStorage::appendWidget(SelectedWidget *incidentWidget) {
    this->incidentWidgets.append(incidentWidget);
    this->widgetNumbers.append(this->widgetNumbers.size() + 1);
}

void InScenarioIncidentWidgetStorage::removeWidget(quint32 widgetID) {
    for(SelectedWidget *incidentWidget : incidentWidgets) {
        if(incidentWidget->getId() == widgetID) {

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

SelectedWidget *InScenarioIncidentWidgetStorage::getIncidentWidget(quint32 widgetID) {
    for(SelectedWidget *incidentWidget : incidentWidgets) {
        if(incidentWidget->getId() == widgetID)
            return incidentWidget;
    }
    return nullptr;
}
