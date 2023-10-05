#include "AdminInCategoryIncludedEventBoxLayoutController.h"

AdminInCategoryIncludedEventBoxLayoutController::AdminInCategoryIncludedEventBoxLayoutController(QObject *parent) : QObject{parent} {}

AdminInCategoryIncludedEventBoxLayoutController::~AdminInCategoryIncludedEventBoxLayoutController() {
    delete this->boxLayoutEvents;
}

void AdminInCategoryIncludedEventBoxLayoutController::addIncludedEvent(SecurityEvent event) {
    includedEvents.append(event);

    InCategoryEventWidget *eventWidget = new InCategoryEventWidget(event.getId(), event.getText());

    this->widgetStorage.appendWidget(eventWidget);
    this->boxLayoutEvents->addEventWidget(eventWidget);
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

void AdminInCategoryIncludedEventBoxLayoutController::deleteIncludedEvent(quint32 eventID) {
    this->boxLayoutEvents->deleteEventWidget(this->widgetStorage.getEventWidget(eventID));

    this->widgetStorage.removeWidget(eventID);

    this->onIncludedEventUnselected(eventID);

    for(SecurityEvent &event : includedEvents) {
        if(event.getId() == eventID) {
            includedEvents.removeOne(event);
        }
    }
}

void AdminInCategoryIncludedEventBoxLayoutController::unselectAllIncludedEvents() {
    for(SecurityEvent event : selectedIncludedEvents) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его не выбранным
        InCategoryEventWidget *eventWidget = this->widgetStorage.getEventWidget(event.getId());
        this->boxLayoutEvents->unselectEventWidget(eventWidget);
    }
}

void AdminInCategoryIncludedEventBoxLayoutController::enableAllIncludedEvents() {
    for(SecurityEvent event : includedEvents) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его доступным
        InCategoryEventWidget *eventWidget = this->widgetStorage.getEventWidget(event.getId());
        this->boxLayoutEvents->enableEventWidget(eventWidget);
    }
}
void AdminInCategoryIncludedEventBoxLayoutController::disableAllIncludedEvents() {
    for(SecurityEvent event : includedEvents) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его не доступным
        InCategoryEventWidget *eventWidget = this->widgetStorage.getEventWidget(event.getId());
        this->boxLayoutEvents->disableEventWidget(eventWidget);
    }
}

void AdminInCategoryIncludedEventBoxLayoutController::onIncludedEventSelected(const quint32 eventID) {
    // Проверка, есть ли в списке событий такое событие
    quint32 eventsChecked = 0;
    for(SecurityEvent event : includedEvents) {
        if(event.getId() != eventID)
            eventsChecked++;
    }
    //if(eventsChecked == events.size())
        // throw

    /// Находим и забрасываем событие в список выбранных
    for(quint32 i = 0; i < includedEvents.size(); i++) {
        SecurityEvent event = this->includedEvents.at(i);
        if(event.getId() == eventID) {
            this->selectedIncludedEvents.append(event);

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
    //if(eventsChecked == events.size())
        // throw

    /// Находим и удаляем событие из списка выбранных событий
    for(quint32 i = 0; i < selectedIncludedEvents.size(); i++) {
        SecurityEvent selectedEvent = this->selectedIncludedEvents.at(i);
        if(selectedEvent.getId() == eventID)
            this->selectedIncludedEvents.removeOne(selectedEvent);
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

        InCategoryEventWidget *eventWidget = new InCategoryEventWidget(event.getId(), event.getText());

        this->widgetStorage.appendWidget(eventWidget);
        this->boxLayoutEvents->addEventWidget(eventWidget);
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

        this->addIncludedEvent(freeEvent);
    }
}

void AdminInCategoryIncludedEventBoxLayoutController::slotRemoveSelectedEventsFromCategoryButtonPressed() {
    emit eventsRemovedFromCategory(selectedIncludedEvents);

    this->clearSelectedIncludedEvents();
}
