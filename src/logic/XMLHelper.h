#ifndef XMLHELPER_H
#define XMLHELPER_H

#include <QObject>
#include <QFile>
#include <QList>
#include <QTextStream>
#include <QTextCodec>

#include <QDebug>

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

        static SecurityEvent readSecurityEvent(QDomElement xmlDomElement);

        static SecurityEventCategory readSecurityEventCategory(QDomElement xmlDomElement);

        static SecurityIncident readSecurityIncident(QDomElement xmlDomElement);

        static SecurityRecommendations readSecurityRecommendations(QDomElement xmlDomElement);

        static SecurityScenario readSecurityScenario(QDomElement xmlDomElement);

        /**
         * @brief writeDatabase - функция сохранения данных в .xml формате
         * @param path - путь до папки сохранения
         **/
        static void writeDatabase(QString path/*, QList<SecurityEvent> eventsList, //Закомитил так как нет еще приходящих данных, сказать Krock если они появятся :^)
                                 QList<SecurityEventCategory> categoriesList,
                                 QList<SecurityIncident> incidentsList,
                                 QList<SecurityRecommendations> recommendationsList,
                                 QList<SecurityScenario> scenariesList*/);
        ///writeDatabaseEvent - функция записи в определенный и конкретный файл(Events.xml)
        static void writeDatabaseEvent(QString path, QMap<quint32, SecurityEvent> events);
        ///writeDatabaseCategory - функция записи в определенный и конкретный файл(Categories.xml)
        static void writeDatabaseCategory(QString path, QMap<quint32, SecurityEventCategory> categories);
        ///writeDatabaseIncidents - функция записи в определенный и конкретный файл(Incidents.xml)
        static void writeDatabaseIncidents(QString path, QMap<quint32, SecurityIncident> incidents);
        ///writeDatabaseRecommendation - функция записи в определенный и конкретный файл(Recommendations.xml)
        static void writeDatabaseRecommendation(QString path, QMap<quint32, SecurityRecommendations> recommendations);
        ///writeDatabaseScenaries - функция записи в определенный и конкретный файл(Scenaries.xml)
        static void writeDatabaseScenaries(QString path, QMap<quint32, SecurityScenario> scenaries);

        /**
         * @brief writeToXMLFile - функция непосредственной записи в файл
         * @param file - файл открываемый для записи
         * @param document - данные, которое нужно записать
         * @param codec - кодировка
         **/
        static bool writeToXMLFile(QFile* file, QDomDocument document, QString codec = "UTF-8");

        /**
         * @brief savedDatabase - функция преобразования QList-ов с данными в Database
         * @brief этот метод вызывает savedDatabaseEvent, savedDatabaseCategory, savedDatabaseIncident, savedDatabaseRecommendations, savedDatabaseScenario
         * @param QList<SecurityEvent> eventsList - лист с ивентами
         * @param QList<SecurityEventCategory> categoriesList - лист с категориями
         * @param QList<SecurityIncident> incidentsList - лист с инцидентами
         * @param QList<SecurityRecommendations> recommendationsList - лист с рекомендациями
         * @param QList<SecurityScenario> scenariesList - лист со сценариями
         **/
        static Database savedDatabase(/*QList<SecurityEvent> eventsList, QList<SecurityEventCategory> categoriesList, //Закомитил так как нет еще приходящих данных, сказать Krock если они появятся :^)
                              QList<SecurityIncident> incidentsList, QList<SecurityRecommendations> recommendationsList,
                              QList<SecurityScenario> scenariesList*/);
        ///savedDatabaseEvent - функция преобразования QList с ивентами в QMap
        static QMap<quint32, SecurityEvent> savedDatabaseEvent(QList<SecurityEvent> eventsList);
        ///savedDatabaseCategory - функция преобразования QList с категориями в QMap
        static QMap<quint32, SecurityEventCategory> savedDatabaseCategory(QList<SecurityEventCategory> categoriesList);
        ///savedDatabaseIncident - функция преобразования QList с инцидентами в QMap
        static QMap<quint32, SecurityIncident> savedDatabaseIncident(QList<SecurityIncident> incidentsList);
        ///savedDatabaseRecommendations - функция преобразования QList с ркомендациями в QMap
        static QMap<quint32, SecurityRecommendations> savedDatabaseRecommendations(QList<SecurityRecommendations> recommendationsList);
        ///savedDatabaseScenario - функция преобразования QList со сценариями в QMap
        static QMap<quint32, SecurityScenario> savedDatabaseScenario(QList<SecurityScenario> scenariesList);



    signals:

};

#endif // XMLHELPER_H
