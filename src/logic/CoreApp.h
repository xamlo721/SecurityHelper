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

    public:

        QMap<quint32, SecurityEvent> eventsSaved = XMLHelper::readDatabase("../SecurityHelper/storage/").events;
        QMap<quint32, SecurityEventCategory> categoriesSaved = XMLHelper::readDatabase("../SecurityHelper/storage/").categories;
        QMap<quint32, SecurityIncident> incidentsSaved = XMLHelper::readDatabase("../SecurityHelper/storage/").incidents;

    public:
        explicit CoreApp(QObject *parent = nullptr);

        void init();

    signals:

//        void eventsFormed(QMap<quint32, SecurityEvent> events);
//        void freeEventsFormed(QMap<quint32, SecurityEvent> freeEvents);
//        void freeEventsForIncidentFormed(QMap<quint32, SecurityEvent> freeEvents);

//        void incidentsFormed(QMap<quint32, SecurityIncident> incidents);
//        void freeIncidentsFormed(QMap<quint32, SecurityIncident> freeIncidents);

//        void scenariesFormed(QMap<quint32, SecurityScenario> scenaries);
//        void freeIncidentsForScenarioFormed(QMap<quint32, SecurityIncident> freeIncidents);

//        void signalOpenAdminCategory(const QMap<quint32, SecurityEvent> categoryEvents);
//        void signalOpenAdminDeletedCategory(const QMap<quint32, SecurityEvent> categoryEvents);

//        void signalOpenAdminIncident(const QMap<quint32, SecurityEvent> incidentEvents);

//        void signalOpenAdminScenario(const QMap<quint32, SecurityIncident> scenarioIncidents);

    public slots:
        void acceptCategoriesForSaving(const QMap<quint32, SecurityEventCategory> categories);
        void acceptIncidentsForSaving(const QMap<quint32, SecurityIncident> incidents);

        void acceptEventCategoryForSaving(const quint32 categoryID, QMap<quint32, SecurityEvent> categoryEvents);
        void acceptEventIncidentsForSaving(const quint32 incidentID, QMap<quint32, SecurityEvent> incidentEvents);
        void acceptEventForSaving(QMap<quint32, SecurityEvent> events);

//        void onOpenCategory(quint32 categoryId, bool isForAdminMode = false);
//        void onOpenDeletedCategory(const quint32 categoryId);

//        void onCalculateIncident(QMap<quint32, SecurityEvent> selectedEvents);

//        void onOpenIncident(quint32 incidentId);
//        void onOpenAdminIncident(quint32 incidentId);

//        void onOpenScenario(quint32 id);
//        void onOpenAdminScenario(quint32 scenarioID);

//        void formEvents();
//        void formFreeEvents();
//        void formFreeEventsForIncident(const quint32 incidentID);

//        void formIncidents();
//        void formFreeIncidents();

//        void formScenaries();
//        void formFreeIncidentsForScenario(const quint32 scenarioID);

    private:
        Database db = XMLHelper::readDatabase("../SecurityHelper/storage/");

};

#endif // COREAPP_H
