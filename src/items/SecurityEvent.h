#ifndef SECURITYEVENT_H
#define SECURITYEVENT_H

#include <QObject>

/**
 * @brief The SecurityEvent class - Data-class, описывающий
 * понятие события информационной безопасности
 *
 * Например, это отключение сети, НСД или попытка взлома.
 */
class SecurityEvent : public QObject {

    Q_OBJECT

    private:
        ///Цифровой целочисленный ID для однозначной идентификации и учёта объекта
        quint32 id;
        ///Текстовое описание события, задаваемое администратором
        QString text;

    public:
        /**
         * @brief SecurityEvent - базовый конструктор по умолчанию
         * Он необходим для того, чтобы объект можно было хранить
         * в контейнерах Qlist, QMap и т.д
         */
        SecurityEvent();

        /**
         * @brief SecurityEvent - конструктор копирования объектов
         * Достаточно часто неявно вызывается, особенно при передаче
         * в функцию в качестве параметра и т.д
         * @param other - объект, используемый как источник данных
         */
        SecurityEvent(const SecurityEvent& copy);

        /**
         * @brief SecurityEvent
         * @param id - Цифровой целочисленный ID для однозначной идентификации и учёта объекта
         * @param text - Текстовое описание события, задаваемое администратором
         * @param parent - родительский объект в иерархии Qt.
         * Выстраиваение древовидной структуры объектов помогает потом не терять память
         * из-за встроенного в Qt garbage collector.
         * (когда вызывается деструктор родительского объекта,
         * вызовется деструктор дочерних объектов)
         */
        SecurityEvent(quint32 id, QString text, QObject *parent = nullptr);

        /**
         * @brief getId - Получить ID события
         * @return
         */
        quint32 getId() const;

        /**
         * @brief getText - Получить текст события
         * @return
         */
        QString getText() const;

        /**
         * @brief operator =
         * @param other
         * @return
         */
        SecurityEvent& operator=(const SecurityEvent& other);

        /**
         * @brief operator ==
         * @param other
         * @return
         */
        bool operator==(const SecurityEvent& other) const;

        /**
         * @brief operator !=
         * @param other
         * @return
         */
        bool operator!=(const SecurityEvent& other) const;

        /**
         * @brief operator <
         * @param other
         * @return
         */
        bool operator<(const SecurityEvent& other) const;

        /**
         * @brief operator >
         * @param other
         * @return
         */
        bool operator>(const SecurityEvent& other) const;

        /**
         * @brief operator >=
         * @param other
         * @return
         */
        bool operator>=(const SecurityEvent& other) const;

        /**
         * @brief operator <=
         * @param other
         * @return
         */
        bool operator<=(const SecurityEvent& other) const;


};

#endif // SECURITYEVENT_H
