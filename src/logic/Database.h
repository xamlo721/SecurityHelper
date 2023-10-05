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
        Database(QMap<quint32, SecurityEvent> events, QMap<quint32, SecurityEventCategory> categories,
                 QMap<quint32, SecurityIncident> incidents, QMap<quint32, SecurityRecommendations> recommendations,
                 QMap<quint32, SecurityScenario> scenaries, QObject *parent = nullptr);

        Database(const Database& other);

        Database& operator=(const Database& other);
        bool operator==(const Database& other) const;
        bool operator!=(const Database& other) const;

    public:
        QMap<quint32, SecurityEvent> events;
        QMap<quint32, SecurityEventCategory> categories;
        QMap<quint32, SecurityIncident> incidents;
        QMap<quint32, SecurityRecommendations> recommendations;
        QMap<quint32, SecurityScenario> scenaries;

    signals:

};

#endif // DATABASE_H
