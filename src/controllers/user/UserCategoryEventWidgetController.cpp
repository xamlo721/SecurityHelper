#include "UserCategoryEventWidgetController.h"

#include "src/ui/SelectedWidget.h"

UserCategoryEventWidgetController::UserCategoryEventWidgetController(QObject *parent) : QObject{parent} {

}

void UserCategoryEventWidgetController::init(MainMenuWidget *menuWidget) {
    mainMenuWidget = menuWidget;
}

void UserCategoryEventWidgetController::setCategoryList(QList<SecurityEventCategory> categories) {
    this->categories = categories;
    this->mainMenuWidget->clearCategories();
    for (SecurityEventCategory cat : categories) {
        SelectedWidget * categoryWidget = new SelectedWidget(cat.getId(), cat.getText());
        QObject::connect(categoryWidget, &SelectedWidget::signalSelected, this, &UserCategoryEventWidgetController::signalOpenCategory);

        this->mainMenuWidget->addCategory(categoryWidget);
    }
}

void UserCategoryEventWidgetController::setEventList(QList<SecurityEvent> events) {
    this->availableEvents = events;

    //TODO: Вычесть те, которые уже отображены
    this->mainMenuWidget->clearAvailableEvents();

    for (SecurityEvent event : events) {
        SelectedWidget * eventWidget = new SelectedWidget(event.getId(), event.getText(), false);
        QObject::connect(eventWidget, &SelectedWidget::signalSelected, this, &UserCategoryEventWidgetController::onEventSelected);

        this->mainMenuWidget->addEvent(eventWidget);
    }

}

void UserCategoryEventWidgetController::onEventSelected(quint32 eventID) {

    ///1) Найти и переложить событие

    //TODO: Проверка, что он его вообще содержит!
    for (quint32 i = 0; i < availableEvents.size(); i++) {
        SecurityEvent event = availableEvents.at(i);
        if (event.getId() == eventID) {
            this->activeEvents.append(availableEvents.takeAt(i));
        }
    }

    ///2) Почистить доступные ивенты от него

    //TODO: Вычесть те, которые уже отображены
    this->mainMenuWidget->clearAvailableEvents();
    for (SecurityEvent event : availableEvents) {
        SelectedWidget * eventWidget = new SelectedWidget(event.getId(), event.getText(), false);
        QObject::connect(eventWidget, &SelectedWidget::signalSelected, this, &UserCategoryEventWidgetController::onEventSelected);
        this->mainMenuWidget->addEvent(eventWidget);
    }

    ///3) обновить выбранные ивенты
    this->mainMenuWidget->clearSelectedEvents();
    for (SecurityEvent event : activeEvents) {
        SelectedWidget * eventWidget = new SelectedWidget(event.getId(), event.getText(), true);
        QObject::connect(eventWidget, &SelectedWidget::signalSelected, this, &UserCategoryEventWidgetController::onEventUnselected);
        this->mainMenuWidget->addSelectedEvent(eventWidget);
    }


}

void UserCategoryEventWidgetController::onEventUnselected(quint32 eventID) {

    ///1) Найти и переложить событие

    //TODO: Проверка, что он его вообще содержит!
    for (quint32 i = 0; i < activeEvents.size(); i++) {
        SecurityEvent event = activeEvents.at(i);
        if (event.getId() == eventID) {
            this->availableEvents.append(activeEvents.takeAt(i));
        }
    }


    ///2) Почистить доступные ивенты от него

    //TODO: Вычесть те, которые уже отображены
    this->mainMenuWidget->clearAvailableEvents();
    for (SecurityEvent event : availableEvents) {
        SelectedWidget * eventWidget = new SelectedWidget(event.getId(), event.getText(), false);
        QObject::connect(eventWidget, &SelectedWidget::signalSelected, this, &UserCategoryEventWidgetController::onEventSelected);
        this->mainMenuWidget->addEvent(eventWidget);
    }


    ///3) обновить выбранные ивенты
    this->mainMenuWidget->clearSelectedEvents();
    for (SecurityEvent event : activeEvents) {
        SelectedWidget * eventWidget = new SelectedWidget(event.getId(), event.getText(), true);
        QObject::connect(eventWidget, &SelectedWidget::signalSelected, this, &UserCategoryEventWidgetController::onEventUnselected);
        this->mainMenuWidget->addSelectedEvent(eventWidget);
    }


}

void UserCategoryEventWidgetController::onCalculateIncident() {
    emit signalCalculateIncident(activeEvents);
}

void UserCategoryEventWidgetController::clearWidget() {
    this->availableEvents.clear();
    this->activeEvents.clear();
    this->mainMenuWidget->clearAvailableEvents();
    this->mainMenuWidget->clearSelectedEvents();
}
