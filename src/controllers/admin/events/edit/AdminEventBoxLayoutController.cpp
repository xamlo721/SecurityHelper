#include "AdminEventBoxLayoutController.h"

#include "src/ui/admin/ItemDeletionMessageBox.h"
#include "src/ui/admin/EnumMessageBoxVariants.h"
#include "src/ui/admin/EnumMessageBoxItemVariants.h"

AdminEventBoxLayoutController::AdminEventBoxLayoutController(QObject *parent) : QObject{parent} {}

void AdminEventBoxLayoutController::init(QVBoxLayout *editMenuBoxLayoutEvents) {
    /// Выделяем память под бокс событий
    this->boxLayoutEvents = new AdminEventBoxLayout();
    /// Инициализируем бокс событий тем боксом, который уже находится в AdminEditMenuWidget
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

        this->boxLayoutEvents->addEventWidget(uneditableWidget, editableWidget);
    }
    /// Отправляем в ядро сигнал о завершении установки списка событий
    ///
}

void AdminEventBoxLayoutController::slotShowEditableWidget(UneditableEventWidget *uneditableWidget) {
    /// Берем редактируемый виджет из хранилища, по соответствующему ему не редактируемому виджету
    EditableEventWidget *editableWidget = this->widgetStorage.getEditableWidget(uneditableWidget->getID());
    /// Показываем редактируемый виджет
    this->boxLayoutEvents->showEditableWidget(uneditableWidget, editableWidget);

    /// Делаем все события не выбранными
    this->unselectAllEvents();
    /// Делаем все события не доступными
    this->disableAllEvents();

    /// Отправляем сигнал о том, что появилось активное событие
    emit eventIsActive();
}

void AdminEventBoxLayoutController::slotShowUneditableWidget(EditableEventWidget *editableWidget) {
    /// Берем не редактируемый виджет из хранилища, по соответствующему ему редактируемому виджету
    UneditableEventWidget *uneditableWidget = this->widgetStorage.getUneditableWidget(editableWidget->getID());

    /// Переименовываем событие в списке в соответствии с переименованием виджета администратором
    this->renameEvent(editableWidget->getID(), editableWidget->getTitle());

    /// Устанавливаем измененное администратором имя не редактируемому виджету
    uneditableWidget->setTitle(editableWidget->getTitle());

    /// Показываем не редактируемый виджет
    this->boxLayoutEvents->showUneditableWidget(editableWidget, uneditableWidget);

    /// Делаем все события доступными
    this->enableAllEvents();
    /// Отправляем сигнал о том, что активного события больше нет
    emit eventIsNotActive();
}

void AdminEventBoxLayoutController::addEvent() {
    ///     Создаем новое событие с id большим на 1, чем у последнего события и именем Новое событие
    SecurityEvent newEvent(events.last().getId() + 1, "Новое событие");
    /// Добавляем новое событие в список событий контроллера
    events.append(newEvent);

    /// Отправляем сигнал о том, что новое событие добавлено
    emit eventAdded(newEvent);
}

void AdminEventBoxLayoutController::deleteEvent(const quint32 eventID) {

    /// Удаление из списка событий контроллера необходимого события
    /// ( удаление не изменяет айди других событий )
    for(SecurityEvent &event : events) {
        if(event.getId() == eventID) {

            /// Удаляем событие
            events.removeOne(event);
        }
    }
    /// Отправляем сигнал о том, что событие удалено
    emit eventDeleted(eventID);
}

void AdminEventBoxLayoutController::renameEvent(const quint32 widgetID, const QString widgetText) {
    /// Переименование в списке контроллера необходимого события
    quint32 eventID;
    QString newEventTitle;
    for(SecurityEvent &event : events) {
        if(event.getId() == widgetID) {

            event.setText(widgetText);

            eventID = event.getId();
            newEventTitle = widgetText;
        }
    }

    emit eventRenamed(eventID, newEventTitle);
}

void AdminEventBoxLayoutController::unselectAllEvents() {
    for(SecurityEvent event : selectedEvents) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его не выбранным
        UneditableEventWidget *uneditableWidget = this->widgetStorage.getUneditableWidget(event.getId());
        this->boxLayoutEvents->unselectUneditableWidget(uneditableWidget);
    }
}

void AdminEventBoxLayoutController::enableAllEvents() {
    for(SecurityEvent event : events) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его доступным
        UneditableEventWidget *uneditableWidget = this->widgetStorage.getUneditableWidget(event.getId());
        this->boxLayoutEvents->enableUneditableWidget(uneditableWidget);
    }
}

void AdminEventBoxLayoutController::disableAllEvents() {
    for(SecurityEvent event : events) {
        /// Берем не редактируемый виджет из хранилища по ID события и делаем его не доступным
        UneditableEventWidget *uneditableWidget = this->widgetStorage.getUneditableWidget(event.getId());
        this->boxLayoutEvents->disableUneditableWidget(uneditableWidget);
    }
}

void AdminEventBoxLayoutController::slotEmptyWidget(EditableEventWidget * editableWidget) {
    /// Создаем окно сообщений
    ItemDeletionMessageBox messageBox;
    /// Вызываем его в режиме предупреждения, если администратор нажмет Да, то удаляем событие
    if(messageBox.openWarning(EnumMessageBoxVariants::DeletionOneItem, EnumMessageBoxItemVariants::Event) == ItemDeletionMessageBox::Yes) {

        UneditableEventWidget *uneditableEmptyWidget = this->widgetStorage.getUneditableWidget(editableWidget->getID());
        /// Удаляем событие из списка контроллера
        this->deleteEvent(uneditableEmptyWidget->getID());
        /// Удаляем виджет из хранилища
        this->widgetStorage.removeWidget(uneditableEmptyWidget->getID());
        /// Удаляем виджет из бокса событий
        this->boxLayoutEvents->deleteEventWidget(uneditableEmptyWidget);

        /// Производим разблокировку интерфейса
        this->enableAllEvents();
        emit eventIsNotActive();
    }
}

void AdminEventBoxLayoutController::slotDeleteEvent(UneditableEventWidget * uneditableWidget) {
    /// Создаем окно сообщений
    ItemDeletionMessageBox messageBox;
    /// Вызываем его в режиме предупреждения, если администратор нажмет Да, то удаляем событие
    if(messageBox.openWarning(EnumMessageBoxVariants::DeletionOneItem, EnumMessageBoxItemVariants::Event) == ItemDeletionMessageBox::Yes) {

        /// Удаляем событие из списка контроллера
        this->deleteEvent(uneditableWidget->getID());
        /// Удаляем виджет из хранилища
        this->widgetStorage.removeWidget(uneditableWidget->getID());
        /// Удаляем виджет из бокса событий
        this->boxLayoutEvents->deleteEventWidget(uneditableWidget);
    }
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
    /// Создаем окно сообщений
    ItemDeletionMessageBox messageBox;
    /// Вызываем его в режиме предупреждения, если администратор нажмет Да, то удаляем выбранные события
    if(messageBox.openWarning(EnumMessageBoxVariants::DeletionSeveralItems, EnumMessageBoxItemVariants::Event) == ItemDeletionMessageBox::Yes) {

        /// Удаляем все выбранные события
        for(SecurityEvent &event : selectedEvents) {

            /// Удаляем виджет события из бокса
            this->boxLayoutEvents->deleteEventWidget(this->widgetStorage.getUneditableWidget(event.getId()));

            /// Удаляем виджет из хранилища
            this->widgetStorage.removeWidget(event.getId());

            /// Удаляем событие из списка выбранных событий контроллера
            this->onEventUnselected(event.getId());
            /// Удаляем событие из списка событий контроллера
            this->deleteEvent(event.getId());

        }
    }
}

void AdminEventBoxLayoutController::onEventSelected(const quint32 eventID) {
    // Проверка, есть ли в списке событий такое событие
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
    // Проверка, есть ли в списке событий такое событие
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
