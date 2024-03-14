#ifndef INCIDENTCONTROLLER_H
#define INCIDENTCONTROLLER_H

#include <QObject>
#include <QMap>

#include "src/items/SecurityIncident.h"
#include "src/items/SecurityEvent.h"

#include "src/logic/Database.h"

#include "src/ui/admin/AdminIncidentsWidget.h"
#include "src/ui/admin/dialogs/AdminIncidentDialog.h"

class IncidentController : public QObject {

    Q_OBJECT

    private:
        Database copyDatabase;
        AdminIncidentsWidget *ui;
        AdminIncidentDialog *editDialog;
        QMap<quint32, SecurityIncident> incidents;
        QMap<quint32, SecurityEvent> allEvents;
        QList<SecurityEvent> availableEvents;
        QList<SecurityEvent> selectedEvents;

    public:
        explicit IncidentController(QObject *parent = nullptr);

        void init(AdminIncidentsWidget *incidentWidget);

    public slots:

        void onDatabaseUpdated(const Database & db);


    private slots:
        void onIncidentSelected(quint32 incidentID);
        void onIncidentAdded();
        void onIncidentEditRequest(quint32 incidentID);
        void onIncidentUpdated(quint32 incidentID, QString categoryName);
        void onIncidentDeleted(quint32 incidentID);
        void onEventSelected(quint32 eventID);
        void onEventUnselected(quint32 eventID);

    signals:
        /**
         * @brief signalAdminAddIncident - сигнал вызывается
         * при кажатии добавлении администратором нового инцидента
         */
        void signalAdminAddIncident();

        /**
         * @brief signalAdminUpdateIncident - сигнал вызывается
         * при изменении администратором существующего инцидента
         * @param incidentID - ID выбранного инцидента
         * @param incident - изменённый инцидент
         */
        void signalAdminUpdateIncident(quint32 incidentID, SecurityIncident incident);

        /**
         * @brief signalAdminDeleteIncident - сигнал вызывается
         * при удалении администратором существующего инцидента
         * @param incidentID - ID выбранного инцидента
         */
        void signalAdminDeleteIncident(quint32 incidentID);

};

#endif // INCIDENTCONTROLLER_H
