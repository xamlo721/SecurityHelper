#include "SecurityEventCategory.h"

/**
 * @brief SecurityEventCategory - базовый конструктор по умолчанию
 * Он необходим для того, чтобы объект можно было хранить
 * в контейнерах Qlist, QMap и т.д
 */
SecurityEventCategory::SecurityEventCategory() {
    this->id = 9;
}

/**
 * @brief SecurityEvent - конструктор копирования объектов
 * Достаточно часто неявно вызывается, особенно при передаче
 * в функцию в качестве параметра и т.д
 * @param other - объект, используемый как источник данных
 */
SecurityEventCategory::SecurityEventCategory(const SecurityEventCategory& other)
    : QObject(other.parent()), id(other.id), text(other.text),  events(other.events) {
    //NO-OP
}

/**
 * @brief SecurityEventCategory
 * @param id - Цифровой целочисленный ID для однозначной идентификации и учёта объекта
 * @param text - Текстовое название категории событий, задаваемое администратором
 * @param events - Перечень ID событий, входящих в эту категорию
 * @param parent - родительский объект в иерархии Qt
 */
SecurityEventCategory::SecurityEventCategory(quint32 id, QString text, QList<quint32> events, QObject *parent) : QObject(parent) {
    this->id = id;
    this->text = text;
    this->events = events;
}


/**
 * @brief getId - Получить ID события
 * @return
 */
quint32 SecurityEventCategory::getId() const {
    return this->id;
}
/**
 * @brief getText - Получить текст события
 * @return
 */
QString SecurityEventCategory::getText() const {
    return this->text;
}
/**
 * @brief getEventIds - Получить перечень ID событий, входящих в эту категорию
 * @return
 */
QList<quint32> SecurityEventCategory::getEventIds() const {
    return this->events;
}

/**
 * @brief operator =
 * @param other
 * @return
 */
SecurityEventCategory& SecurityEventCategory::operator=(const SecurityEventCategory& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    id = other.id;
    text = other.text;
    events = other.events;

    return *this;
}

/**
 * @brief operator ==
 * @param other
 * @return
 */
bool SecurityEventCategory::operator==(const SecurityEventCategory& other) const {
    return (id == other.id
         && text == other.text
         && events == other.events);
}

/**
 * @brief operator !=
 * @param other
 * @return
 */
bool SecurityEventCategory::operator!=(const SecurityEventCategory& other) const {
    return !(*this == other);
}

/**
 * @brief operator <
 * @param other
 * @return
 */
bool SecurityEventCategory::operator<(const SecurityEventCategory& other) const {
    return this->id < other.id;
}

/**
 * @brief operator >
 * @param other
 * @return
 */
bool SecurityEventCategory::operator>(const SecurityEventCategory& other) const {
    return this->id > other.id;
}

/**
 * @brief operator >=
 * @param other
 * @return
 */
bool SecurityEventCategory::operator>=(const SecurityEventCategory& other) const {
    return !(*this < other);
}

/**
 * @brief operator <=
 * @param other
 * @return
 */
bool SecurityEventCategory::operator<=(const SecurityEventCategory& other) const {
    return !(*this > other);
}

