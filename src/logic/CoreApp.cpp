#include "CoreApp.h"

CoreApp::CoreApp(QObject *parent) : QObject(parent) {

}

void CoreApp::init() {

    //Отправим в UI список категорий
    emit signalOpenCategories(db.categories.values());

}


void CoreApp::onOpenCategory(int categoryId) {

    QList<SecurityEvent> categoryEvents;
    SecurityEventCategory category = db.categories.value(categoryId);
    //Проходимся по списку всех событий в категории
    for (int eventid : category.getEventIds()) {
        if (!db.events.contains(eventid)) {
            //Бросить исключение
            continue;
        }

        categoryEvents.append(db.events.value(eventid));
    }

    emit signalOpenCategory(categoryEvents);

}
