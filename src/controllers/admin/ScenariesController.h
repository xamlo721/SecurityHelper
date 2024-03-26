#ifndef SCENARIESCONTROLLER_H
#define SCENARIESCONTROLLER_H

#include <QObject>

#include "src/items/SecurityIncident.h"
#include "src/items/SecurityScenario.h"

#include "src/logic/Database.h"

#include "src/ui/admin/AdminScenariesWidget.h"
#include "src/ui/admin/dialogs/AdminScenariesDialog.h"

class ScenariesController  : public QObject {

    Q_OBJECT

    private:
        Database copyDatabase;
        AdminScenariesWidget *ui;
        AdminScenariesDialog *editDialog;
        QMap<quint32, SecurityScenario> scenaries;
        QMap<quint32, SecurityIncident> allIncidents;
        QList<SecurityIncident> availableIncidents;
        QList<SecurityIncident> selectedIncidents;

        ///ID выбранной каьешлоии
        quint32 selectedScenarioID;

    public:
        ScenariesController(QObject *parent = nullptr);

        void init(AdminScenariesWidget *scenaryWidget);

    private:
        void resetSelectedIncidents(QList<SecurityIncident> freeIncidents);
        void resetAvailableIncidents(QList<SecurityIncident> freeIncidents);

    public slots:

        void onDatabaseUpdated(const Database & db);


    private slots:

        /**
         * @brief slotItemNameEdited - случает, когда меняется имя
         * @param name - новое имя объекта
         */
        void slotItemNameEdited(QString name);

        void onScenarySelected(quint32 scenaryID);
        void onScenaryUnselected(quint32 scenaryID);
        void onScenaryAdded();
        void onScenaryUpdated(quint32 scenaryID, QString categoryName);
        void onScenaryEditRequest(quint32 scenaryID);
        void onScenaryDeleted(quint32 scenaryID);
        void onIncidentSelected(quint32 incidentID);
        void onIncidentUnselected(quint32 incidentID);

    signals:
        /**
         * @brief signalAdminAddIncident - сигнал вызывается
         * при кажатии добавлении администратором нового сценария
         */
        void signalAdminAddScenary();

        /**
         * @brief signalAdminUpdateIncident - сигнал вызывается
         * при изменении администратором существующего сценария
         * @param scenaryID - ID выбранного сценария
         * @param scenary - изменённый сценарий
         */
        void signalAdminUpdateScenary(quint32 scenaryID, SecurityScenario scenary);

        /**
         * @brief signalAdminDeleteIncident - сигнал вызывается
         * при удалении администратором существующего сценария
         * @param scenaryID - ID выбранного сценария
         */
        void signalAdminDeleteScenary(quint32 scenaryID);

};

#endif // SCENARIESCONTROLLER_H
