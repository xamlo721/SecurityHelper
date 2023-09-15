#ifndef XMLHELPER_H
#define XMLHELPER_H

#include <QObject>
#include <QFile>

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

        static Database readDatabase(QString path);

        static void writeDatabase(QString path);

        static SecurityEvent readSecurityEvent(QDomElement xmlDomElement);

        static SecurityEventCategory readSecurityEventCategory(QDomElement xmlDomElement);

        static SecurityIncident readSecurityIncident(QDomElement xmlDomElement);

        static SecurityRecommendations readSecurityRecommendations(QDomElement xmlDomElement);

        static SecurityScenario readSecurityScenario(QDomElement xmlDomElement);

    signals:

};

#endif // XMLHELPER_H
