#include "CoreApp.h"

CoreApp::CoreApp(QObject *parent) : QObject(parent) {

}

void CoreApp::init() {

    //Отправим в UI список категорий
    emit signalOpenCategories(db.categories.values());

    /// Отправление в UI администратора списка категорий
    emit signalAdminOpenCategories(db.categories.values());
}


void CoreApp::onOpenCategory(quint32 categoryId) {

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

    emit signalOpenCategory(categoryEvents);

}
#include <QDebug>
void CoreApp::formEvents() {

    QList<SecurityEvent> events;
    QList<SecurityEventCategory> categories = db.categories.values();
    qDebug() << "начало ";
    for(auto category : categories) {
        qDebug() << category.getText();
    }
    qDebug() << "конец ";

    for(auto category : categories) {
        for (quint32 eventid : category.getEventIds()) {
            if (!db.events.contains(eventid)) {
                //Бросить исключение
                continue;
            }
            if (!events.contains(db.events.value(eventid))) {

                events.append(db.events.value(eventid));

            }
        }
    }
    emit eventsFormed(events);

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

