#include "CoreApp.h"

CoreApp::CoreApp(QObject *parent) : QObject(parent) {

}

void CoreApp::init() {

}


void CoreApp::loadDatabase() {
    this->db = XMLHelper::readDatabase("../SecurityHelper/storage/"); //TODO: Унести в константы
    emit signalDatabaseUpdated(this->db);
}

void CoreApp::saveDatabase() {
    //TODO:
}


void CoreApp::addCategory() {

    quint32 newCategoryID = 0;//FIXME

    QList<quint32> events;
    SecurityEventCategory category(newCategoryID, "", events);

    this->db.categories.insert(newCategoryID, category);
    emit signalDatabaseUpdated(this->db);
}


void CoreApp::addEvent() {

    quint32 newEventID = 0;//FIXME

    SecurityEvent event(newEventID, "");

    this->db.events.insert(newEventID, event);
    emit signalDatabaseUpdated(this->db);

}


void CoreApp::addIncident() {

    quint32 newIncidentID = 0;//FIXME

    QList<quint32> events;
    SecurityIncident incident(newIncidentID, "", "", events);

    this->db.incidents.insert(newIncidentID, incident);
    emit signalDatabaseUpdated(this->db);

}


void CoreApp::addScenario() {

    quint32 newScenarioID = 0;//FIXME

    QList<quint32> incidents;
    SecurityScenario scenario(newScenarioID, "", "", incidents);

    this->db.scenaries.insert(newScenarioID, scenario);
    emit signalDatabaseUpdated(this->db);

}


void CoreApp::addRecommendations() {

    quint32 newRecommendationID = 0;//FIXME

    QList<quint32> scenaries;
    SecurityRecommendations recommendation(newRecommendationID, "", "", "", "", scenaries);

    this->db.recommendations.insert(newRecommendationID, recommendation);
    emit signalDatabaseUpdated(this->db);

}



void CoreApp::removeCategory(quint32 categoryID) {
    this->db.categories.remove(categoryID);
    emit signalDatabaseUpdated(this->db);
}


void CoreApp::removeEvent(quint32 eventID) {

    //Удалить событие из категорий, если оно там есть
    for (SecurityEventCategory category : this->db.categories.values()) {

        if (category.getEventIds().contains(eventID)) {
            QList<quint32> containedEvents = category.getEventIds();
            containedEvents.removeOne(eventID);
            category.setIDEvents(containedEvents);
        }

    }

    //Удалить событие из инцидентов, если оно там есть
    for (SecurityIncident incident : this->db.incidents.values()) {

        if (incident.getEventIds().contains(eventID)) {
            QList<quint32> containedEvents = incident.getEventIds();
            containedEvents.removeOne(eventID);
            incident.setIDEvents(containedEvents);
        }

    }


    this->db.events.remove(eventID);
    emit signalDatabaseUpdated(this->db);

}


void CoreApp::removeIncident(quint32 incidentID) {
    //Удалить инцидент из сценариев, если оно там есть
    for (SecurityScenario scenary : this->db.scenaries.values()) {

        if (scenary.getIncidents().contains(incidentID)) {
            QList<quint32> containedIncident = scenary.getIncidents();
            containedIncident.removeOne(incidentID);
            scenary.setIncidents(containedIncident);
        }

    }


    this->db.incidents.remove(incidentID);
    emit signalDatabaseUpdated(this->db);
}


void CoreApp::removeScenario(quint32 scenarioID) {
    //Удалить сценарий из рекомендаций, если оно там есть
    for (SecurityRecommendations recommendation : this->db.recommendations.values()) {

        if (recommendation.getScenaries().contains(scenarioID)) {
            QList<quint32> containedIncident = recommendation.getScenaries();
            containedIncident.removeOne(scenarioID);
            recommendation.setScenaries(containedIncident);
        }

    }

    this->db.scenaries.remove(scenarioID);
    emit signalDatabaseUpdated(this->db);
}


void CoreApp::removeRecommendations(quint32 recommendationID) {
    this->db.recommendations.remove(recommendationID);
    emit signalDatabaseUpdated(this->db);
}



void CoreApp::updateCategory(quint32 categoryID,SecurityEventCategory category) {
    this->db.categories.insert(categoryID, category);
    emit signalDatabaseUpdated(this->db);

}


void CoreApp::updateEvent(quint32 eventID, SecurityEvent event) {
    this->db.events.insert(eventID, event);
    emit signalDatabaseUpdated(this->db);

}


void CoreApp::updateIncident(quint32 incidentID, SecurityIncident incident) {
    this->db.incidents.insert(incidentID, incident);
    emit signalDatabaseUpdated(this->db);

}


void CoreApp::updateScenario(quint32 scenarioID, SecurityScenario scenarion) {
    this->db.scenaries.insert(scenarioID, scenarion);
    emit signalDatabaseUpdated(this->db);

}


void CoreApp::updateRecommendations(quint32 recommendationID, SecurityRecommendations recommendation) {
    this->db.recommendations.insert(recommendationID, recommendation);
    emit signalDatabaseUpdated(this->db);

}
