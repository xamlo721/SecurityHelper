#include "UserEventsController.h"

#include "src/ui/SelectedWidget.h"

UserEventsController::UserEventsController(QObject *parent) : QObject{parent} {
    //NO-OP
}

void UserEventsController::init(MainMenuWidget *menuWidget) {
    mainMenuWidget = menuWidget;
    QObject::connect(menuWidget, &MainMenuWidget::signalCategoryClicked, this, &UserEventsController::onCetegorySelected);
    QObject::connect(menuWidget, &MainMenuWidget::signaAvailableEventClicked, this, &UserEventsController::onEventSelected);
    QObject::connect(menuWidget, &MainMenuWidget::signalSelectedEventClicked, this, &UserEventsController::onEventUnselected);
}

void UserEventsController::onDatabaseUpdated(const Database & db) {
    this->categories = db.categories;
    this->allEvents = db.events;

    //Отображение категорий
    this->mainMenuWidget->clearCategories();
    for (SecurityEventCategory cat : categories) {
        SelectedWidget * categoryWidget = new SelectedWidget(cat.getId(), cat.getText());

        this->mainMenuWidget->addCategory(categoryWidget);
    }
}

void UserEventsController::onCetegorySelected(quint32 categoryID) {
    this->availableEvents.clear();
    this->mainMenuWidget->clearAvailableEvents();
    SecurityEventCategory category = categories.value(categoryID);

    QList<SecurityEvent> eventsInCetegory;
    for (quint32 eventID : category.getEventIds()) {

        for (SecurityEvent event : allEvents) {
            if (event.getId() == eventID && !selectedEvents.contains(event)) {
                eventsInCetegory.append(event);
                this->availableEvents.append(event);
            }
        }
    }

    for (SecurityEvent event : eventsInCetegory) {
        this->mainMenuWidget->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }
}

void UserEventsController::onEventSelected(quint32 eventID) {

    ///1) Найти и переложить событие
    this->selectedEvents.append(allEvents.value(eventID));
    this->availableEvents.removeOne(allEvents.value(eventID));

    ///2) Почистить доступные ивенты от него

    //TODO: Вычесть те, которые уже отображены
    this->mainMenuWidget->clearAvailableEvents();
    for (SecurityEvent event : availableEvents) {
        this->mainMenuWidget->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }

    ///3) обновить выбранные ивенты
    this->mainMenuWidget->clearSelectedEvents();
    for (SecurityEvent event : selectedEvents) {
        this->mainMenuWidget->addSelectedEvent(new SelectedWidget(event.getId(), event.getText()));
    }

}

void UserEventsController::onEventUnselected(quint32 eventID) {

    ///1) Найти и переложить событие
    this->selectedEvents.removeOne(allEvents.value(eventID));
    this->availableEvents.append(allEvents.value(eventID));

    ///2) Почистить доступные ивенты от него

    //TODO: Вычесть те, которые уже отображены
    this->mainMenuWidget->clearAvailableEvents();
    for (SecurityEvent event : availableEvents) {
        this->mainMenuWidget->addAvalilableEvent(new SelectedWidget(event.getId(), event.getText()));
    }


    ///3) обновить выбранные ивенты
    this->mainMenuWidget->clearSelectedEvents();
    for (SecurityEvent event : selectedEvents) {
        this->mainMenuWidget->addSelectedEvent(new SelectedWidget(event.getId(), event.getText()));
    }


}

void UserEventsController::resetWidget() {
    this->availableEvents.clear();
    this->selectedEvents.clear();
    this->mainMenuWidget->clearAvailableEvents();
    this->mainMenuWidget->clearSelectedEvents();
}


void UserEventsController::onCalculateIncident() {
    emit signalEventsForIncidentSelected(this->selectedEvents);
}
