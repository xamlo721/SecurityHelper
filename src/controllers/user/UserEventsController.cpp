#include "UserEventsController.h"

#include "src/ui/SelectedWidget.h"

UserEventsController::UserEventsController(QObject *parent) : QObject{parent} {

}

void UserEventsController::init(MainMenuWidget *menuWidget) {
    mainMenuWidget = menuWidget;
    QObject::connect(menuWidget, &MainMenuWidget::signalCategoryClicked, this, &UserEventsController::onCetegorySelected);
}

void UserEventsController::setCategoryList(QMap< quint32, SecurityEventCategory> categories) {
    this->categories = categories;

    //Отображение категорий
    this->mainMenuWidget->clearCategories();
    for (SecurityEventCategory cat : categories) {
        SelectedWidget * categoryWidget = new SelectedWidget(cat.getId(), cat.getText());
        QObject::connect(categoryWidget, &SelectedWidget::signalSelected, this, &UserEventsController::onCetegorySelected);

        this->mainMenuWidget->addCategory(categoryWidget);
    }
}

void UserEventsController::setEventList(QMap< quint32, SecurityEvent> events) {
    this->allEvents = events;

    //TODO: Вычесть те, которые уже отображены
    /**
    this->mainMenuWidget->clearAvailableEvents();

    for (SecurityEvent event : events) {
        SelectedWidget * eventWidget = new SelectedWidget(event.getId(), event.getText(), false);
        QObject::connect(eventWidget, &SelectedWidget::signalSelected, this, &UserEventsController::onEventSelected);

        this->mainMenuWidget->addEvent(eventWidget);
    } */

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
        this->mainMenuWidget->addEvent(new SelectedWidget(event.getId(), event.getText()));
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
        this->mainMenuWidget->addEvent(new SelectedWidget(event.getId(), event.getText()));
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
        this->mainMenuWidget->addEvent(new SelectedWidget(event.getId(), event.getText()));
    }


    ///3) обновить выбранные ивенты
    this->mainMenuWidget->clearSelectedEvents();
    for (SecurityEvent event : selectedEvents) {
        this->mainMenuWidget->addSelectedEvent(new SelectedWidget(event.getId(), event.getText()));
    }


}

void UserEventsController::onCalculateIncident() {
    emit signalCalculateIncident(selectedEvents);
}

void UserEventsController::clearWidget() {
    this->availableEvents.clear();
    this->selectedEvents.clear();
    this->mainMenuWidget->clearAvailableEvents();
    this->mainMenuWidget->clearSelectedEvents();
}
