#include "AdminInScenarioIncludedIncidentBoxLayoutController.h"

AdminInScenarioIncludedIncidentBoxLayoutController::AdminInScenarioIncludedIncidentBoxLayoutController(QObject *parent) : QObject{parent} {}

AdminInScenarioIncludedIncidentBoxLayoutController::~AdminInScenarioIncludedIncidentBoxLayoutController() {
    delete this->boxLayoutIncidents;
}

SecurityIncident AdminInScenarioIncludedIncidentBoxLayoutController::addIncludedIncident(SecurityIncident incident) {
    includedIncidents.append(incident);

    return incident;
}

void AdminInScenarioIncludedIncidentBoxLayoutController::addIncludedIncidentWidget(SecurityIncident incident) {
    InScenarioIncidentWidget *incidentWidget = new InScenarioIncidentWidget(incident.getId(), incident.getText(), incident.getName());

    this->widgetStorage.appendWidget(incidentWidget);
    this->boxLayoutIncidents->addIncidentWidget(incidentWidget);
}

void AdminInScenarioIncludedIncidentBoxLayoutController::deleteIncludedIncident(quint32 incidentID) {

    for(SecurityIncident &incident : includedIncidents) {
        if(incident.getId() == incidentID) {
            includedIncidents.removeOne(incident);
        }
    }

    this->onIncludedIncidentUnselected(incidentID);
}

void AdminInScenarioIncludedIncidentBoxLayoutController::deleteIncludedIncidentWidget(quint32 incidentID) {
    InScenarioIncidentWidget *tempWidget = this->widgetStorage.getIncidentWidget(incidentID);

    this->widgetStorage.removeWidget(incidentID);
    this->boxLayoutIncidents->deleteIncidentWidget(tempWidget);
}

void AdminInScenarioIncludedIncidentBoxLayoutController::renameIncludedIncident(const quint32 incidentID, QString newIncidentTitle) {
    for(SecurityIncident &incident : includedIncidents) {
        if(incident.getId() == incidentID) {


            incident.setText(newIncidentTitle);

            this->widgetStorage.getIncidentWidget(incidentID)->setTitle(newIncidentTitle);
        }
    }
}

void AdminInScenarioIncludedIncidentBoxLayoutController::unselectAllIncludedIncidents() {
    for(SecurityIncident incident : selectedIncludedIncidents) {

        this->boxLayoutIncidents->unselectIncidentWidget(this->widgetStorage.getIncidentWidget(incident.getId()));
    }
}

void AdminInScenarioIncludedIncidentBoxLayoutController::enableAllIncludedIncidents() {
    for(SecurityIncident incident : includedIncidents) {

        this->boxLayoutIncidents->enableIncidentWidget(this->widgetStorage.getIncidentWidget(incident.getId()));
    }
}

void AdminInScenarioIncludedIncidentBoxLayoutController::disableAllIncludedIncidents() {
    for(SecurityIncident incident : includedIncidents) {

        this->boxLayoutIncidents->disableIncidentWidget(this->widgetStorage.getIncidentWidget(incident.getId()));
    }
}

void AdminInScenarioIncludedIncidentBoxLayoutController::onIncludedIncidentSelected(const quint32 incidentID) {

    quint32 incidentsChecked = 0;
    for(SecurityIncident incident : includedIncidents) {
        if(incident.getId() != incidentID)
            incidentsChecked++;
    }

    /*if(eventsChecked == events.size()) {
        throw
    }*/


    incidentsChecked = 0;
    for(SecurityIncident selectedIncludedIncident : selectedIncludedIncidents) {
        if(selectedIncludedIncident.getId() == incidentID)
            incidentsChecked++;
    }

    if(incidentsChecked != 1) {


        for(quint32 i = 0; i < includedIncidents.size(); i++) {
            SecurityIncident incident = this->includedIncidents.at(i);
            if(incident.getId() == incidentID) {
                this->selectedIncludedIncidents.append(incident);

            }
        }
    }

    if(!selectedIncludedIncidents.isEmpty())
        emit signalSelectedIncludedIncidentsNotEmpty();
}

void AdminInScenarioIncludedIncidentBoxLayoutController::onIncludedIncidentUnselected(const quint32 incidentID) {

    quint32 incidentsChecked = 0;
    for(SecurityIncident incident : includedIncidents) {
        if(incident.getId() != incidentID)
            incidentsChecked++;
    }

    /*if(eventsChecked == events.size()) {
        throw
    }*/


    incidentsChecked = 0;
    for(SecurityIncident selectedIncludedIncident : selectedIncludedIncidents) {
        if(selectedIncludedIncident.getId() == incidentID)
            incidentsChecked++;
    }

    if(incidentsChecked != 1) {
        //throw
    }

    else {


        for(quint32 i = 0; i < selectedIncludedIncidents.size(); i++) {
            SecurityIncident selectedIncident = this->selectedIncludedIncidents.at(i);
            if(selectedIncident.getId() == incidentID)
                this->selectedIncludedIncidents.removeOne(selectedIncident);
        }
    }

    if(selectedIncludedIncidents.isEmpty())
        emit signalSelectedIncludedIncidentsEmpty();
}


void AdminInScenarioIncludedIncidentBoxLayoutController::init(QVBoxLayout *editMenuBoxLayoutInScenarioIncidents) {
    this->boxLayoutIncidents = new AdminInScenarioIncidentBoxLayout();
    this->boxLayoutIncidents->init(editMenuBoxLayoutInScenarioIncidents);

    QObject::connect(this->boxLayoutIncidents, &AdminInScenarioIncidentBoxLayout::signalIncidentSelected, this, &AdminInScenarioIncludedIncidentBoxLayoutController::onIncludedIncidentSelected);
    QObject::connect(this->boxLayoutIncidents, &AdminInScenarioIncidentBoxLayout::signalIncidentUnselected, this, &AdminInScenarioIncludedIncidentBoxLayoutController::onIncludedIncidentUnselected);

}

void AdminInScenarioIncludedIncidentBoxLayoutController::setIncludedIncidentList(const QList<SecurityIncident> incidents) {
    this->includedIncidents = incidents;
    this->boxLayoutIncidents->clearIncidents();

    for (SecurityIncident incident : incidents) {

        this->addIncludedIncidentWidget(incident);
    }
}

void AdminInScenarioIncludedIncidentBoxLayoutController::clearIncludedIncidentList(const quint32 scenarioID) {
    emit scenarioIncidentsMustBeSaved(scenarioID, this->includedIncidents);

    this->includedIncidents.clear();

    this->unselectAllIncludedIncidents();
    this->selectedIncludedIncidents.clear();

    this->boxLayoutIncidents->clearIncidents();
    this->widgetStorage.clear();
}

void AdminInScenarioIncludedIncidentBoxLayoutController::slotIncludeFreeIncidentsToScenario(QList<SecurityIncident> freeIncidents) {
    for(SecurityIncident freeIncident : freeIncidents) {

        //if(this->includedEvents.contains(freeEvent) || this->selectedIncludedEvents.contains(freeEvent))
            // throw

        this->slotAddIncludedIncident(freeIncident.getId(), freeIncident.getText(), freeIncident.getName(), freeIncident.getEventIds());
    }
}

void AdminInScenarioIncludedIncidentBoxLayoutController::slotDeleteIncludedIncident(quint32 incidentID) {
    this->deleteIncludedIncidentWidget(incidentID);
    this->deleteIncludedIncident(incidentID);
}

void AdminInScenarioIncludedIncidentBoxLayoutController::slotAddIncludedIncident(quint32 incidentID, QString incidentText, QString incidentTitle, QList<quint32> incidentEvents) {
    SecurityIncident newIncident(incidentID, incidentText, incidentTitle, incidentEvents);

    this->addIncludedIncident(newIncident);
    this->addIncludedIncidentWidget(newIncident);
}

void AdminInScenarioIncludedIncidentBoxLayoutController::slotRemoveSelectedIncidentsFromScenarioButtonPressed() {
    emit incidentsRemovedFromScenario(selectedIncludedIncidents);

    for(SecurityIncident selectedIncludedIncident : selectedIncludedIncidents) {

        this->slotDeleteIncludedIncident(selectedIncludedIncident.getId());
    }
}
