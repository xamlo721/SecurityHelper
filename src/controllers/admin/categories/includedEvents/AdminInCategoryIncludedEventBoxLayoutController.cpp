#include "AdminInCategoryIncludedEventBoxLayoutController.h"

AdminInCategoryIncludedEventBoxLayoutController::AdminInCategoryIncludedEventBoxLayoutController(QObject *parent) : QObject{parent} {}

AdminInCategoryIncludedEventBoxLayoutController::~AdminInCategoryIncludedEventBoxLayoutController() {
    delete this->boxLayoutEvents;
}

SecurityEvent AdminInCategoryIncludedEventBoxLayoutController::addIncludedEvent(SecurityEvent event) {
    includedEvents.append(event);

    return event;
}

void AdminInCategoryIncludedEventBoxLayoutController::addIncludedEventWidget(SecurityEvent event) {
    InCategoryEventWidget *eventWidget = new InCategoryEventWidget(event.getId(), event.getText());

    this->widgetStorage.appendWidget(eventWidget);
    this->boxLayoutEvents->addEventWidget(eventWidget);
}

void AdminInCategoryIncludedEventBoxLayoutController::deleteIncludedEvent(quint32 eventID) {

    for(SecurityEvent &event : includedEvents) {
        if(event.getId() == eventID) {
            includedEvents.removeOne(event);
        }
    }

    this->onIncludedEventUnselected(eventID);
}

void AdminInCategoryIncludedEventBoxLayoutController::deleteIncludedEventWidget(quint32 eventID) {
    InCategoryEventWidget *tempWidget = this->widgetStorage.getEventWidget(eventID);

    this->widgetStorage.removeWidget(eventID);
    this->boxLayoutEvents->deleteEventWidget(tempWidget);
}

void AdminInCategoryIncludedEventBoxLayoutController::renameIncludedEvent(const quint32 eventID, QString newEventTitle) {
    for(SecurityEvent &event : includedEvents) {
        if(event.getId() == eventID) {

            /// Изменяем имя события
            event.setText(newEventTitle);
            /// Изменяем имя виджета этого события
            this->widgetStorage.getEventWidget(eventID)->setTitle(newEventTitle);
        }
    }
}

void AdminInCategoryIncludedEventBoxLayoutController::unselectAllIncludedEvents() {
    for(SecurityEvent event : selectedIncludedEvents) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его не выбранным
        this->boxLayoutEvents->unselectEventWidget(this->widgetStorage.getEventWidget(event.getId()));
    }
}

void AdminInCategoryIncludedEventBoxLayoutController::enableAllIncludedEvents() {
    for(SecurityEvent event : includedEvents) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его доступным
        this->boxLayoutEvents->enableEventWidget(this->widgetStorage.getEventWidget(event.getId()));
    }
}

void AdminInCategoryIncludedEventBoxLayoutController::disableAllIncludedEvents() {
    for(SecurityEvent event : includedEvents) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его не доступным
        this->boxLayoutEvents->disableEventWidget(this->widgetStorage.getEventWidget(event.getId()));
    }
}

void AdminInCategoryIncludedEventBoxLayoutController::onIncludedEventSelected(const quint32 eventID) {
    // Проверка, есть ли в списке событий такое событие
    quint32 eventsChecked = 0;
    for(SecurityEvent event : includedEvents) {
        if(event.getId() != eventID)
            eventsChecked++;
    }

    /*if(eventsChecked == events.size()) {
        throw
    }*/


    eventsChecked = 0;
    for(SecurityEvent selectedIncludedEvent : selectedIncludedEvents) {
        if(selectedIncludedEvent.getId() == eventID)
            eventsChecked++;
    }

    if(eventsChecked != 1) {

        /// Находим и забрасываем событие в список выбранных
        for(quint32 i = 0; i < includedEvents.size(); i++) {
            SecurityEvent event = this->includedEvents.at(i);
            if(event.getId() == eventID) {
                this->selectedIncludedEvents.append(event);

            }
        }
    }

    if(!selectedIncludedEvents.isEmpty())
        emit signalSelectedIncludedEventsNotEmpty();
}

void AdminInCategoryIncludedEventBoxLayoutController::onIncludedEventUnselected(const quint32 eventID) {
    // Проверка, есть ли в списке событий такое событие
    quint32 eventsChecked = 0;
    for(SecurityEvent event : includedEvents) {
        if(event.getId() != eventID)
            eventsChecked++;
    }

    /*if(eventsChecked == events.size()) {
        throw
    }*/


    eventsChecked = 0;
    for(SecurityEvent selectedIncludedEvent : selectedIncludedEvents) {
        if(selectedIncludedEvent.getId() == eventID)
            eventsChecked++;
    }

    if(eventsChecked != 1) {
        //throw
    }

    else {

        /// Находим и удаляем событие из списка выбранных событий
        for(quint32 i = 0; i < selectedIncludedEvents.size(); i++) {
            SecurityEvent selectedEvent = this->selectedIncludedEvents.at(i);
            if(selectedEvent.getId() == eventID)
                this->selectedIncludedEvents.removeOne(selectedEvent);
        }
    }

    if(selectedIncludedEvents.isEmpty())
        emit signalSelectedIncludedEventsEmpty();
}


void AdminInCategoryIncludedEventBoxLayoutController::init(QVBoxLayout *editMenuBoxLayoutInCategoryEvents) {
    this->boxLayoutEvents = new AdminInCategoryEventBoxLayout();
    this->boxLayoutEvents->init(editMenuBoxLayoutInCategoryEvents);

    QObject::connect(this->boxLayoutEvents, &AdminInCategoryEventBoxLayout::signalEventSelected, this, &AdminInCategoryIncludedEventBoxLayoutController::onIncludedEventSelected);
    QObject::connect(this->boxLayoutEvents, &AdminInCategoryEventBoxLayout::signalEventUnselected, this, &AdminInCategoryIncludedEventBoxLayoutController::onIncludedEventUnselected);

}

void AdminInCategoryIncludedEventBoxLayoutController::setIncludedEventList(const QList<SecurityEvent> events) {
    this->includedEvents = events;
    this->boxLayoutEvents->clearEvents();

    for (SecurityEvent event : events) {

        this->addIncludedEventWidget(event);
    }
}

void AdminInCategoryIncludedEventBoxLayoutController::clearIncludedEventList(const quint32 categoryID) {
    /// Отправляем сигнал о принудительном сохранении в базу данных событий в категорию
    emit categoryEventsMustBeSaved(categoryID, this->includedEvents);

    this->includedEvents.clear();
    this->selectedIncludedEvents.clear();

    this->boxLayoutEvents->clearEvents();
    this->widgetStorage.clear();
}

void AdminInCategoryIncludedEventBoxLayoutController::clearSelectedIncludedEvents() {
    for(SecurityEvent selectedIncludedEvent : selectedIncludedEvents) {
        this->deleteIncludedEvent(selectedIncludedEvent.getId());
    }
}

void AdminInCategoryIncludedEventBoxLayoutController::slotIncludeFreeEventsToCategory(QList<SecurityEvent> freeEvents) {
    for(SecurityEvent freeEvent : freeEvents) {

        //if(this->includedEvents.contains(freeEvent) || this->selectedIncludedEvents.contains(freeEvent))
            // throw

        this->slotAddIncludedEvent(freeEvent.getId(), freeEvent.getText());
    }
}

void AdminInCategoryIncludedEventBoxLayoutController::slotDeleteIncludedEvent(quint32 eventID) {
    this->deleteIncludedEventWidget(eventID);
    this->deleteIncludedEvent(eventID);
}

void AdminInCategoryIncludedEventBoxLayoutController::slotAddIncludedEvent(quint32 eventID, QString eventTitle) {
    SecurityEvent newEvent(eventID, eventTitle);

    this->addIncludedEvent(newEvent);
    this->addIncludedEventWidget(newEvent);
}

void AdminInCategoryIncludedEventBoxLayoutController::slotRemoveSelectedEventsFromCategoryButtonPressed() {
    emit eventsRemovedFromCategory(selectedIncludedEvents);

    for(SecurityEvent selectedIncludedEvent : selectedIncludedEvents) {

        this->slotDeleteIncludedEvent(selectedIncludedEvent.getId());
    }

    this->clearSelectedIncludedEvents();
}
