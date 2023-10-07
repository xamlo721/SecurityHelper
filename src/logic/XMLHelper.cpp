#include "XMLHelper.h"
#include "src/logic/XmlUtils.h"
#include <QMap>

XMLHelper::XMLHelper(QObject *parent) : QObject(parent) {

}

Database XMLHelper::readDatabase(QString path) {

    QString pathToStockDatabase = "../SecurityHelper/rss/StockDatabase/";

    { //Если не найдены файлы в основной базе, то запуск идет с резервной
        if (!XmlUtils::checkFile(path + "Events.xml")) {
            if (!XmlUtils::checkFile(pathToStockDatabase + "Events.xml")) {
                throw std::runtime_error(QString("[XMLHelper] Error! Cannot load Events.xml!").toLocal8Bit().constData());
            }
            return XMLHelper::readDatabase(pathToStockDatabase);
        }
        if (!XmlUtils::checkFile(path + "Categories.xml")) {
            if (!XmlUtils::checkFile(pathToStockDatabase + "Categories.xml")) {
                throw std::runtime_error(QString("[XMLHelper] Error! Cannot load Categories.xml!").toLocal8Bit().constData());
            }
            return XMLHelper::readDatabase(pathToStockDatabase);
        }
        if (!XmlUtils::checkFile(path + "Incidents.xml")) {
            if (!XmlUtils::checkFile(pathToStockDatabase + "Incidents.xml")) {
                throw std::runtime_error(QString("[XMLHelper] Error! Cannot load Incidents.xml!").toLocal8Bit().constData());
            }
            return XMLHelper::readDatabase(pathToStockDatabase);
        }
        if (!XmlUtils::checkFile(path + "Recommendations.xml")) {
            if (!XmlUtils::checkFile(pathToStockDatabase + "Recommendations.xml")) {
                throw std::runtime_error(QString("[XMLHelper] Error! Cannot load Recommendations.xml!").toLocal8Bit().constData());
            }
            return XMLHelper::readDatabase(pathToStockDatabase);
        }
        if (!XmlUtils::checkFile(path + "Scenaries.xml")) {
            if (!XmlUtils::checkFile(pathToStockDatabase + "Scenaries.xml")) {
                throw std::runtime_error(QString("[XMLHelper] Error! Cannot load Scenaries.xml!").toLocal8Bit().constData());
            }
            return XMLHelper::readDatabase(pathToStockDatabase);
        }
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

void XMLHelper::writeDatabase(QString path/*, QList<SecurityEvent> eventsList, //Закомитил так как нет еще приходящих данных, сказать Krock если они появятся :^)
                                 QList<SecurityEventCategory> categoriesList,
                                 QList<SecurityIncident> incidentsList,
                                 QList<SecurityRecommendations> recommendationsList,
                                 QList<SecurityScenario> scenariesList*/) {

    Database database = XMLHelper::savedDatabase(/*QList<SecurityEvent> eventsList, //Закомитил так как нет еще приходящих данных, сказать Krock если они появятся :^)
                                 QList<SecurityEventCategory> categoriesList,
                                 QList<SecurityIncident> incidentsList,
                                 QList<SecurityRecommendations> recommendationsList,
                                 QList<SecurityScenario> scenariesList*/);

    XMLHelper::writeDatabaseEvent(path, database);

    XMLHelper::writeDatabaseCategory(path, database);

    XMLHelper::writeDatabaseIncidents(path, database);

    XMLHelper::writeDatabaseRecommendation(path, database);

    XMLHelper::writeDatabaseScenaries(path, database);
}

void XMLHelper::writeDatabaseEvent(QString path, Database database) {
    QFile eventsFile(path + "Events.xml");
    eventsFile.open(QFile::WriteOnly | QFile::Text);
    QDomDocument eventsDoc;
    XmlUtils::writeXMLHeader(&eventsDoc);

    QDomElement eventsElement = XmlUtils::writeXMLStructTree(&eventsDoc, "Events");

    for (SecurityEvent event : database.events.values()) {
        QDomElement eventElement = eventsDoc.createElement("Event");
        XmlUtils::writeUint(eventsDoc, eventElement , "id", event.getId());
        XmlUtils::writeText(eventsDoc, eventElement , "Text", event.getText());
        eventsElement.appendChild(eventElement);
    }
    XMLHelper::writeToXMLFile(&eventsFile, eventsDoc, "UTF-8");
    eventsFile.close();
}

void XMLHelper::writeDatabaseCategory(QString path, Database database) {
    QFile categoriesFile(path + "Categories.xml");
    categoriesFile.open(QFile::WriteOnly | QFile::Text);
    QDomDocument eventsDoc;
    XmlUtils::writeXMLHeader(&eventsDoc);

    QDomElement categoriesElement = XmlUtils::writeXMLStructTree(&eventsDoc, "Categories");

    for (SecurityEventCategory event : database.categories.values()) {
        QDomElement eventElement = eventsDoc.createElement("Category");
        XmlUtils::writeUint(eventsDoc, eventElement , "id", event.getId());
        XmlUtils::writeText(eventsDoc, eventElement , "Text", event.getText());
        XmlUtils::writeUints(eventsDoc, eventElement , "events", event.getEventIds());
        categoriesElement.appendChild(eventElement);
    }
    XMLHelper::writeToXMLFile(&categoriesFile, eventsDoc, "UTF-8");
    categoriesFile.close();
}

void XMLHelper::writeDatabaseIncidents(QString path, Database database) {
    QFile incidentsFile(path + "Incidents.xml");
    incidentsFile.open(QFile::WriteOnly | QFile::Text);
    QDomDocument eventsDoc;
    XmlUtils::writeXMLHeader(&eventsDoc);

    QDomElement incidentsElement = XmlUtils::writeXMLStructTree(&eventsDoc, "Incidents");

    for (SecurityIncident event : database.incidents.values()) {
        QDomElement eventElement = eventsDoc.createElement("Incident");
        XmlUtils::writeUint(eventsDoc, eventElement , "id", event.getId());
        XmlUtils::writeText(eventsDoc, eventElement , "Name", event.getName());
        XmlUtils::writeText(eventsDoc, eventElement , "Text", event.getText());
        XmlUtils::writeUints(eventsDoc, eventElement , "events", event.getEventIds());
        incidentsElement.appendChild(eventElement);
    }
    XMLHelper::writeToXMLFile(&incidentsFile, eventsDoc, "UTF-8");
    incidentsFile.close();
}

void XMLHelper::writeDatabaseRecommendation(QString path, Database database) {
    QFile recommendationsFile(path + "Recommendations.xml");
    recommendationsFile.open(QFile::WriteOnly | QFile::Text);
    QDomDocument eventsDoc;
    XmlUtils::writeXMLHeader(&eventsDoc);

    QDomElement recommendationsElement = XmlUtils::writeXMLStructTree(&eventsDoc, "Recommendations");

    for (SecurityRecommendations event : database.recommendations.values()) {
        QDomElement eventElement = eventsDoc.createElement("Recommendation");
        XmlUtils::writeUint(eventsDoc, eventElement , "id", event.getId());
        XmlUtils::writeText(eventsDoc, eventElement , "TextContainment", event.getTextContainment());
        XmlUtils::writeText(eventsDoc, eventElement , "TextFixes", event.getTextFixes());
        XmlUtils::writeText(eventsDoc, eventElement , "TextRestore", event.getTextRestore());
        XmlUtils::writeUints(eventsDoc, eventElement , "Scenario", event.getScenaries());
        recommendationsElement.appendChild(eventElement);
    }
    XMLHelper::writeToXMLFile(&recommendationsFile, eventsDoc, "UTF-8");
    recommendationsFile.close();
}

void XMLHelper::writeDatabaseScenaries(QString path, Database database) {
    QFile scenariesFile(path + "Scenaries.xml");
    scenariesFile.open(QFile::WriteOnly | QFile::Text);
    QDomDocument eventsDoc;
    XmlUtils::writeXMLHeader(&eventsDoc);

    QDomElement scenariesElement = XmlUtils::writeXMLStructTree(&eventsDoc, "Scenaries");

    for (SecurityScenario event : database.scenaries.values()) {
        QDomElement eventElement = eventsDoc.createElement("Scenary");
        XmlUtils::writeUint(eventsDoc, eventElement , "id", event.getId());
        XmlUtils::writeText(eventsDoc, eventElement , "Name", event.getName());
        XmlUtils::writeText(eventsDoc, eventElement , "Text", event.getText());
        XmlUtils::writeUints(eventsDoc, eventElement , "Incident", event.getIncidents());
        scenariesElement.appendChild(eventElement);
    }
    XMLHelper::writeToXMLFile(&scenariesFile, eventsDoc, "UTF-8");
    scenariesFile.close();
}

Database XMLHelper::savedDatabase(/*QList<SecurityEvent> eventsList, //Закомитил так как нет еще приходящих данных, сказать Krock если они появятся :^)
                                 QList<SecurityEventCategory> categoriesList,
                                 QList<SecurityIncident> incidentsList,
                                 QList<SecurityRecommendations> recommendationsList,
                                 QList<SecurityScenario> scenariesList*/) {

    Database db = XMLHelper::readDatabase("../SecurityHelper/storage/");


    /* //Закомитил так как нет еще приходящих данных, сказать Krock если они появятся :^)
    QMap<quint32, SecurityEvent> events = XMLHelper::savedDatabaseEvent(eventsList);
    QMap<quint32, SecurityEventCategory> categories = XMLHelper::savedDatabaseCategory;
    QMap<quint32, SecurityIncident> incidents = XMLHelper::savedDatabaseIncident;
    QMap<quint32, SecurityRecommendations> recommendations = XMLHelper::savedDatabaseRecommendations;
    QMap<quint32, SecurityScenario> scenaries = XMLHelper::savedDatabaseScenario;

    return dataBase(events, categories, incidents, recommendations, scenaries); */
    return db;
}

QMap<quint32, SecurityEvent> XMLHelper::savedDatabaseEvent(QList<SecurityEvent> eventsList) {
    QMap<quint32, SecurityEvent> events;
    for(SecurityEvent event : eventsList) {
        events.insert(event.getId(), event);
    }
    return events;
}

QMap<quint32, SecurityEventCategory> XMLHelper::savedDatabaseCategory(QList<SecurityEventCategory> categoriesList) {
    QMap<quint32, SecurityEventCategory> categories;
    for(SecurityEventCategory category : categoriesList) {
        categories.insert(category.getId(), category);
    }
    return categories;
}

QMap<quint32, SecurityIncident> XMLHelper::savedDatabaseIncident(QList<SecurityIncident> incidentsList) {
    QMap<quint32, SecurityIncident> incidents;
    for(SecurityIncident incident : incidentsList) {
        incidents.insert(incident.getId(), incident);
    }
    return incidents;
}

QMap<quint32, SecurityRecommendations> XMLHelper::savedDatabaseRecommendations(QList<SecurityRecommendations> recommendationsList) {
    QMap<quint32, SecurityRecommendations> recommendations;
    for(SecurityRecommendations recommendation : recommendationsList) {
        recommendations.insert(recommendation.getId(), recommendation);
    }
    return recommendations;
}

QMap<quint32, SecurityScenario> XMLHelper::savedDatabaseScenario(QList<SecurityScenario> scenariesList) {
    QMap<quint32, SecurityScenario> scenaries;
    for(SecurityScenario scenary : scenariesList) {
        scenaries.insert(scenary.getId(), scenary);
    }
    return scenaries;
}

bool XMLHelper::writeToXMLFile(QFile* file, QDomDocument document, QString codec) {
    if (file->isOpen()) {
        QTextStream writer(file);
        writer.setCodec(QTextCodec::codecForName(codec.toStdString().data()));
        document.save(writer, 4);
        return true;
    } else {
        qDebug()<<file->errorString();
        return false;
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
