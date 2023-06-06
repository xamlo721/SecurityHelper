#include "SecurityRecommendations.h"

SecurityRecommendations::SecurityRecommendations(int id, QString textContainment, QString textFixes, QString textRestore, QList<int> scenaries, QObject *parent) : QObject(parent) {
    this->id = id;
    this->textContainment = textContainment;
    this->textFixes = textFixes;
    this->textRestore = textRestore;
    this->scenaries = scenaries;
}


SecurityRecommendations::SecurityRecommendations(const SecurityRecommendations& other)
    : QObject(other.parent()), id(other.id), textContainment(other.textContainment),
      textFixes(other.textFixes), textRestore(other.textRestore), scenaries(other.scenaries) {


}

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

bool SecurityRecommendations::operator==(const SecurityRecommendations& other) const {
    return (id == other.id
         && textContainment == other.textContainment
         && textFixes == other.textFixes
         && textRestore == other.textRestore
         && scenaries == other.scenaries);
}

bool SecurityRecommendations::operator!=(const SecurityRecommendations& other) const {
    return !(*this == other);
}

bool SecurityRecommendations::operator<(const SecurityRecommendations& other) const {
    return this->id < other.id;
}

bool SecurityRecommendations::operator>(const SecurityRecommendations& other) const {
    return this->id > other.id;
}


int SecurityRecommendations::getId() {
    return this->id;
}

QString SecurityRecommendations::getTextContainment() {
    return this->textContainment;
}

QString SecurityRecommendations::getTextFixes() {
    return this->textFixes;
}

QString SecurityRecommendations::getTextRestore() {
    return this->textRestore;
}
QList<int> SecurityRecommendations::getScenaries() {
    return this->scenaries;
}
