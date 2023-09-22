#ifndef SECURITYSCENARIO_H
#define SECURITYSCENARIO_H

#include <QObject>
#include <QList>

/**
 * @brief The SecurityScenario class - Data-class описыващий
 * понятие сценария развития событий ИБ
 */
class SecurityScenario : public QObject {

    Q_OBJECT

    private:
        ///Цифровой целочисленный ID для однозначной идентификации и учёта объекта
        quint32 id;
        ///Текстовое описании Сценария ИБ, задаваемое администратором
        QString text;
        QString name;
        ///Перечень SecurityIncident информационной безопасности, которые
        /// могут  привести к указанному сценарию
        QList<quint32> incidents;

    public:
        /**
         * @brief SecurityScenario - базовый конструктор по умолчанию
         * Он необходим для того, чтобы объект можно было хранить
         * в контейнерах Qlist, QMap и т.д
         */
        SecurityScenario();
        /**
         * @brief SecurityScenario - конструктор копирования объектов
         * @param other - объект, используемый как источник данных
         */
        SecurityScenario(const SecurityScenario& other);

        /**
         * @brief SecurityScenario
         * @param id - Цифровой целочисленный ID для однозначной идентификации и учёта объекта
         * @param text - Текстовое описании Инцидента ИБ, задаваемое администратором
         * @param name - Текстовое название сценария
         * @param incidents - Перечень SecurityIncident информационной безопасности, которые
         * могут  привести к указанному сценарию
         * @param parent
         */
        SecurityScenario(quint32 id, QString text, QString name, QList<quint32> incidents, QObject *parent = nullptr);

        /**
         * @brief getId - Получить ID сценария
         * @return
         */
        quint32 getId();

        /**
         * @brief getText - Получить текст Сценария
         * @return
         */
        QString getText();

        /**
         * @brief getName - Получить название Сценария
         * @return
         */
        QString getName();


        /**
         * @brief getIncidents - Получить список инцидентов ИБ,
         * которые могут приветси к развитию этого сценария
         * @return
         */
        QList<quint32> getIncidents();


        /**
         * @brief operator =
         * @param other
         * @return
         */
        SecurityScenario& operator=(const SecurityScenario& other);

        /**
         * @brief operator ==
         * @param other
         * @return
         */
        bool operator==(const SecurityScenario& other) const;

        /**
         * @brief operator !=
         * @param other
         * @return
         */
        bool operator!=(const SecurityScenario& other) const;

        /**
         * @brief operator <
         * @param other
         * @return
         */
        bool operator<(const SecurityScenario& other) const;

        /**
         * @brief operator >
         * @param other
         * @return
         */
        bool operator>(const SecurityScenario& other) const;

        /**
         * @brief operator >=
         * @param other
         * @return
         */
        bool operator>=(const SecurityScenario& other) const;

        /**
         * @brief operator <=
         * @param other
         * @return
         */
        bool operator<=(const SecurityScenario& other) const;

};

#endif // SECURITYSCENARIO_H
