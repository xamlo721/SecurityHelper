#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QMap>

#include "src/items/SecurityEvent.h"
#include "src/items/SecurityEventCategory.h"
#include "src/items/SecurityIncident.h"
#include "src/items/SecurityRecommendations.h"
#include "src/items/SecurityScenario.h"

class Database : public QObject {

    Q_OBJECT

    public:
        Database(QMap<int, SecurityEvent> events, QMap<int, SecurityEventCategory> categories, QMap<int, SecurityIncident> incidents, QMap<int, SecurityRecommendations> recommendations, QMap<int, SecurityScenario> scenaries, QObject *parent = nullptr);

        Database(const Database& other);

        Database& operator=(const Database& other);
        bool operator==(const Database& other) const;
        bool operator!=(const Database& other) const;

    private:
        QMap<int, SecurityEvent> events;
        QMap<int, SecurityEventCategory> categories;
        QMap<int, SecurityIncident> incidents;
        QMap<int, SecurityRecommendations> recommendations;
        QMap<int, SecurityScenario> scenaries;

    signals:

};

#endif // DATABASE_H
