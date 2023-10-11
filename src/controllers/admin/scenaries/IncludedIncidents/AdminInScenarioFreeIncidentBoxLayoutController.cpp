#include "AdminInScenarioFreeIncidentBoxLayoutController.h"

AdminInScenarioFreeIncidentBoxLayoutController::AdminInScenarioFreeIncidentBoxLayoutController(QObject *parent) : QObject{parent} {}

AdminInScenarioFreeIncidentBoxLayoutController::~AdminInScenarioFreeIncidentBoxLayoutController() {
    delete this->boxLayoutIncidents;
}

SecurityIncident AdminInScenarioFreeIncidentBoxLayoutController::addFreeIncident(SecurityIncident incident) {
    freeIncidents.append(incident);

    return incident;
}

void AdminInScenarioFreeIncidentBoxLayoutController::addFreeIncidentWidget(SecurityIncident incident) {
    SelectedWidget *incidentWidget = new SelectedWidget(incident.getId(), incident.getName()); // incident.getText(),

    this->widgetStorage.appendWidget(incidentWidget);
    this->boxLayoutIncidents->addIncidentWidget(incidentWidget);
}

void AdminInScenarioFreeIncidentBoxLayoutController::addDisabledFreeIncident(SecurityIncident incident) {
    freeIncidents.append(incident);

    SelectedWidget *incidentWidget = new SelectedWidget(incident.getId(),  incident.getName()); //incident.getText(),

    this->widgetStorage.appendWidget(incidentWidget);
    this->boxLayoutIncidents->addIncidentWidget(incidentWidget);

    incidentWidget->setEnabled(false);
}

void AdminInScenarioFreeIncidentBoxLayoutController::deleteFreeIncident(quint32 incidentID) {
    for(SecurityIncident &incident : freeIncidents) {
        if(incident.getId() == incidentID) {
            freeIncidents.removeOne(incident);
        }
    }

    this->onFreeIncidentUnselected(incidentID);
}

void AdminInScenarioFreeIncidentBoxLayoutController::deleteFreeIncidentWidget(quint32 incidentID) {
    SelectedWidget *tempWidget = this->widgetStorage.getIncidentWidget(incidentID);

    this->widgetStorage.removeWidget(incidentID);
    this->boxLayoutIncidents->deleteIncidentWidget(tempWidget);
}

void AdminInScenarioFreeIncidentBoxLayoutController::renameFreeIncident(const quint32 incidentID, QString newIncidentTitle) {
    for(SecurityIncident &incident : freeIncidents) {
        if(incident.getId() == incidentID) {

            incident.setText(newIncidentTitle);

            this->widgetStorage.getIncidentWidget(incidentID)->setText(newIncidentTitle);
        }
    }
}

void AdminInScenarioFreeIncidentBoxLayoutController::unselectAllFreeIncidents() {
    for(SecurityIncident incident : selectedFreeIncidents) {

        this->boxLayoutIncidents->unselectIncidentWidget(this->widgetStorage.getIncidentWidget(incident.getId()));
    }
}

void AdminInScenarioFreeIncidentBoxLayoutController::enableAllFreeIncidents() {
    for(SecurityIncident incident : freeIncidents) {

        this->boxLayoutIncidents->enableIncidentWidget(this->widgetStorage.getIncidentWidget(incident.getId()));
    }
}

void AdminInScenarioFreeIncidentBoxLayoutController::disableAllFreeIncidents() {
    for(SecurityIncident incident : freeIncidents) {

        this->boxLayoutIncidents->disableIncidentWidget(this->widgetStorage.getIncidentWidget(incident.getId()));
    }
}

void AdminInScenarioFreeIncidentBoxLayoutController::onFreeIncidentSelected(const quint32 incidentID) {

    quint32 incidentsChecked = 0;
    for(SecurityIncident incident : freeIncidents) {
        if(incident.getId() != incidentID)
            incidentsChecked++;
    }

    /*if(eventsChecked == events.size()) {
        throw
    }*/


    incidentsChecked = 0;
    for(SecurityIncident selectedFreeIncident : selectedFreeIncidents) {
        if(selectedFreeIncident.getId() == incidentID)
            incidentsChecked++;
    }

    if(incidentsChecked != 1) {


        for(qint32 i = 0; i < freeIncidents.size(); i++) {
            SecurityIncident incident = this->freeIncidents.at(i);
            if(incident.getId() == incidentID) {
                this->selectedFreeIncidents.append(incident);

            }
        }
    }

    //else throw

    if(!selectedFreeIncidents.isEmpty())
        emit signalSelectedFreeIncidentsNotEmpty();
}

void AdminInScenarioFreeIncidentBoxLayoutController::onFreeIncidentUnselected(const quint32 incidentID) {

    quint32 incidentsChecked = 0;
    for(SecurityIncident incident : freeIncidents) {
        if(incident.getId() != incidentID)
            incidentsChecked++;
    }

    //if(eventsChecked == events.size())
        //throw

    incidentsChecked = 0;
    for(SecurityIncident selectedFreeIncident : selectedFreeIncidents) {
        if(selectedFreeIncident.getId() == incidentID)
            incidentsChecked++;
    }

    if(incidentsChecked != 1) {
        //throw
    }

    else {

        for(qint32 i = 0; i < selectedFreeIncidents.size(); i++) {
            SecurityIncident selectedIncident = this->selectedFreeIncidents.at(i);
            if(selectedIncident.getId() == incidentID)
                this->selectedFreeIncidents.removeOne(selectedIncident);
        }
    }

    if(selectedFreeIncidents.isEmpty())
        emit signalSelectedFreeIncidentsEmpty();
}


void AdminInScenarioFreeIncidentBoxLayoutController::init(QVBoxLayout *editMenuBoxLayoutInScenarioIncident) {
    this->boxLayoutIncidents = new AdminInScenarioIncidentBoxLayout();
    this->boxLayoutIncidents->init(editMenuBoxLayoutInScenarioIncident);

    QObject::connect(this->boxLayoutIncidents, &AdminInScenarioIncidentBoxLayout::signalIncidentSelected, this, &AdminInScenarioFreeIncidentBoxLayoutController::onFreeIncidentSelected);
    QObject::connect(this->boxLayoutIncidents, &AdminInScenarioIncidentBoxLayout::signalIncidentUnselected, this, &AdminInScenarioFreeIncidentBoxLayoutController::onFreeIncidentUnselected);

}

void AdminInScenarioFreeIncidentBoxLayoutController::setFreeIncidentList(const QList<SecurityIncident> incidents) {
    this->freeIncidents = incidents;
    this->boxLayoutIncidents->clearIncidents();

    for (SecurityIncident incident : incidents) {

        this->addFreeIncidentWidget(incident);
    }
}

void AdminInScenarioFreeIncidentBoxLayoutController::slotUnincludeIncidentsFromScenario(QList<SecurityIncident> includedIncidents) {
    for(SecurityIncident includedIncident : includedIncidents) {

        //if(this->freeEvents.contains(includedEvent) || this->selectedFreeEvents.contains(includedEvent))
            // throw

        this->slotAddFreeIncident(includedIncident.getId(), includedIncident.getText(), includedIncident.getName(), includedIncident.getEventIds());
    }
}

void AdminInScenarioFreeIncidentBoxLayoutController::slotAddFreeIncident(quint32 incidentID, QString incidentText, QString incidentTitle, QList<quint32> incidentEvents) {
    SecurityIncident newIncident(incidentID, incidentText, incidentTitle, incidentEvents);

    this->addFreeIncident(newIncident);
    this->addFreeIncidentWidget(newIncident);
}

void AdminInScenarioFreeIncidentBoxLayoutController::slotDeleteFreeIncident(quint32 incidentID) {
    this->deleteFreeIncidentWidget(incidentID);
    this->deleteFreeIncident(incidentID);
}

void AdminInScenarioFreeIncidentBoxLayoutController::slotAddSelectedIncidentsToScenarioButtonPressed() {
    emit freeIncidentsIncludedInScenario(selectedFreeIncidents);

    for(SecurityIncident selectedFreeIncident : selectedFreeIncidents) {

        this->slotDeleteFreeIncident(selectedFreeIncident.getId());
    }
}

void AdminInScenarioFreeIncidentBoxLayoutController::clearFreeIncidentList(const quint32 scenarioID) {
    this->freeIncidents.clear();

    this->unselectAllFreeIncidents();
    this->selectedFreeIncidents.clear();

    this->boxLayoutIncidents->clearIncidents();
    this->widgetStorage.clear();
}
