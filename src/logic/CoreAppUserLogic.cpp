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
