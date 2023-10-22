#include "CoreApp.h"


void CoreApp::onEventsSelected(QList<SecurityEvent> selectedEvents) {


    QMap<quint32, SecurityIncident> availableIncidents;


    for (const SecurityEvent event : selectedEvents) {

        for (const SecurityIncident incident : db.incidents) {

            //Если инцидент содержит такой ивент, то добавим его в список доступных
            if (incident.getEventIds().contains(event.getId()) && !availableIncidents.contains(event.getId())) {
                availableIncidents.insert(incident.getId(), incident);
            }

        }

    }

    emit signalIncidentCalculated(availableIncidents.values());
}


void CoreApp::onIncidentSelected(quint32 incidentID) {

    QMap<quint32, SecurityScenario> availableScenaries;

    for (const SecurityScenario scenary : db.scenaries) {

        //Выбираем сценарии, которые содержат такой инцидент
        if (scenary.getIncidents().contains(incidentID) && !availableScenaries.contains(incidentID)) {
            availableScenaries.insert(scenary.getId(), scenary);
        }

    }

    emit signalScenarioCalculated(availableScenaries.values());
}
