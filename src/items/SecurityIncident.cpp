#include "SecurityIncident.h"

/**
 * @brief SecurityIncident - базовый конструктор по умолчанию
 * Он необходим для того, чтобы объект можно было хранить
 * в контейнерах Qlist, QMap и т.д
 */
SecurityIncident::SecurityIncident() {

}
/**
 * @brief SecurityIncident - конструктор копирования объектов
 * @param other - объект, используемый как источник данных
 */
SecurityIncident::SecurityIncident(const SecurityIncident& other)
    : QObject(other.parent()), id(other.id), text(other.text), name(other.name), events(other.events) {

}
/**
 * @brief SecurityIncident
 * @param id - Цифровой целочисленный ID для однозначной идентификации и учёта объекта
 * @param text - Текстовое описании Инцидента ИБ, задаваемое администратором
 * @param text - Текстовое название инцидента
 * @param events - Перечень SecurityEvent информационной безопасности, которые
 * могут сигнализируют о наступлении этого инцидента
 * @param parent - родительский объект в иерархии Qt.
 */
SecurityIncident::SecurityIncident(quint32 id, QString text, QString name, QList<quint32> events, QObject *parent) : QObject(parent) {
    this->id = id;
    this->text = text;
    this->name = name;
    this->events = events;
}
/**
 * @brief getId - Получить ID инцидента
 * @return
 */
quint32 SecurityIncident::getId() const {
    return this->id;
}
/**
 * @brief getText - Получить текст инцидента
 * @return
 */
QString SecurityIncident::getText() const {
    return this->text;
}
/**
 * @brief getName - Получить название инцидента
 * @return
 */
QString SecurityIncident::getName() const {
    return this->name;
}
/**
 * @brief getEventIds - Получить список событий ИБ,
 * которые могут согнализируют о наструплении этого инцидента
 * @return
 */
QList<quint32> SecurityIncident::getEventIds() const {
    return this->events;
}

/**
 * @brief setText - Установить текст инцидента
 * @return
 */
void SecurityIncident::setText(QString const text) {
    this->text = text;
}

/**
 * @brief setName - Установить название инцидента
 * @return
 */
void SecurityIncident::setName(QString const name) {
    this->name = name;
}

/**
 * @brief setID - Установить ID инцидента
 * @return
 */
void SecurityIncident::setID(quint32 const id) {
    this->id = id;
}

/**
 * @brief setIDEvents - Установить ID ивентов
 * @return
 */
void SecurityIncident::setIDEvents(QList<quint32> const events) {
    this->events = events;
}

/**
 * @brief operator =
 * @param other
 * @return
 */
SecurityIncident& SecurityIncident::operator=(const SecurityIncident& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    id = other.id;
    text = other.text;
    name = other.name;
    events = other.events;

    return *this;
}

/**
 * @brief operator ==
 * @param other
 * @return
 */
bool SecurityIncident::operator==(const SecurityIncident& other) const {
    return (id == other.id
         && text == other.text
         && name == other.name
         && events == other.events);
}

/**
 * @brief operator !=
 * @param other
 * @return
 */
bool SecurityIncident::operator!=(const SecurityIncident& other) const {
    return !(*this == other);
}

/**
 * @brief operator <
 * @param other
 * @return
 */
bool SecurityIncident::operator<(const SecurityIncident& other) const {
    return !(*this > other);
}

/**
 * @brief operator >
 * @param other
 * @return
 */
bool SecurityIncident::operator>(const SecurityIncident& other) const {
    return this->id > other.id;
}

/**
 * @brief operator >=
 * @param other
 * @return
 */
bool SecurityIncident::operator>=(const SecurityIncident& other) const {
    return !(*this < other);
}

/**
 * @brief operator <=
 * @param other
 * @return
 */
bool SecurityIncident::operator<=(const SecurityIncident& other) const {
    return !(*this > other);
}
