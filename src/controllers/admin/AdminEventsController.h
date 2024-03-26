#ifndef ADMINEVENTSCONTROLLER_H
#define ADMINEVENTSCONTROLLER_H

#include <QObject>

#include "src/logic/Database.h"

#include "src/ui/admin/AdminEventsWidget.h"
#include "src/ui/admin/dialogs/AdminEventDialog.h"

class AdminEventsController : public QObject {

    Q_OBJECT

    private:

        ///Копия базы даных для работы с данными на экране
        Database copyDatabase;
        ///Указатель на управляемый виджет
        AdminEventsWidget *ui;
        ///Указатель на открываемое окно редактирования
        AdminEventDialog *editDialog;

        ///ID выбранного события
        quint32 selectedEventID;

        QMap<quint32, SecurityEvent> allEvents;

    public:
        AdminEventsController(QObject *parent = nullptr);

        void init(AdminEventsWidget *eventsWidget);


    public slots:

        void onDatabaseUpdated(const Database & db);

    private slots:

        /**
         * @brief slotItemNameEdited - случает, когда меняется имя
         * @param name - новое имя объекта
         */
        void slotItemNameEdited(QString name);

        /**
         * @brief slotOnEventButtonPressed - слот. активируемый при нажатии
         * на нажатии на кнопку События.
         * @param eventId
         */
        void slotOnEventSelected(quint32 eventId);

        /**
         * @brief slotOnEventButtonPressed - слот. активируемый при нажатии
         * на нажатии на кнопку События.
         * @param eventId
         */
        void slotOnEventUnselected(quint32 eventId);

        void onEventAdded();
        void onEventUpdated(quint32 eventID, QString eventName);
        void onEventEditRequest(quint32 eventID);
        void onEventDeleted(quint32 eventID);

    signals:
        /**
         * @brief signalAdminAddEvent - сигнал вызывается
         * при кажатии добавлении администратором нового события
         */
        void signalAdminAddEvent();

        /**
         * @brief signalAdminUpdateEvent - сигнал вызывается
         * при изменении администратором существующего события
         * @param eventID - ID выбранного события
         * @param event - изменённое событие
         */
        void signalAdminUpdateEvent(quint32 eventID, SecurityEvent event);

        /**
         * @brief signalAdminDeleteEvent - сигнал вызывается
         * при удалении администратором существующего события
         * @param eventID - ID выбранного события
         */
        void signalAdminDeleteEvent(quint32 eventID);

};

#endif // ADMINEVENTSCONTROLLER_H
