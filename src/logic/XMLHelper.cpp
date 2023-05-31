#include "XMLHelper.h"
#include "src/logic/XmlUtils.h"

XMLHelper::XMLHelper(QObject *parent) : QObject(parent) {

}

Database readDatabase(QString path) {

}

void writeDatabase(QString path) {

}

SecurityEvent XMLHelper::readSecurityEvent(QDomElement xmlDomElement) {
    QString eventTitle =XmlUtils::readText(xmlDomElement, "Text");
    int eventId = XmlUtils::readint(xmlDomElement, "id");
    return SecurityEvent(eventId, eventTitle);
}

SecurityEventCategory XMLHelper::readSecurityEventCategory(QDomElement xmlDomElement) {

}

SecurityIncident XMLHelper::readSecurityIncident(QDomElement xmlDomElement) {
    QString incidentTitle =XmlUtils::readText(xmlDomElement, "Text");
    int incidentId = XmlUtils::readint(xmlDomElement, "id");
    return SecurityIncident(incidentId, incidentTitle);
}

SecurityRecommendations XMLHelper::readSecurityRecommendations(QDomElement xmlDomElement) {
    QString recContainment =XmlUtils::readText(xmlDomElement, "TextContainment");
    QString recFixes =XmlUtils::readText(xmlDomElement, "TextFixes");
    QString recRestore =XmlUtils::readText(xmlDomElement, "TextRestore");
    int recId = XmlUtils::readint(xmlDomElement, "id");
    return SecurityRecommendations(recId, recContainment, recFixes, recRestore);
}

SecurityScenario XMLHelper::readSecurityScenario(QDomElement xmlDomElement) {
    QString scenarioTitle =XmlUtils::readText(xmlDomElement, "Text");
    int scenarioId = XmlUtils::readint(xmlDomElement, "id");
    return SecurityScenario(scenarioId, scenarioTitle);
}
