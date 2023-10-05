#include "AdminInCategoryFreeEventBoxLayoutController.h"

AdminInCategoryFreeEventBoxLayoutController::AdminInCategoryFreeEventBoxLayoutController(QObject *parent) : QObject{parent} {}

AdminInCategoryFreeEventBoxLayoutController::~AdminInCategoryFreeEventBoxLayoutController() {
    delete this->boxLayoutEvents;
}

void AdminInCategoryFreeEventBoxLayoutController::addFreeEvent(SecurityEvent event) {
    freeEvents.append(event);

    InCategoryEventWidget *eventWidget = new InCategoryEventWidget(event.getId(), event.getText());

    this->widgetStorage.appendWidget(eventWidget);
    this->boxLayoutEvents->addEventWidget(eventWidget);
}

void AdminInCategoryFreeEventBoxLayoutController::renameFreeEvent(const quint32 eventID, QString newEventTitle) {
    for(SecurityEvent &event : freeEvents) {
        if(event.getId() == eventID) {

            /// Изменяем имя события
            event.setText(newEventTitle);
            /// Изменяем имя виджета этого события
            this->widgetStorage.getEventWidget(eventID)->setTitle(newEventTitle);
        }
    }
}

void AdminInCategoryFreeEventBoxLayoutController::deleteFreeEvent(quint32 eventID) {
    this->boxLayoutEvents->deleteEventWidget(this->widgetStorage.getEventWidget(eventID));

    this->widgetStorage.removeWidget(eventID);

    this->onFreeEventUnselected(eventID);

    for(SecurityEvent &event : freeEvents) {
        if(event.getId() == eventID) {
            freeEvents.removeOne(event);
        }
    }
}

void AdminInCategoryFreeEventBoxLayoutController::unselectAllFreeEvents() {
    for(SecurityEvent event : selectedFreeEvents) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его не выбранным
        InCategoryEventWidget *eventWidget = this->widgetStorage.getEventWidget(event.getId());
        this->boxLayoutEvents->unselectEventWidget(eventWidget);
    }
}

void AdminInCategoryFreeEventBoxLayoutController::enableAllFreeEvents() {
    for(SecurityEvent event : freeEvents) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его доступным
        InCategoryEventWidget *eventWidget = this->widgetStorage.getEventWidget(event.getId());
        this->boxLayoutEvents->enableEventWidget(eventWidget);
    }
}
void AdminInCategoryFreeEventBoxLayoutController::disableAllFreeEvents() {
    for(SecurityEvent event : freeEvents) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его не доступным
        InCategoryEventWidget *eventWidget = this->widgetStorage.getEventWidget(event.getId());
        this->boxLayoutEvents->disableEventWidget(eventWidget);
    }
}

void AdminInCategoryFreeEventBoxLayoutController::onFreeEventSelected(const quint32 eventID) {
    // Проверка, есть ли в списке событий такое событие
    quint32 eventsChecked = 0;
    for(SecurityEvent event : freeEvents) {
        if(event.getId() != eventID)
            eventsChecked++;
    }
    //if(eventsChecked == events.size())
        // throw

    /// Находим и забрасываем событие в список выбранных
    for(quint32 i = 0; i < freeEvents.size(); i++) {
        SecurityEvent event = this->freeEvents.at(i);
        if(event.getId() == eventID) {
            this->selectedFreeEvents.append(event);

        }
    }
    if(!selectedFreeEvents.isEmpty())
        emit signalSelectedFreeEventsNotEmpty();
}

void AdminInCategoryFreeEventBoxLayoutController::onFreeEventUnselected(const quint32 eventID) {
    // Проверка, есть ли в списке событий такое событие
    quint32 eventsChecked = 0;
    for(SecurityEvent event : freeEvents) {
        if(event.getId() != eventID)
            eventsChecked++;
    }
    //if(eventsChecked == events.size())
        // throw

    /// Находим и удаляем событие из списка выбранных событий
    for(quint32 i = 0; i < selectedFreeEvents.size(); i++) {
        SecurityEvent selectedEvent = this->selectedFreeEvents.at(i);
        if(selectedEvent.getId() == eventID)
            this->selectedFreeEvents.removeOne(selectedEvent);
    }
    if(selectedFreeEvents.isEmpty())
        emit signalSelectedFreeEventsEmpty();
}


void AdminInCategoryFreeEventBoxLayoutController::init(QVBoxLayout *editMenuBoxLayoutInCategoryEvents) {
    this->boxLayoutEvents = new AdminInCategoryEventBoxLayout();
    this->boxLayoutEvents->init(editMenuBoxLayoutInCategoryEvents);

    QObject::connect(this->boxLayoutEvents, &AdminInCategoryEventBoxLayout::signalEventSelected, this, &AdminInCategoryFreeEventBoxLayoutController::onFreeEventSelected);
    QObject::connect(this->boxLayoutEvents, &AdminInCategoryEventBoxLayout::signalEventUnselected, this, &AdminInCategoryFreeEventBoxLayoutController::onFreeEventUnselected);

}

void AdminInCategoryFreeEventBoxLayoutController::setFreeEventList(const QList<SecurityEvent> events) {
    this->freeEvents = events;
    this->boxLayoutEvents->clearEvents();

    for (SecurityEvent event : events) {

        InCategoryEventWidget *eventWidget = new InCategoryEventWidget(event.getId(), event.getText());

        this->widgetStorage.appendWidget(eventWidget);
        this->boxLayoutEvents->addEventWidget(eventWidget);
    }
    this->unselectAllFreeEvents();
    this->disableAllFreeEvents();
}

void AdminInCategoryFreeEventBoxLayoutController::clearSelectedFreeEvents() {
    for(SecurityEvent selectedFreeEvent : selectedFreeEvents) {
        this->deleteFreeEvent(selectedFreeEvent.getId());
    }
}

void AdminInCategoryFreeEventBoxLayoutController::slotUnincludeEventsFromCategory(QList<SecurityEvent> includedEvents) {
    for(SecurityEvent includedEvent : includedEvents) {

        //if(this->freeEvents.contains(includedEvent) || this->selectedFreeEvents.contains(includedEvent))
            // throw

        this->addFreeEvent(includedEvent);
    }
}

void AdminInCategoryFreeEventBoxLayoutController::slotAddSelectedEventsToCategoryButtonPressed() {
    emit freeEventsIncludedInCategory(selectedFreeEvents);

    this->clearSelectedFreeEvents();
}
