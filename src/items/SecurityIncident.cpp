#include "SecurityIncident.h"

SecurityIncident::SecurityIncident(int id, QString text, QObject *parent) : QObject(parent) {
    this->id = id;
    this->text = text;
}


SecurityIncident::SecurityIncident(const SecurityIncident& other)
    : QObject(other.parent()), id(other.id), text(other.text) {


}

SecurityIncident& SecurityIncident::operator=(const SecurityIncident& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    id = other.id;
    text = other.text;

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


int SecurityIncident::getId() {
    return this->id;
}

QString SecurityIncident::getText() {
    return this->text;
}
