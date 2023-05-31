#include "SecurityRecommendations.h"

SecurityRecommendations::SecurityRecommendations(int id, QString textContainment, QString textFixes, QString textRestore, QObject *parent) : QObject(parent) {
    this->id = id;
    this->textContainment = textContainment;
    this->textFixes = textFixes;
    this->textRestore = textRestore;
}


SecurityRecommendations::SecurityRecommendations(const SecurityRecommendations& other)
    : QObject(other.parent()), id(other.id), textContainment(other.textContainment), textFixes(other.textFixes), textRestore(other.textRestore) {


}

SecurityRecommendations& SecurityRecommendations::operator=(const SecurityRecommendations& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    id = other.id;
    textContainment = other.textContainment;
    textFixes = other.textFixes;
    textRestore = other.textRestore;

    return *this;
}

bool SecurityRecommendations::operator==(const SecurityRecommendations& other) const {
    return (id == other.id
         && textContainment == other.textContainment
         && textFixes == other.textFixes
         && textRestore == other.textRestore);
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
