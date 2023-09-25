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
        QDomElement root = eventsDoc.createElement("Database");
        eventsDoc.appendChild(root);
        QDomElement eventsElement  = eventsDoc.createElement("Events");
        eventsDoc.appendChild(eventsElement);

        for (SecurityEvent event : database.events.values()) {
            QDomElement eventElement = eventsDoc.createElement("Event");
            XmlUtils::writeUint(eventsDoc, eventsElement , "id", event.getId());
            XmlUtils::writeText(eventsDoc, eventsElement , "Text", event.getText());
            eventsElement.appendChild(eventElement);
        }
    }

    {
        QFile categoriesFile(path + "Categories.xml");
        categoriesFile.open(QFile::WriteOnly | QFile::Text);
        QDomDocument eventsDoc;
        XmlUtils::writeXMLHeader(&eventsDoc);
        QDomElement root = eventsDoc.createElement("Database");
        eventsDoc.appendChild(root);
        QDomElement categoriesElement  = eventsDoc.createElement("Categories");
        eventsDoc.appendChild(categoriesElement);

        for (SecurityEventCategory event : database.categories.values()) {
            QDomElement eventElement = eventsDoc.createElement("Category");
            XmlUtils::writeUint(eventsDoc, categoriesElement , "id", event.getId());
            XmlUtils::writeText(eventsDoc, categoriesElement , "Text", event.getText());
            XmlUtils::writeUints(eventsDoc, categoriesElement , "events", event.getEventIds());
            categoriesElement.appendChild(eventElement);
        }
    }

    {
        QFile incidentsFile(path + "Incidents.xml");
        incidentsFile.open(QFile::WriteOnly | QFile::Text);
        QDomDocument eventsDoc;
        XmlUtils::writeXMLHeader(&eventsDoc);
        QDomElement root = eventsDoc.createElement("Database");
        eventsDoc.appendChild(root);
        QDomElement incidentsElement  = eventsDoc.createElement("Incidents");
        eventsDoc.appendChild(incidentsElement);

        for (SecurityIncident event : database.incidents.values()) {
            QDomElement eventElement = eventsDoc.createElement("Incident");
            XmlUtils::writeUint(eventsDoc, incidentsElement , "id", event.getId());
            XmlUtils::writeText(eventsDoc, incidentsElement , "Name", event.getName());
            XmlUtils::writeText(eventsDoc, incidentsElement , "Text", event.getText());
            XmlUtils::writeUints(eventsDoc, incidentsElement , "events", event.getEventIds());
            incidentsElement.appendChild(eventElement);
        }
    }

    {
        QFile recommendationsFile(path + "Recommendations.xml");
        recommendationsFile.open(QFile::WriteOnly | QFile::Text);
        QDomDocument eventsDoc;
        XmlUtils::writeXMLHeader(&eventsDoc);
        QDomElement root = eventsDoc.createElement("Database");
        eventsDoc.appendChild(root);
        QDomElement recommendationsElement = eventsDoc.createElement("Recommendations");
        eventsDoc.appendChild(recommendationsElement);

        for (SecurityRecommendations event : database.recommendations.values()) {
            QDomElement eventElement = eventsDoc.createElement("Recommendation");
            XmlUtils::writeUint(eventsDoc, recommendationsElement , "id", event.getId());
            XmlUtils::writeText(eventsDoc, recommendationsElement , "TextContainment", event.getTextContainment());
            XmlUtils::writeText(eventsDoc, recommendationsElement , "TextFixes", event.getTextFixes());
            XmlUtils::writeText(eventsDoc, recommendationsElement , "TextRestore", event.getTextRestore());
            XmlUtils::writeUints(eventsDoc, recommendationsElement , "Scenario", event.getScenaries());
            recommendationsElement.appendChild(eventElement);
        }
    }

    {
        QFile scenariesFile(path + "Scenaries.xml");
        scenariesFile.open(QFile::WriteOnly | QFile::Text);
        QDomDocument eventsDoc;
        XmlUtils::writeXMLHeader(&eventsDoc);
        QDomElement root = eventsDoc.createElement("Database");
        eventsDoc.appendChild(root);
        QDomElement scenariesElement = eventsDoc.createElement("Scenaries");
        eventsDoc.appendChild(scenariesElement);

        for (SecurityScenario event : database.scenaries.values()) {
            QDomElement eventElement = eventsDoc.createElement("Scenary");
            XmlUtils::writeUint(eventsDoc, scenariesElement , "id", event.getId());
            XmlUtils::writeText(eventsDoc, scenariesElement , "Name", event.getName());
            XmlUtils::writeText(eventsDoc, scenariesElement , "Text", event.getText());
            XmlUtils::writeUints(eventsDoc, scenariesElement , "Incident", event.getIncidents());
            scenariesElement.appendChild(eventElement);
        }
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
