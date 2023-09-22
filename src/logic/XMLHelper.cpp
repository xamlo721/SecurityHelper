#include "XMLHelper.h"
#include "src/logic/XmlUtils.h"
#include <QMap>

XMLHelper::XMLHelper(QObject *parent) : QObject(parent) {

}

Database XMLHelper::readDatabase(QString path) {

    if (!XmlUtils::checkFile(path + "Events.xml")) {
        throw std::runtime_error(QString("[XMLHelper] Error! Cannot load Events.xml!").toLocal8Bit().constData());
    }
    if (!XmlUtils::checkFile(path + "Categories.xml")) {
        throw std::runtime_error(QString("[XMLHelper] Error! Cannot load Categories.xml!").toLocal8Bit().constData());
    }
    if (!XmlUtils::checkFile(path + "Incidents.xml")) {
        throw std::runtime_error(QString("[XMLHelper] Error! Cannot load Incidents.xml!").toLocal8Bit().constData());
    }
    if (!XmlUtils::checkFile(path + "Recommendations.xml")) {
        throw std::runtime_error(QString("[XMLHelper] Error! Cannot load Recommendations.xml!").toLocal8Bit().constData());
    }
    if (!XmlUtils::checkFile(path + "Scenaries.xml")) {
        throw std::runtime_error(QString("[XMLHelper] Erro!r Cannot load Scenaries.xml!").toLocal8Bit().constData());
    }


    QMap<quint32, SecurityEvent> events;
    QMap<quint32, SecurityEventCategory> categories;
    QMap<quint32, SecurityIncident> incidents;
    QMap<quint32, SecurityRecommendations> recommendations;
    QMap<quint32, SecurityScenario> scenaries;

    {
        QFile eventsFile(path + "Events.xml");
        eventsFile.open(QFile::ReadOnly | QFile::Text);
        QDomDocument eventsDoc;
        eventsDoc.setContent(&eventsFile);
        QDomElement eventsDatabaseDomElement = XmlUtils::readSingleNode(eventsDoc.documentElement(), "Database");
        QDomElement databaseDomElement = XmlUtils::readSingleNode(eventsDatabaseDomElement, "Events");
        QList<QDomElement> eventListDomElements = XmlUtils::readMultiNode(databaseDomElement, "Event");

        for (QDomElement eventDomElement : eventListDomElements) {
            SecurityEvent event = XMLHelper::readSecurityEvent(eventDomElement);
            events.insert(event.getId(), event);
        }
        eventsFile.close();
    }

    {
        QFile categoriesFile(path + "Categories.xml");
        categoriesFile.open(QFile::ReadOnly | QFile::Text);
        QDomDocument eventsDoc;
        eventsDoc.setContent(&categoriesFile);
        QDomElement eventsDatabaseDomElement = XmlUtils::readSingleNode(eventsDoc.documentElement(), "Database");
        QDomElement databaseDomElement = XmlUtils::readSingleNode(eventsDatabaseDomElement, "Categories");
        QList<QDomElement> categoryListDomElements = XmlUtils::readMultiNode(databaseDomElement, "Category");

        for (QDomElement categoryDomElement : categoryListDomElements) {
            SecurityEventCategory category = XMLHelper::readSecurityEventCategory(categoryDomElement);
            categories.insert(category.getId(), category);
        }
        categoriesFile.close();
    }

    {
        QFile incidentsFile(path + "Incidents.xml");
        incidentsFile.open(QFile::ReadOnly | QFile::Text);
        QDomDocument eventsDoc;
        eventsDoc.setContent(&incidentsFile);
        QDomElement eventsDatabaseDomElement = XmlUtils::readSingleNode(eventsDoc.documentElement(), "Database");
        QDomElement databaseDomElement = XmlUtils::readSingleNode(eventsDatabaseDomElement, "Incidents");
        QList<QDomElement> incidentListDomElements = XmlUtils::readMultiNode(databaseDomElement, "Incident");

        for (QDomElement incidentDomElement : incidentListDomElements) {
            SecurityIncident incident = XMLHelper::readSecurityIncident(incidentDomElement);
            incidents.insert(incident.getId(), incident);
        }
        incidentsFile.close();
    }

    {
        QFile recommendationsFile(path + "Recommendations.xml");
        recommendationsFile.open(QFile::ReadOnly | QFile::Text);
        QDomDocument eventsDoc;
        eventsDoc.setContent(&recommendationsFile);
        QDomElement eventsDatabaseDomElement = XmlUtils::readSingleNode(eventsDoc.documentElement(), "Database");
        QDomElement databaseDomElement = XmlUtils::readSingleNode(eventsDatabaseDomElement, "Recommendations");
        QList<QDomElement> recommendationListDomElements = XmlUtils::readMultiNode(databaseDomElement, "Recommendation");

        for (QDomElement recommendationDomElement : recommendationListDomElements) {
            SecurityRecommendations recommendation = XMLHelper::readSecurityRecommendations(recommendationDomElement);
            recommendations.insert(recommendation.getId(), recommendation);
        }
        recommendationsFile.close();
    }

    {
        QFile scenariesFile(path + "Scenaries.xml");
        scenariesFile.open(QFile::ReadOnly | QFile::Text);
        QDomDocument eventsDoc;
        eventsDoc.setContent(&scenariesFile);
        QDomElement eventsDatabaseDomElement = XmlUtils::readSingleNode(eventsDoc.documentElement(), "Database");
        QDomElement databaseDomElement = XmlUtils::readSingleNode(eventsDatabaseDomElement, "Scenaries");
        QList<QDomElement> scenaryListDomElements = XmlUtils::readMultiNode(databaseDomElement, "Scenary");

        for (QDomElement scenaryDomElement : scenaryListDomElements) {
            SecurityScenario scenary = XMLHelper::readSecurityScenario(scenaryDomElement);
            scenaries.insert(scenary.getId(), scenary);
        }
        scenariesFile.close();
    }

    return Database(events, categories, incidents, recommendations, scenaries);
}

void XMLHelper::writeDatabase(QString path, Database database) {

    if (!XmlUtils::checkFile(path + "Events.xml")) {
        throw std::runtime_error(QString("[XMLHelper] Error! Cannot load Events.xml!").toLocal8Bit().constData());
    }
    if (!XmlUtils::checkFile(path + "Categories.xml")) {
        throw std::runtime_error(QString("[XMLHelper] Error! Cannot load Categories.xml!").toLocal8Bit().constData());
    }
    if (!XmlUtils::checkFile(path + "Incidents.xml")) {
        throw std::runtime_error(QString("[XMLHelper] Error! Cannot load Incidents.xml!").toLocal8Bit().constData());
    }
    if (!XmlUtils::checkFile(path + "Recommendations.xml")) {
        throw std::runtime_error(QString("[XMLHelper] Error! Cannot load Recommendations.xml!").toLocal8Bit().constData());
    }
    if (!XmlUtils::checkFile(path + "Scenaries.xml")) {
        throw std::runtime_error(QString("[XMLHelper] Erro!r Cannot load Scenaries.xml!").toLocal8Bit().constData());
    }

    {
        QFile eventsFile(path + "Events.xml");
        eventsFile.open(QFile::WriteOnly | QFile::Text);
        QDomDocument eventsDoc;
        XmlUtils::writeXMLHeader(&eventsDoc);
        QDomElement root = eventsDoc.createElement("Events");
        eventsDoc.appendChild(root);
        XmlUtils::writeUint(eventsDoc, root, "events", database.events.firstKey());
        QTextStream out(&eventsFile);
        QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
        out.setCodec(codec);
        out << eventsDoc;
        eventsFile.close();
    }

    {
        QFile categoriesFile(path + "Categories.xml");
        categoriesFile.open(QFile::WriteOnly | QFile::Text);
        QDomDocument eventsDoc;
        XmlUtils::writeXMLHeader(&eventsDoc);
        QDomElement root = eventsDoc.createElement("Categories");
        eventsDoc.appendChild(root);
        XmlUtils::writeUint(eventsDoc, root, "categories", database.categories.firstKey());
        QTextStream out(&categoriesFile);
        QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
        out.setCodec(codec);
        out << eventsDoc;
        categoriesFile.close();
    }

    {
        QFile incidentsFile(path + "Incidents.xml");
        incidentsFile.open(QFile::WriteOnly | QFile::Text);
        QDomDocument eventsDoc;
        XmlUtils::writeXMLHeader(&eventsDoc);
        QDomElement root = eventsDoc.createElement("Incidents");
        eventsDoc.appendChild(root);
        XmlUtils::writeUint(eventsDoc, root, "incidents", database.incidents.firstKey());
        QTextStream out(&incidentsFile);
        QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
        out.setCodec(codec);
        out << eventsDoc;
        incidentsFile.close();
    }

    {
        QFile recommendationsFile(path + "Recommendations.xml");
        recommendationsFile.open(QFile::WriteOnly | QFile::Text);
        QDomDocument eventsDoc;
        XmlUtils::writeXMLHeader(&eventsDoc);
        QDomElement root = eventsDoc.createElement("Recommendations");
        eventsDoc.appendChild(root);
        XmlUtils::writeUint(eventsDoc, root, "recommendations", database.recommendations.firstKey());
        QTextStream out(&recommendationsFile);
        QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
        out.setCodec(codec);
        out << eventsDoc;
        recommendationsFile.close();
    }

    {
        QFile scenariesFile(path + "Scenaries.xml");
        scenariesFile.open(QFile::WriteOnly | QFile::Text);
        QDomDocument eventsDoc;
        XmlUtils::writeXMLHeader(&eventsDoc);
        QDomElement root = eventsDoc.createElement("Scenaries");
        eventsDoc.appendChild(root);
        XmlUtils::writeUint(eventsDoc, root, "scenaries", database.scenaries.firstKey());
        QTextStream out(&scenariesFile);
        QTextCodec* codec = QTextCodec::codecForName( "UTF-8" );
        out.setCodec(codec);
        out << eventsDoc;
        scenariesFile.close();
    }

}

SecurityEvent XMLHelper::readSecurityEvent(QDomElement xmlDomElement) {
    QString eventTitle =XmlUtils::readText(xmlDomElement, "Text");
    quint32 eventId = XmlUtils::readint(xmlDomElement, "id");
    return SecurityEvent(eventId, eventTitle);
}

SecurityEventCategory XMLHelper::readSecurityEventCategory(QDomElement xmlDomElement) {
    QString categoryTitle =XmlUtils::readText(xmlDomElement, "Text");
    quint32 categoryId = XmlUtils::readint(xmlDomElement, "id");
    QList<quint32> categoryEventIds = XmlUtils::readUints(xmlDomElement, "events");
    return SecurityEventCategory(categoryId, categoryTitle, categoryEventIds);
}

SecurityIncident XMLHelper::readSecurityIncident(QDomElement xmlDomElement) {
    QString incidentTitle =XmlUtils::readText(xmlDomElement, "Text");
    QString incidentName =XmlUtils::readText(xmlDomElement, "Name");
    quint32 incidentId = XmlUtils::readint(xmlDomElement, "id");
    QList<quint32> incidentEventIds = XmlUtils::readUints(xmlDomElement, "events");
    return SecurityIncident(incidentId, incidentTitle, incidentName, incidentEventIds);
}

SecurityRecommendations XMLHelper::readSecurityRecommendations(QDomElement xmlDomElement) {
    QString recContainment =XmlUtils::readText(xmlDomElement, "TextContainment");
    QString recFixes =XmlUtils::readText(xmlDomElement, "TextFixes");
    QString recRestore =XmlUtils::readText(xmlDomElement, "TextRestore");
    quint32 recId = XmlUtils::readint(xmlDomElement, "id");
    QList<quint32> scenaryIds = XmlUtils::readUints(xmlDomElement, "Scenario");
    return SecurityRecommendations(recId, recContainment, recFixes, recRestore,scenaryIds);
}

SecurityScenario XMLHelper::readSecurityScenario(QDomElement xmlDomElement) {
    QString scenarioTitle =XmlUtils::readText(xmlDomElement, "Text");
    QString scenarioName =XmlUtils::readText(xmlDomElement, "Name");
    quint32 scenarioId = XmlUtils::readint(xmlDomElement, "id");
    QList<quint32> incidentIds = XmlUtils::readUints(xmlDomElement, "Incident");
    return SecurityScenario(scenarioId, scenarioTitle, scenarioName, incidentIds);
}
