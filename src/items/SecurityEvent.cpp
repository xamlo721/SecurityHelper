#include "SecurityEvent.h"

SecurityEvent::SecurityEvent(quint32 id, QString text, QObject *parent) : QObject(parent) {
    this->id = id;
    this->text = text;
}


SecurityEvent::SecurityEvent(const SecurityEvent& other)
    : QObject(other.parent()), id(other.id), text(other.text) {


}

SecurityEvent& SecurityEvent::operator=(const SecurityEvent& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    id = other.id;
    text = other.text;

    return *this;
}

bool SecurityEvent::operator==(const SecurityEvent& other) const {
    return (id == other.id
         && text == other.text);
}

bool SecurityEvent::operator!=(const SecurityEvent& other) const {
    return !(*this == other);
}

bool SecurityEvent::operator<(const SecurityEvent& other) const {
    return this->id < other.id;
}

bool SecurityEvent::operator>(const SecurityEvent& other) const {
    return this->id > other.id;
}


quint32 SecurityEvent::getId() {
    return this->id;
}

QString SecurityEvent::getText() {
    return this->text;
}
