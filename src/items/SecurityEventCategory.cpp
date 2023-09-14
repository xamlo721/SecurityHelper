#include "SecurityEventCategory.h"

SecurityEventCategory::SecurityEventCategory(quint32 id, QString text, QList<quint32> events, QObject *parent) : QObject(parent) {
    this->id = id;
    this->text = text;
    this->events = events;
}

SecurityEventCategory::SecurityEventCategory(const SecurityEventCategory& other)
    : QObject(other.parent()), id(other.id), text(other.text),  events(other.events) {


}

SecurityEventCategory& SecurityEventCategory::operator=(const SecurityEventCategory& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    id = other.id;
    text = other.text;
    events = other.events;

    return *this;
}

bool SecurityEventCategory::operator==(const SecurityEventCategory& other) const {
    return (id == other.id
         && text == other.text
         && events == other.events);
}

bool SecurityEventCategory::operator!=(const SecurityEventCategory& other) const {
    return !(*this == other);
}

bool SecurityEventCategory::operator<(const SecurityEventCategory& other) const {
    return this->id < other.id;
}

bool SecurityEventCategory::operator>(const SecurityEventCategory& other) const {
    return this->id > other.id;
}


quint32 SecurityEventCategory::getId() {
    return this->id;
}

QString SecurityEventCategory::getText() {
    return this->text;
}

QList<quint32> SecurityEventCategory::getEventIds() {
    return this->events;
}
