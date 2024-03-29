#include "SecurityScenario.h"

SecurityScenario::SecurityScenario(quint32 id, QString text, QList<quint32> incidents, QObject *parent) : QObject(parent) {
    this->id = id;
    this->text = text;
    this->incidents = incidents;
}


SecurityScenario::SecurityScenario(const SecurityScenario& other)
    : QObject(other.parent()), id(other.id), text(other.text), incidents(other.incidents){


}

SecurityScenario& SecurityScenario::operator=(const SecurityScenario& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    id = other.id;
    text = other.text;
    incidents = other.incidents;

    return *this;
}

bool SecurityScenario::operator==(const SecurityScenario& other) const {
    return (id == other.id
         && text == other.text
            && incidents == other.incidents);
}

bool SecurityScenario::operator!=(const SecurityScenario& other) const {
    return !(*this == other);
}

bool SecurityScenario::operator<(const SecurityScenario& other) const {
    return this->id < other.id;
}

bool SecurityScenario::operator>(const SecurityScenario& other) const {
    return this->id > other.id;
}


quint32 SecurityScenario::getId() {
    return this->id;
}

QString SecurityScenario::getText() {
    return this->text;
}

QList<quint32> SecurityScenario::getIncidents() {
    return this->incidents;
}

