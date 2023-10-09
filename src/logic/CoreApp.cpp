#include "CoreApp.h"

CoreApp::CoreApp(QObject *parent) : QObject(parent) {

}

void CoreApp::init() {

    //Отправим в UI список категорий
    emit signalOpenCategories(db.categories.values());

    /// Отправление в UI администратора списка категорий
    emit signalAdminOpenCategories(db.categories.values());
}

QList<SecurityEventCategory> CoreApp::categoriesToList(QMap<quint32, SecurityEventCategory> qMapCategories) {
    QList<SecurityEventCategory> qListCategories;
    for(quint32 i = 0; i < qMapCategories.size(); i++ ) {
        qListCategories.append(qMapCategories[i]);
    }
    return qListCategories;
}

QList<SecurityIncident> CoreApp::incidentsToList(QMap<quint32, SecurityIncident> qMapIncidents) {
    QList<SecurityIncident> qListIncidents;
    for(quint32 i = 0; i < qMapIncidents.size(); i++ ) {
        qListIncidents.append(qMapIncidents[i]);
    }
    return qListIncidents;
}

QList<SecurityEvent> CoreApp::eventToList(QMap<quint32, SecurityEvent> qMapEvents) {
    QList<SecurityEvent> qListEvents;
    for(quint32 i = 0; i < qMapEvents.size(); i++ ) {
        qListEvents.append(qMapEvents[i]);
    }
    return qListEvents;
}

void CoreApp::acceptCategoriesForSaving(const QList<SecurityEventCategory> categories) {
    categoriesSaved = categories;
}

void CoreApp::acceptIncidentsForSaving(const QList<SecurityIncident> incidents) {
    incidentsSaved = incidents;
}

void CoreApp::acceptEventCategoryForSaving(const quint32 categoryID, QList<SecurityEvent> categoryEvents) {
    QList<quint32> events;
    for(SecurityEvent securityEvent : categoryEvents) {
        events.append(securityEvent.getId());
    }
    categoriesSaved[categoryID].setIDEvents(events);
    QMap<quint32, SecurityEventCategory> readyToSaveCategories;
    for(SecurityEventCategory category : categoriesSaved) {
        readyToSaveCategories.insert(category.getId(), category);
    }
    XMLHelper::writeDatabaseCategory("../SecurityHelper/storage/", readyToSaveCategories);
}
void CoreApp::acceptEventIncidentsForSaving(const quint32 incidentID, QList<SecurityEvent> incidentEvents) {
    QList<quint32> events;
    for(SecurityEvent securityEvent : incidentEvents) {
        events.append(securityEvent.getId());
    }
    incidentsSaved[incidentID].setIDEvents(events);
    QMap<quint32, SecurityIncident> readyToSaveIncident;
    for(SecurityIncident incident : incidentsSaved) {
        readyToSaveIncident.insert(incident.getId(), incident);
    }
    XMLHelper::writeDatabaseIncidents("../SecurityHelper/storage/", readyToSaveIncident);
}

void CoreApp::acceptEventForSaving(QList<SecurityEvent> events) {
    QMap<quint32, SecurityEvent> readyToSaveEvents;
    for(SecurityEvent event : events) {
        readyToSaveEvents.insert(event.getId(), event);
    }
    XMLHelper::writeDatabaseEvent("../SecurityHelper/storage/", readyToSaveEvents);
}

void CoreApp::onOpenCategory(quint32 categoryId, bool isForAdminMode) {

    QList<SecurityEvent> categoryEvents;
    SecurityEventCategory category = db.categories.value(categoryId);
    //Проходимся по списку всех событий в категории
    for (quint32 eventID : category.getEventIds()) {
        if (!db.events.contains(eventID)) {
            //Бросить исключение
            continue;
        }
        if (!categoryEvents.contains(db.events.value(eventID))) {

            categoryEvents.append(db.events.value(eventID));

        }
    }

    if(isForAdminMode)
        emit signalOpenAdminCategory(categoryEvents);
    else
        XMLHelper::writeDatabase("../SecurityHelper/storage/new/");
        emit signalOpenCategory(categoryEvents);

}

void CoreApp::onOpenDeletedCategory(const quint32 categoryId) {

    QList<SecurityEvent> categoryEvents;
    SecurityEventCategory category = db.categories.value(categoryId);
    //Проходимся по списку всех событий в категории
    for (quint32 eventID : category.getEventIds()) {
        if (!db.events.contains(eventID)) {
            //Бросить исключение
            continue;
        }
        if (!categoryEvents.contains(db.events.value(eventID))) {

            categoryEvents.append(db.events.value(eventID));

        }
    }

    emit signalOpenAdminDeletedCategory(categoryEvents);
}

void CoreApp::formEvents() {
    /// Берем из базы данных события
    QList<SecurityEvent> events = db.events.values();
    /// Составляем лист свободных событий для вкладки Категории событий и отправляем их в неё
    this->formFreeEvents();
    /// Отправляем сигнал с событиями во вкладку События
    emit eventsFormed(events);
}

void CoreApp::formFreeEvents() {
    QList<SecurityEvent> freeEvents = db.events.values();

    QList<SecurityEventCategory> categories = db.categories.values();

    for(auto category : categories) {

        for (quint32 eventID : category.getEventIds()) {

            if (!db.events.contains(eventID)) {
                //Бросить исключение
                continue;
            }
            /// Если лист свободных событий содержит событие, которое уже лежит в какой-то категории, то удаляем это событие из листа
            if (freeEvents.contains(db.events.value(eventID))) {

                freeEvents.removeOne(db.events.value(eventID));

            }
        }

    }

    emit freeEventsFormed(freeEvents);
}

void CoreApp::formFreeEventsForIncident(const quint32 incidentID) {
    QList<SecurityEvent> freeEvents = db.events.values();

    SecurityIncident incident = db.incidents.value(incidentID);

    for (SecurityEvent event : this->db.events.values()) {

        if (!db.events.contains(event.getId())) {
            //Бросить исключение
            continue;
        }

        if (incident.getEventIds().contains(event.getId()))

            freeEvents.removeOne(db.events.value(event.getId()));

    }

    emit freeEventsForIncidentFormed(freeEvents);
}

void CoreApp::formIncidents() {

    QList<SecurityIncident> incidents = db.incidents.values();

    this->formFreeIncidents();

    emit incidentsFormed(incidents);
}

void CoreApp::formFreeIncidents() {
    QList<SecurityIncident> freeIncidents = db.incidents.values();

    QList<SecurityScenario> scenaries = db.scenaries.values();

    for(auto scenario : scenaries) {

        for (quint32 incidentID : scenario.getIncidents()) {

            if (!db.events.contains(incidentID)) {
                //Бросить исключение
                continue;
            }
            /// Если лист свободных событий содержит событие, которое уже лежит в какой-то категории, то удаляем это событие из листа
            if (freeIncidents.contains(db.incidents.value(incidentID))) {

                freeIncidents.removeOne(db.incidents.value(incidentID));

            }
        }

    }
    emit freeIncidentsFormed(freeIncidents);
}

void CoreApp::onCalculateIncident(QList<SecurityEvent> selectedEvents) {

    QList<SecurityIncident> incidents;
    ///Ищем среди инцидентов те, что образуются указанными событиями
    for (SecurityEvent event : selectedEvents) {

        for (SecurityIncident inc : this->db.incidents) {

            if (inc.getEventIds().contains(event.getId())) {

                incidents.append(inc);

            }

        }

    }

    //TODO: Удалить повторы

    emit signalOpenIncidents(incidents);
}

void CoreApp::onOpenIncident(quint32 incidentID) {

    QList<SecurityScenario> scenaries;
    ///Ищем среди сценариев те, что образуется указанным инцидентом

    for (SecurityScenario sc : this->db.scenaries) {

        if (sc.getIncidents().contains(incidentID)) {

            scenaries.append(sc);

        }

    }


    //TODO: Удалить повторы

    emit signalOpenScenaries(scenaries);
}

void CoreApp::onOpenAdminIncident(quint32 incidentID) {

    QList<SecurityEvent> incidentEvents;
    SecurityIncident incident = db.incidents.value(incidentID);

    for (quint32 eventID : incident.getEventIds()) {
        if (!db.events.contains(eventID)) {
            //Бросить исключение
            continue;
        }
        if (!incidentEvents.contains(db.events.value(eventID))) {

            incidentEvents.append(db.events.value(eventID));

        }
    }

    emit signalOpenAdminIncident(incidentEvents);

    this->formFreeEventsForIncident(incidentID);
}

void CoreApp::onOpenScenario(quint32 id) {

    QList<SecurityRecommendations> recoms;
    ///Ищем среди рекомендаций те, что образуется указанным инцидентом

    for (SecurityRecommendations rec : this->db.recommendations) {

        if (rec.getScenaries().contains(id)) {

            recoms.append(rec);

        }

    }

    //TODO: Удалить повторы

    emit signalOpenRecommandations(recoms);
}

