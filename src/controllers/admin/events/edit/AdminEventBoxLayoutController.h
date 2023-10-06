#ifndef ADMINEVENTBOXLAYOUTCONTROLLER_H
#define ADMINEVENTBOXLAYOUTCONTROLLER_H

#include <QObject>

#include "src/items/SecurityEvent.h"

#include "src/ui/admin/events/edit/UneditableEventWidget.h"
#include "src/ui/admin/events/edit/EditableEventWidget.h"

#include "src/ui/admin/events/edit/AdminEventBoxLayout.h"

#include "src/ui/admin/events/edit/EventWidgetStorage.h"

class AdminEventBoxLayoutController : public QObject {

    Q_OBJECT

    private:
        /// Управляемый бокс событий
        AdminEventBoxLayout *boxLayoutEvents;

        /// Список событий, полученных из ядра программы
        QList<SecurityEvent> events;
        /// Список выбранных администратором событий
        QList<SecurityEvent> selectedEvents;
        /// Хранилище пар не редактирумого и редактируемого виджета
        EventWidgetStorage widgetStorage;

        SecurityEvent addEvent();
        void addEventWidget(const SecurityEvent event);

        void deleteEvent(const quint32 eventID);
        void deleteEventWidget(const quint32 eventID);

        void renameEvent(const quint32 widgetID, const QString widgetText);

        void unselectAllEvents();

        void enableAllEvents();
        void disableAllEvents();

    private slots:
        void slotShowEditableWidget(UneditableEventWidget *uneditableWidget);
        void slotShowUneditableWidget(EditableEventWidget *editableWidget);

        void slotEmptyWidget(EditableEventWidget * editableWidget);
        void slotDeleteEvent(UneditableEventWidget * uneditableWidget);

        void onEventSelected(const quint32 eventID);
        void onEventUnselected(const quint32 eventID);

    public:
        explicit AdminEventBoxLayoutController(QObject *parent = nullptr);

        void init(QVBoxLayout *editMenuBoxLayoutEvents);

    public slots:
        void setEventList(const QList<SecurityEvent> events);

        void slotAddEventButtonPressed();
        void slotDeleteSelectedEventsButtonPressed();

    signals:
        void signalSelectedEventsNotEmpty();
        void signalSelectedEventsEmpty();

        void eventIsActive();
        void eventIsNotActive();

        void eventAdded(SecurityEvent newEvent);
        void eventRenamed(const quint32 eventID, QString newEventTitle);
        void eventDeleted(const quint32 eventID);
};

#endif // ADMINEVENTBOXLAYOUTCONTROLLER_H
