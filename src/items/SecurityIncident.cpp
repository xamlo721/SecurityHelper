#include "SecurityIncident.h"

SecurityIncident::SecurityIncident(quint32 id, QString text, QList<quint32> events, QObject *parent) : QObject(parent) {
    this->id = id;
    this->text = text;
    this->events = events;
}


SecurityIncident::SecurityIncident(const SecurityIncident& other)
    : QObject(other.parent()), id(other.id), text(other.text), events(other.events) {


}

SecurityIncident& SecurityIncident::operator=(const SecurityIncident& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    id = other.id;
    text = other.text;
    events = other.events;

    return *this;
}

bool SecurityIncident::operator==(const SecurityIncident& other) const {
    return (id == other.id
         && text == other.text);
}

bool SecurityIncident::operator!=(const SecurityIncident& other) const {
    return !(*this == other);
}

bool SecurityIncident::operator<(const SecurityIncident& other) const {
    return this->id < other.id;
}

bool SecurityIncident::operator>(const SecurityIncident& other) const {
    return this->id > other.id;
}


quint32 SecurityIncident::getId() {
    return this->id;
}

QString SecurityIncident::getText() {
    return this->text;
}

QList<quint32> SecurityIncident::getEventIds() {
    return this->events;
}
