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
        explicit CoreApp(QObject *parent = nullptr);

        void init();

        QList<SecurityEvent> eventsSaved = CoreApp::eventToList(XMLHelper::readDatabase("../SecurityHelper/storage/").events);
        QList<SecurityEventCategory> categoriesSaved = CoreApp::categoriesToList(XMLHelper::readDatabase("../SecurityHelper/storage/").categories);
        QList<SecurityIncident> incidentsSaved = CoreApp::incidentsToList(XMLHelper::readDatabase("../SecurityHelper/storage/").incidents);

        QList<SecurityEventCategory> categoriesToList(QMap<quint32, SecurityEventCategory> qMapCategories);
        QList<SecurityIncident> incidentsToList(QMap<quint32, SecurityIncident> qMapIncidents);
        QList<SecurityEvent> eventToList(QMap<quint32, SecurityEvent> qMapEvents);

        //QMap<quint32, SecurityEventCategory> categoriesQListToQMap(const quint32 categoryID, QList<SecurityEvent> categoryEvents);
        //QMap<quint32, SecurityEventCategory> categoriesQListToQMap(const quint32 categoryID, QList<SecurityEvent> categoryEvents);

    signals:
        void signalOpenCategory(QList<SecurityEvent> categoryEvents);
        void signalOpenCategories(QList<SecurityEventCategory> availableCategories);
        void signalOpenIncidents(QList<SecurityIncident> incidents);
        void signalOpenScenaries(QList<SecurityScenario> scenaries);
        void signalOpenRecommandations(QList<SecurityRecommendations> scenaries);

        void signalAdminOpenCategories(QList<SecurityEventCategory> availableCategories);


        void eventsFormed(QList<SecurityEvent> events);
        void freeEventsFormed(QList<SecurityEvent> freeEvents);
        void freeEventsForIncidentFormed(QList<SecurityEvent> freeEvents);

        void incidentsFormed(QList<SecurityIncident> incidents);
        void freeIncidentsFormed(QList<SecurityIncident> freeIncidents);

        void scenariesFormed(QList<SecurityScenario> scenaries);
        void freeIncidentsForScenarioFormed(QList<SecurityIncident> freeIncidents);

        void signalOpenAdminCategory(const QList<SecurityEvent> categoryEvents);
        void signalOpenAdminDeletedCategory(const QList<SecurityEvent> categoryEvents);

        void signalOpenAdminIncident(const QList<SecurityEvent> incidentEvents);

        void signalOpenAdminScenario(const QList<SecurityIncident> scenarioIncidents);

    public slots:
        void acceptCategoriesForSaving(const QList<SecurityEventCategory> categories);
        void acceptIncidentsForSaving(const QList<SecurityIncident> incidents);

        void acceptEventCategoryForSaving(const quint32 categoryID, QList<SecurityEvent> categoryEvents);
        void acceptEventIncidentsForSaving(const quint32 incidentID, QList<SecurityEvent> incidentEvents);
        void acceptEventForSaving(QList<SecurityEvent> events);

        void onOpenCategory(quint32 categoryId, bool isForAdminMode = false);
        void onOpenDeletedCategory(const quint32 categoryId);

        void onCalculateIncident(QList<SecurityEvent> selectedEvents);

        void onOpenIncident(quint32 incidentId);
        void onOpenAdminIncident(quint32 incidentId);

        void onOpenScenario(quint32 id);
        void onOpenAdminScenario(quint32 scenarioID);

        void formEvents();
        void formFreeEvents();
        void formFreeEventsForIncident(const quint32 incidentID);

        void formIncidents();
        void formFreeIncidents();

        void formScenaries();
        void formFreeIncidentsForScenario(const quint32 scenarioID);

    private:
        Database db = XMLHelper::readDatabase("../SecurityHelper/storage/");

};

#endif // COREAPP_H
