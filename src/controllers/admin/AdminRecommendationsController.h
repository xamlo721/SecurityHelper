#ifndef ADMINRECOMMENDATIONSWIDGET_H
#define ADMINRECOMMENDATIONSWIDGET_H

#include <QObject>
#include <QMap>

#include "src/items/SecurityIncident.h"
#include "src/items/SecurityEvent.h"

#include "src/logic/Database.h"

#include "src/ui/admin/AdminRecommendationWidget.h"
#include "src/ui/admin/dialogs/AdminRecommendationDialog.h"

class AdminRecommendationsController : public QObject {

    Q_OBJECT

    private:
        Database copyDatabase;
        AdminRecommendationWidget *ui;
        AdminRecommendationDialog *editDialog;
        QMap<quint32, SecurityRecommendations> recommendations;
        QMap<quint32, SecurityScenario> allScenaries;
        QList<SecurityScenario> availableScenaries;
        QList<SecurityScenario> selectedScenaries;


    public:
        AdminRecommendationsController(QObject *parent = nullptr);

        void init(AdminRecommendationWidget * recommendationWidget);

    public slots:

        void onDatabaseUpdated(const Database & db);

    private slots:
        void onRecommendationSelected(quint32 recommendationID);
        void onRecommendationAdded();
        void onRecommendationUpdated(quint32 recommendationID, QString recommendationName, QString TextContainment, QString TextFixes, QString TextRestore);
        void onRecommendationEditRequest(quint32 recommendationID);
        void onRecommendationDeleted(quint32 recommendationID);
        void onScenarySelected(quint32 scenaryID);
        void onScenaryUnselected(quint32 scenaryID);

    signals:
        /**
         * @brief signalAdminAddRecommendation - сигнал вызывается
         * при кажатии добавлении администратором нового инцидента
         */
        void signalAdminAddRecommendation();

        /**
         * @brief signalAdminUpdateRecommendation - сигнал вызывается
         * при изменении администратором существующего инцидента
         * @param recommendationID - ID выбранного инцидента
         * @param incident - изменённый инцидент
         */
        void signalAdminUpdateRecommendation(quint32 recommendationID, SecurityRecommendations incident);

        /**
         * @brief signalAdminDeleteRecommendation - сигнал вызывается
         * при удалении администратором существующего инцидента
         * @param incidentID - ID выбранного инцидента
         */
        void signalAdminDeleteRecommendation(quint32 recommendationID);
};

#endif // ADMINRECOMMENDATIONSWIDGET_H
