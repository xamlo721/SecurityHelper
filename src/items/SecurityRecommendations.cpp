#include "SecurityRecommendations.h"

/**
 * @brief SecurityRecommendations - базовый конструктор по умолчанию
 * Он необходим для того, чтобы объект можно было хранить
 * в контейнерах Qlist, QMap и т.д
 */
SecurityRecommendations::SecurityRecommendations() {

}
/**
 * @brief SecurityRecommendations - конструктор копирования объектов
 * @param other - объект, используемый как источник данных
 */
SecurityRecommendations::SecurityRecommendations(quint32 id, QString textContainment, QString textFixes, QString textRestore, QList<quint32> scenaries, QObject *parent) : QObject(parent) {
    this->id = id;
    this->textContainment = textContainment;
    this->textFixes = textFixes;
    this->textRestore = textRestore;
    this->scenaries = scenaries;
}

/**
 * @brief SecurityRecommendations
 * @param id - Цифровой целочисленный ID для однозначной идентификации и учёта объекта
 * @param textContainment - Набор инструкций для сдерживания игрозы, задаваемый администратором
 * @param textFixes - Набор инструкций для устранения угрозы, задаваемый администратором
 * @param textRestore - Набор инструкций для восстановления системы, задаваемый администратором
 * @param scenaries - Перечень SecurityScenario информационной безопасности, которые
 * могут быть исправлены этими рекомендациями
 * @param parent - родительский объект в иерархии Qt.
 */
SecurityRecommendations::SecurityRecommendations(const SecurityRecommendations& other)
    : QObject(other.parent()), id(other.id), textContainment(other.textContainment),
      textFixes(other.textFixes), textRestore(other.textRestore), scenaries(other.scenaries) {
}

/**
 * @brief getId - Получить ID рекомендации
 * @return
 */
quint32 SecurityRecommendations::getId() {
    return this->id;
}

/**
 * @brief getTextContainment - Получить текст рекомендации для сдерживания
 * @return
 */
QString SecurityRecommendations::getTextContainment() {
    return this->textContainment;
}

/**
 * @brief getTextFixes - Получить текст рекомендации для устранения
 * @return
 */
QString SecurityRecommendations::getTextFixes() {
    return this->textFixes;
}

/**
 * @brief getTextRestore - Получить текст рекомендации для восстановления
 * @return
 */
QString SecurityRecommendations::getTextRestore() {
    return this->textRestore;
}

/**
 * @brief getScenaries - получить перечень возможных сценариев
 * @return
 */
QList<quint32> SecurityRecommendations::getScenaries() {
    return this->scenaries;
}

/**
 * @brief setId - Установить ID инцидента
 * @return
 */
void SecurityRecommendations::setId(quint32 const id) {
    this->id = id;
}

/**
 * @brief setTextContainment - установить текст рекомендации для сдерживания
 * @return
 */
void SecurityRecommendations::setTextContainment(QString const textContainment) {
    this->textContainment = textContainment;
}

/**
 * @brief setTextFixes - установить текст рекомендации для устранения
 * @return
 */
void SecurityRecommendations::setTextFixes(QString const textFixes) {
    this->textFixes = textFixes;
}

/**
 * @brief setTextRestore - установить текст рекомендации для восстановления
 * @return
 */
void SecurityRecommendations::setTextRestore(QString const textRestore) {
    this->textRestore = textRestore;
}

/**
 * @brief setScenaries - установить перечень возможных сценариев
 * @return
 */
void SecurityRecommendations::setScenaries(QList<quint32> const scenaries) {
    this->scenaries = scenaries;
}

/**
 * @brief operator =
 * @param other
 * @return
 */
SecurityRecommendations& SecurityRecommendations::operator=(const SecurityRecommendations& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    id = other.id;
    textContainment = other.textContainment;
    textFixes = other.textFixes;
    textRestore = other.textRestore;
    scenaries = other.scenaries;

    return *this;
}

/**
 * @brief operator ==
 * @param other
 * @return
 */
bool SecurityRecommendations::operator==(const SecurityRecommendations& other) const {
    return (id == other.id
         && textContainment == other.textContainment
         && textFixes == other.textFixes
         && textRestore == other.textRestore
         && scenaries == other.scenaries);
}

/**
 * @brief operator !=
 * @param other
 * @return
 */
bool SecurityRecommendations::operator!=(const SecurityRecommendations& other) const {
    return !(*this == other);
}

/**
 * @brief operator <
 * @param other
 * @return
 */
bool SecurityRecommendations::operator<(const SecurityRecommendations& other) const {
    return !(*this > other);
}

/**
 * @brief operator >
 * @param other
 * @return
 */
bool SecurityRecommendations::operator>(const SecurityRecommendations& other) const {
    return this->id > other.id;
}

/**
 * @brief operator >=
 * @param other
 * @return
 */
bool SecurityRecommendations::operator>=(const SecurityRecommendations& other) const {
    return !(*this < other);
}

/**
 * @brief operator <=
 * @param other
 * @return
 */
bool SecurityRecommendations::operator<=(const SecurityRecommendations& other) const {
    return !(*this > other);
}
