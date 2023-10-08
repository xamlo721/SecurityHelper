#ifndef SECURITYINCIDENT_H
#define SECURITYINCIDENT_H

#include <QObject>

/**
 * @brief The SecurityIncident class - Data-class, описывающий
 * понятие инцидента в сфере ИБ
 */
class SecurityIncident : public QObject {

    Q_OBJECT

    private:
        ///Цифровой целочисленный ID для однозначной идентификации и учёта объекта
        quint32 id;
        ///Текстовое описании Инцидента ИБ, задаваемое администратором
        QString text;
        QString name;
        ///Перечень SecurityEvent информационной безопасности, которые
        /// могут сигнализируют о наступлении этого инцидента
        QList<quint32> events;

    public:
        /**
         * @brief SecurityIncident - базовый конструктор по умолчанию
         * Он необходим для того, чтобы объект можно было хранить
         * в контейнерах Qlist, QMap и т.д
         */
        SecurityIncident();

        /**
         * @brief SecurityIncident - конструктор копирования объектов
         * @param other - объект, используемый как источник данных
         */
        SecurityIncident(const SecurityIncident& other);

        /**
         * @brief SecurityIncident
         * @param id - Цифровой целочисленный ID для однозначной идентификации и учёта объекта
         * @param text - Текстовое описании Инцидента ИБ, задаваемое администратором
         * @param name - Текстовое название инцидента
         * @param events - Перечень SecurityEvent информационной безопасности, которые
         * могут сигнализируют о наступлении этого инцидента
         * @param parent - родительский объект в иерархии Qt.
         */
        SecurityIncident(quint32 id, QString text, QString name, QList<quint32> events, QObject *parent = nullptr);

        /**
         * @brief getId - Получить ID инцидента
         * @return
         */
        quint32 getId();

        /**
         * @brief getText - Получить текст инцидента
         * @return
         */
        QString getText();

        /**
         * @brief getName - Получить название инцидента
         * @return
         */
        QString getName();

        /**
         * @brief getEventIds - Получить список событий ИБ,
         * которые могут согнализируют о наструплении этого инцидента
         * @return
         */
        QList<quint32> getEventIds();

        /**
         * @brief setText - Установить текст инцидента
         * @return
         */
        void setText(QString const text);

        /**
         * @brief setName - Установить название инцидента
         * @return
         */
        void setName(QString const name);

        /**
         * @brief setID - Установить ID инцидента
         * @return
         */
        void setID(quint32 const id);

        /**
         * @brief setIDEvents - Установить ID ивентов
         * @return
         */
        void setIDEvents(QList<quint32> const events);

        /**
         * @brief operator =
         * @param other
         * @return
         */
        SecurityIncident& operator=(const SecurityIncident& other);

        /**
         * @brief operator ==
         * @param other
         * @return
         */
        bool operator==(const SecurityIncident& other) const;

        /**
         * @brief operator !=
         * @param other
         * @return
         */
        bool operator!=(const SecurityIncident& other) const;

        /**
         * @brief operator <
         * @param other
         * @return
         */
        bool operator<(const SecurityIncident& other) const;

        /**
         * @brief operator >
         * @param other
         * @return
         */
        bool operator>(const SecurityIncident& other) const;

        /**
         * @brief operator >=
         * @param other
         * @return
         */
        bool operator>=(const SecurityIncident& other) const;

        /**
         * @brief operator <=
         * @param other
         * @return
         */
        bool operator<=(const SecurityIncident& other) const;



};

#endif // SECURITYINCIDENT_H
