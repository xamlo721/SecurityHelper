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

    signals:
        void signalOpenCategory(QList<SecurityEvent> categoryEvents);
        void signalOpenCategories(QList<SecurityEventCategory> availableCategories);
        void signalOpenIncidents(QList<SecurityIncident> incidents);

    public slots:
        void onOpenCategory(int categoryId);
        void onCalculateIncident(QList<SecurityEvent> selectedEvents);
        void onOpenIncident(int id);

    private:
        Database db = XMLHelper::readDatabase("../SecurityHelper/storage/");

};

#endif // COREAPP_H
