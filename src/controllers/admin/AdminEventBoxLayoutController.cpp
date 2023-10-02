#include "AdminEventBoxLayoutController.h"

AdminEventBoxLayoutController::AdminEventBoxLayoutController(QObject *parent) : QObject{parent} {}

void AdminEventBoxLayoutController::init(QVBoxLayout *editMenuBoxLayoutEvents) {
    /// Выделяем память под бокс категорий
    this->boxLayoutEvents = new AdminEventBoxLayout();
    /// Инициализируем бокс категорий тем боксом, который уже находится в AdminEditMenuWidget
    this->boxLayoutEvents->init(editMenuBoxLayoutEvents);

    /// Блок связи сигналов, поступающих в меню редактирования из не редактируемого виджета
    QObject::connect(this->boxLayoutEvents, &AdminEventBoxLayout::signalEditEvent, this, &AdminEventBoxLayoutController::slotShowEditableWidget);
    QObject::connect(this->boxLayoutEvents, &AdminEventBoxLayout::signalDeleteEvent, this, &AdminEventBoxLayoutController::slotDeleteEvent);

    QObject::connect(this->boxLayoutEvents, &AdminEventBoxLayout::signalEventSelected, this, &AdminEventBoxLayoutController::onEventSelected);
    QObject::connect(this->boxLayoutEvents, &AdminEventBoxLayout::signalEventUnselected, this, &AdminEventBoxLayoutController::onEventUnselected);

    /// Блок связи сигналов, поступающих в меню редактирования из редактируемого виджета
    QObject::connect(this->boxLayoutEvents, &AdminEventBoxLayout::editingFinished, this, &AdminEventBoxLayoutController::slotShowUneditableWidget);
    QObject::connect(this->boxLayoutEvents, &AdminEventBoxLayout::emptyWidget, this, &AdminEventBoxLayoutController::slotEmptyWidget);
}

void AdminEventBoxLayoutController::setEventList(const QList<SecurityEvent> events) {
    /// Сохраняем список событий
    this->events = events;
    /// Очищаем список событий в боксе для исключения неточностей
    this->boxLayoutEvents->clearEvents();
    /// Проходим по списку событий, инициализируя и добавляя виджеты в бокс
    for (SecurityEvent event : events) {
        UneditableEventWidget *uneditableWidget = new UneditableEventWidget(event.getId(), event.getText());
        EditableEventWidget *editableWidget = new EditableEventWidget(event.getId(), event.getText());
        this->widgetStorage.appendWidget(uneditableWidget, editableWidget);
        //QObject::connect(categoryWidget, &UneditableEventCategoryWidget::signalOpenIncident, this, &AdminEditMenuController::signalOpenCategory);

        this->boxLayoutEvents->addEventWidget(uneditableWidget, editableWidget);
    }
}

void AdminEventBoxLayoutController::slotShowEditableWidget(UneditableEventWidget *uneditableWidget) {
    /// Берем редактируемый виджет из хранилища, по соответствующему ему не редактируемому виджету
    EditableEventWidget *editableWidget = this->widgetStorage.getEditableWidget(uneditableWidget->getID());
    /// Показываем редактируемый виджет
    this->boxLayoutEvents->showEditableWidget(uneditableWidget, editableWidget);
}

void AdminEventBoxLayoutController::slotShowUneditableWidget(EditableEventWidget *editableWidget) {
    /// Берем не редактируемый виджет из хранилища, по соответствующему ему редактируемому виджету
    UneditableEventWidget *uneditableWidget = this->widgetStorage.getUneditableWidget(editableWidget->getID());

    /// Переименовываем событие в списке в соответствии с переименованием виджета администратором
    this->renameEvent(uneditableWidget->getID(), uneditableWidget->getText());

    /// Устанавливаем измененное администратором имя не редактируемому виджету
    uneditableWidget->setText(editableWidget->getText());

    /// Показываем не редактируемый виджет
    this->boxLayoutEvents->showUneditableWidget(editableWidget, uneditableWidget);
}

void AdminEventBoxLayoutController::addEvent() {
    ///     Создаем новое событие с id большим на 1, чем у последнего события и именем Новое событие
    SecurityEvent newEvent(events.last().getId() + 1, "Новое событие");
    /// Добавляем новое событие в список событий контроллера
    events.append(newEvent);
}

void AdminEventBoxLayoutController::deleteEvent(const quint32 eventID) {
    /// Удаление из списка событий контроллера необходимого события
    /// ( удаление не изменяет айди других событий )
    for(SecurityEvent &event : events) {
        if(event.getId() == eventID) {
            events.removeOne(event);
        }
    }
}

void AdminEventBoxLayoutController::renameEvent(const quint32 widgetID, const QString widgetText) {
    /// Переименование в списке контроллера необходимого события
    for(SecurityEvent &event : events) {
        if(event.getId() == widgetID) {
            event.setText(widgetText);
        }
    }
}

void AdminEventBoxLayoutController::slotEmptyWidget(EditableEventWidget * editableWidget) {

    UneditableEventWidget *uneditableEmptyWidget = this->widgetStorage.getUneditableWidget(editableWidget->getID());
    /// Удаляем событие из списка контроллера
    this->deleteEvent(uneditableEmptyWidget->getID());
    /// Удаляем виджет из хранилища
    this->widgetStorage.removeWidget(uneditableEmptyWidget->getID());
    /// Удаляем виджет из бокса событий
    this->boxLayoutEvents->deleteEventWidget(uneditableEmptyWidget);
}

void AdminEventBoxLayoutController::slotDeleteEvent(UneditableEventWidget * uneditableWidget) {
    /// Удаляем событие из списка контроллера
    this->deleteEvent(uneditableWidget->getID());
    /// Удаляем виджет из бокса событий
    this->boxLayoutEvents->deleteEventWidget(uneditableWidget);
}

void AdminEventBoxLayoutController::slotAddEventButtonPressed() {
    /// Добавляем в список категорий новое событие
    this->addEvent();
    /// Создаем из него виджет
    UneditableEventWidget *newUneditableCategoryWidget = new UneditableEventWidget(events.last().getId(), events.last().getText());
    EditableEventWidget *newEditableCategoryWidget = new EditableEventWidget(events.last().getId(), events.last().getText());
    /// Добавляем новый виджет в хранилище
    this->widgetStorage.appendWidget(newUneditableCategoryWidget, newEditableCategoryWidget);
    /// Добавляем новый виджет в бокс
    this->boxLayoutEvents->addEventWidget(newUneditableCategoryWidget, newEditableCategoryWidget);
}

void AdminEventBoxLayoutController::slotDeleteSelectedEventsButtonPressed() {
    /// Удаляем все выбранные события
    for(SecurityEvent &event : selectedEvents) {

        /// Удаляем виджет события из бокса
        UneditableEventWidget *tempUneditableEventWidget = this->widgetStorage.getUneditableWidget(event.getId());
        this->boxLayoutEvents->deleteEventWidget(tempUneditableEventWidget);

        /// Удаляем виджет из хранилища
        this->widgetStorage.removeWidget(event.getId());

        /// Удаляем событие из списка выбранных событий контроллера
        this->onEventUnselected(event.getId());
        /// Удаляем событие из списка событий контроллера
        this->deleteEvent(event.getId());

    }
}

void AdminEventBoxLayoutController::onEventSelected(const quint32 eventID) {
    /// Проверка, есть ли в списке событий такое событие
    quint32 eventsChecked = 0;
    for(SecurityEvent event : events) {
        if(event.getId() != eventID)
            eventsChecked++;
    }
    //if(eventsChecked == events.size())
        // throw

    /// Находим и забрасываем событие в список выбранных
    for(quint32 i = 0; i < events.size(); i++) {
        SecurityEvent event = this->events.at(i);
        if(event.getId() == eventID) {
            this->selectedEvents.append(event);

        }
    }
    if(!selectedEvents.isEmpty())
        emit signalSelectedEventsNotEmpty();
}

void AdminEventBoxLayoutController::onEventUnselected(const quint32 eventID) {
    /// Проверка, есть ли в списке событий такое событие
    quint32 eventsChecked = 0;
    for(SecurityEvent event : events) {
        if(event.getId() != eventID)
            eventsChecked++;
    }
    //if(eventsChecked == events.size())
        // throw

    /// Находим и удаляем событие из списка выбранных событий
    for(quint32 i = 0; i < selectedEvents.size(); i++) {
        SecurityEvent selectedEvent = this->selectedEvents.at(i);
        if(selectedEvent.getId() == eventID)
            this->selectedEvents.removeOne(selectedEvent);
    }
    if(selectedEvents.isEmpty())
        emit signalSelectedEventsEmpty();
}
