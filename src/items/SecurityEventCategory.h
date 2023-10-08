#ifndef SECURITY_EVENT_CATEGORY_H
#define SECURITY_EVENT_CATEGORY_H

#include <QObject>

/**
 * @brief The SecurityEventCategory class - Data-class для описания
 * понятия Категории событий информационной безопаности
 *
 * По сути это как папка для событий
 */
class SecurityEventCategory : public QObject {

    Q_OBJECT

    private:
        ///Цифровой целочисленный ID для однозначной идентификации и учёта объекта
        quint32 id;
        ///Текстовое название категории событий, задаваемое администратором
        QString text;
        ///Перечень ID событий, входящих в эту категорию
        //TODO: Выяснить, может ли событие быть в нескольких категориях
        QList<quint32> events;

    public:

        /**
         * @brief SecurityEventCategory - базовый конструктор по умолчанию
         * Он необходим для того, чтобы объект можно было хранить
         * в контейнерах Qlist, QMap и т.д
         */
        SecurityEventCategory();

        /**
         * @brief SecurityEvent - конструктор копирования объектов
         * Достаточно часто неявно вызывается, особенно при передаче
         * в функцию в качестве параметра и т.д
         * @param other - объект, используемый как источник данных
         */
        SecurityEventCategory(const SecurityEventCategory& other);

        /**
         * @brief SecurityEventCategory
         * @param id - Цифровой целочисленный ID для однозначной идентификации и учёта объекта
         * @param text - Текстовое название категории событий, задаваемое администратором
         * @param events - Перечень ID событий, входящих в эту категорию
         * @param parent - родительский объект в иерархии Qt
         */
        SecurityEventCategory(quint32 id, QString text, QList<quint32> events, QObject *parent = nullptr);

        /**
         * @brief getId - Получить ID категории
         * @return
         */
        quint32 getId() const;

        /**
         * @brief getText - Получить название категории
         * @return
         */
        QString getText() const;

        /**
         * @brief getEventIds - Получить перечень ID событий, входящих в эту категорию
         * @return
         */
        QList<quint32> getEventIds() const;

        /**
         * @brief setText - Установить название категории
         * @return
         */
        void setText(QString const text);

        /**
         * @brief setID - Установить ID категории
         * @return
         */
        void setID(quint32 const id);

        /**
         * @brief setIDEvents - Установить ID категории
         * @return
         */
        void setIDEvents(QList<quint32> const events);

        /**
         * @brief operator =
         * @param other
         * @return
         */
        SecurityEventCategory& operator=(const SecurityEventCategory& other);

        /**
         * @brief operator ==
         * @param other
         * @return
         */
        bool operator==(const SecurityEventCategory& other) const;

        /**
         * @brief operator !=
         * @param other
         * @return
         */
        bool operator!=(const SecurityEventCategory& other) const;

        /**
         * @brief operator <
         * @param other
         * @return
         */
        bool operator<(const SecurityEventCategory& other) const;

        /**
         * @brief operator >
         * @param other
         * @return
         */
        bool operator>(const SecurityEventCategory& other) const;

        /**
         * @brief operator >=
         * @param other
         * @return
         */
        bool operator>=(const SecurityEventCategory& other) const;

        /**
         * @brief operator <=
         * @param other
         * @return
         */
        bool operator<=(const SecurityEventCategory& other) const;


};

#endif // SECURITY_EVENT_CATEGORY_H
