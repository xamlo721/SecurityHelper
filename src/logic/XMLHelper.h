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
        static void writeDatabase(QString path);

        /**
         * @brief writeToXMLFile - функция непосредственной записи в файл
         * @param file - файл открываемый для записи
         * @param document - данные, которое нужно записать
         * @param codec - кодировка
         **/
        static bool writeToXMLFile(QFile* file, QDomDocument document, QString codec = "UTF-8");

        /**
         * @brief savedDatabase - функция преобразования QList-ов с данными в Database
         * @param QList<SecurityEvent> eventsList - лист с ивентами
         * @param QList<SecurityEventCategory> categoriesList - лист с категориями
         * @param QList<SecurityIncident> incidentsList - лист с инцидентами
         * @param QList<SecurityRecommendations> recommendationsList - лист с рекомендациями
         * @param QList<SecurityScenario> scenariesList - лист со сценариями
         **/
        static Database savedDatabase(/*QList<SecurityEvent> eventsList, QList<SecurityEventCategory> categoriesList, //Закомитил так как нет еще приходящих данных, сказать Krock если они появятся :^)
                              QList<SecurityIncident> incidentsList, QList<SecurityRecommendations> recommendationsList,
                              QList<SecurityScenario> scenariesList*/);

    signals:

};

#endif // XMLHELPER_H
