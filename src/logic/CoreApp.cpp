#include "CoreApp.h"

CoreApp::CoreApp(QObject *parent) : QObject(parent) {

}

void CoreApp::init() {

    //Отправим в UI список категорий
    emit signalOpenCategories(db.categories.values());

    /// Отправление в UI администратора списка категорий
    emit signalAdminOpenCategories(db.categories.values());
}


void CoreApp::onOpenCategory(quint32 categoryId, bool isForAdminMode) {

    QList<SecurityEvent> categoryEvents;
    SecurityEventCategory category = db.categories.value(categoryId);
    //Проходимся по списку всех событий в категории
    for (quint32 eventid : category.getEventIds()) {
        if (!db.events.contains(eventid)) {
            //Бросить исключение
            continue;
        }
        if (!categoryEvents.contains(db.events.value(eventid))) {

            categoryEvents.append(db.events.value(eventid));

        }
    }

    if(isForAdminMode)
        emit signalOpenAdminCategory(categoryEvents);
    else
        emit signalOpenCategory(categoryEvents);

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

        for (quint32 eventid : category.getEventIds()) {

            if (!db.events.contains(eventid)) {
                //Бросить исключение
                continue;
            }
            /// Если лист свободных событий содержит событие, которое уже лежит в какой-то категории, то удаляем это событие из листа
            if (freeEvents.contains(db.events.value(eventid))) {

                freeEvents.removeOne(db.events.value(eventid));

            }
        }

    }
    emit freeEventsFormed(freeEvents);
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

void CoreApp::onOpenIncident(quint32 id) {

    QList<SecurityScenario> scenaries;
    ///Ищем среди сценариев те, что образуется указанным инцидентом

    for (SecurityScenario sc : this->db.scenaries) {

        if (sc.getIncidents().contains(id)) {

            scenaries.append(sc);

        }

    }


    //TODO: Удалить повторы

    emit signalOpenScenaries(scenaries);
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

