#include "SecurityScenario.h"

/**
 * @brief SecurityScenario - базовый конструктор по умолчанию
 * Он необходим для того, чтобы объект можно было хранить
 * в контейнерах Qlist, QMap и т.д
 */
SecurityScenario::SecurityScenario() {

}

/**
 * @brief SecurityScenario - конструктор копирования объектов
 * @param other - объект, используемый как источник данных
 */
SecurityScenario::SecurityScenario(const SecurityScenario& other)
    : QObject(other.parent()), id(other.id), text(other.text), name(other.name), incidents(other.incidents){
    //NO-OP
}

/**
 * @brief SecurityScenario
 * @param id - Цифровой целочисленный ID для однозначной идентификации и учёта объекта
 * @param text - Текстовое описании Инцидента ИБ, задаваемое администратором
 * @param name - Текстовое название сценария
 * @param incidents - Перечень SecurityIncident информационной безопасности, которые
 * могут  привести к указанному сценарию
 * @param parent
 */
SecurityScenario::SecurityScenario(quint32 id, QString text, QString name, QList<quint32> incidents, QObject *parent) : QObject(parent) {
    this->id = id;
    this->text = text;
    this->name = name;
    this->incidents = incidents;
}

/**
 * @brief getId - Получить ID сценария
 * @return
 */
quint32 SecurityScenario::getId() const {
    return this->id;
}

/**
 * @brief getText - Получить текст Сценария
 * @return
 */
QString SecurityScenario::getText() const {
    return this->text;
}

/**
 * @brief getName - Получить название Сценария
 * @return
 */
QString SecurityScenario::getName() const {
    return this->name;
}

/**
 * @brief getIncidents - Получить список инцидентов ИБ,
 * которые могут приветси к развитию этого сценария
 * @return
 */
QList<quint32> SecurityScenario::getIncidents() const {
    return this->incidents;
}

/**
 * @brief setText - Установить текст сценария
 * @return
 */
void SecurityScenario::setText(QString const text) {
    this->text = text;
}

/**
 * @brief setName - Установить название сценария
 * @return
 */
void SecurityScenario::setName(QString const name) {
    this->name = name;
}

/**
 * @brief setID - Установить ID сценария
 * @return
 */
void SecurityScenario::setID(quint32 const id) {
    this->id = id;
}

/**
 * @brief setIncidents - Установить ID сценариев
 * @return
 */
void SecurityScenario::setIncidents(QList<quint32> const incidents) {
    this->incidents = incidents;
}

/**
 * @brief operator =
 * @param other
 * @return
 */
SecurityScenario& SecurityScenario::operator=(const SecurityScenario& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    id = other.id;
    text = other.text;
    name = other.name;
    incidents = other.incidents;

    return *this;
}

/**
 * @brief operator ==
 * @param other
 * @return
 */
bool SecurityScenario::operator==(const SecurityScenario& other) const {
    return (id == other.id
         && text == other.text
         && name == other.name
         && incidents == other.incidents);
}

/**
 * @brief operator !=
 * @param other
 * @return
 */
bool SecurityScenario::operator!=(const SecurityScenario& other) const {
    return !(*this == other);
}

/**
 * @brief operator <
 * @param other
 * @return
 */
bool SecurityScenario::operator<(const SecurityScenario& other) const {
    return !(*this > other);
}

/**
 * @brief operator >
 * @param other
 * @return
 */
bool SecurityScenario::operator>(const SecurityScenario& other) const {
    return this->id > other.id;
}

/**
 * @brief operator >=
 * @param other
 * @return
 */
bool SecurityScenario::operator>=(const SecurityScenario& other) const {
    return !(*this < other);
}

/**
 * @brief operator <=
 * @param other
 * @return
 */
bool SecurityScenario::operator<=(const SecurityScenario& other) const {
    return !(*this > other);
}


