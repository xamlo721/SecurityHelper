#ifndef COREAPP_H
#define COREAPP_H

#include <QObject>

#include "src/items/SecurityEvent.h"
#include "src/items/SecurityEventCategory.h"
#include "src/items/SecurityIncident.h"
#include "src/items/SecurityRecommendations.h"
#include "src/items/SecurityScenario.h"

#include "src/logic/XMLHelper.h"

class CoreApp : public QObject {

    Q_OBJECT

    private:
        Database db;

    public:
        CoreApp(QObject *parent = nullptr);

        void init();

        void loadDatabase();

        void saveDatabase();

        //Сервис для работы из админки

        void addCategory();

        void addEvent();

        void addIncident();

        void addScenario();

        void addRecommendations();


        void removeCategory(quint32 categoryID);

        void removeEvent(quint32 eventID);

        void removeIncident(quint32 incidentID);

        void removeScenario(quint32 scenarioID);

        void removeRecommendations(quint32 recommendationID);


        void updateCategory(quint32 categoryID, SecurityEventCategory category);

        void updateEvent(quint32 eventID, SecurityEvent event);

        void updateIncident(quint32 incidentID, SecurityIncident incident);

        void updateScenario(quint32 scenarioID, SecurityScenario scenarion);

        void updateRecommendations(quint32 recommendationID, SecurityRecommendations recommendation);


    public slots:
            void onEventsSelected(QList<SecurityEvent> selectedEvents);

    signals:
            void signalDatabaseUpdated(const Database & db);

            void signalIncidentCalculated(QList<SecurityIncident> incidents);



};

#endif // COREAPP_H
