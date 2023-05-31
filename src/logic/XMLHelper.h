#ifndef XMLHELPER_H
#define XMLHELPER_H

#include <QObject>

#include <QtXml/QDomElement>

#include "src/logic/Database.h" //FIXME: нарушение иерархии - переместить database в раздел items

#include "src/items/SecurityEvent.h"
#include "src/items/SecurityEventCategory.h"
#include "src/items/SecurityIncident.h"
#include "src/items/SecurityRecommendations.h"
#include "src/items/SecurityScenario.h"


class XMLHelper: public QObject {

    Q_OBJECT

    public:
        explicit XMLHelper(QObject *parent = nullptr);

        Database readDatabase(QString path);

        void writeDatabase(QString path);

        SecurityEvent readSecurityEvent(QDomElement xmlDomElement);

        SecurityEventCategory readSecurityEventCategory(QDomElement xmlDomElement);

        SecurityIncident readSecurityIncident(QDomElement xmlDomElement);

        SecurityRecommendations readSecurityRecommendations(QDomElement xmlDomElement);

        SecurityScenario readSecurityScenario(QDomElement xmlDomElement);

    signals:

};

#endif // XMLHELPER_H
