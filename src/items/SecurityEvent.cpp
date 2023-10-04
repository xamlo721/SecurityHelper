#include "SecurityEvent.h"

/**
 * @brief SecurityEvent - базовый конструктор по умолчанию
 * Он необходим для того, чтобы объект можно было хранить
 * в контейнерах Qlist, QMap и т.д
 */
SecurityEvent::SecurityEvent() {
    this->id = 0;
}

/**
 * @brief SecurityEvent - конструктор копирования объектов
 * Достаточно часто неявно вызывается, особенно при передаче
 * в функцию в качестве параметра и т.д
 * @param other - объект, используемый как источник данных
 */
SecurityEvent::SecurityEvent(quint32 id, QString text, QObject *parent) : QObject(parent) {
    this->id = id;
    this->text = text;
}

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
SecurityEvent::SecurityEvent(const SecurityEvent& copy)
    : QObject(copy.parent()), id(copy.id), text(copy.text) {
    //NO-OP
}

/**
 * @brief getId - Получить ID события
 * @return
 */
quint32 SecurityEvent::getId()  const{
    return this->id;
}

/**
 * @brief getText - Получить текст события
 * @return
 */
QString SecurityEvent::getText()  const{
    return this->text;
}

/**
 * @brief setText - Установить название события
 * @return
 */
void SecurityEvent::setText(QString const text) {
    this->text = text;
}


/**
 * @brief operator =
 * @param other
 * @return
 */
SecurityEvent& SecurityEvent::operator=(const SecurityEvent& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    id = other.id;
    text = other.text;

    return *this;
}

/**
 * @brief operator ==
 * @param other
 * @return
 */
bool SecurityEvent::operator==(const SecurityEvent& other) const {
    return (id == other.id
         && text == other.text);
}

/**
 * @brief operator !=
 * @param other
 * @return
 */
bool SecurityEvent::operator!=(const SecurityEvent& other) const {
    return !(*this == other);
}

/**
 * @brief operator <
 * @param other
 * @return
 */
bool SecurityEvent::operator<(const SecurityEvent& other) const {
    return !(*this > other);
}

/**
 * @brief operator >
 * @param other
 * @return
 */
bool SecurityEvent::operator>(const SecurityEvent& other) const {
    return this->id > other.id;
}

/**
 * @brief operator >=
 * @param other
 * @return
 */
bool SecurityEvent::operator>=(const SecurityEvent& other) const {
    return !(*this < other);
}

/**
 * @brief operator <=
 * @param other
 * @return
 */
bool SecurityEvent::operator<=(const SecurityEvent& other) const {
    return !(*this > other);
}

