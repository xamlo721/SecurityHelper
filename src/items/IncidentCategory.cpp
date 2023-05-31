#include "IncidentCategory.h"

IncidentCategory::IncidentCategory(int id, QString text, QList<int> incidentes, QObject *parent) : QObject(parent) {
    this->id = id;
    this->text = text;
    this->incidentes = incidentes;
}


IncidentCategory::IncidentCategory(const IncidentCategory& other)
    : QObject(other.parent()), id(other.id), text(other.text),  incidentes(other.incidentes) {


}

IncidentCategory& IncidentCategory::operator=(const IncidentCategory& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    id = other.id;
    text = other.text;
    incidentes = other.incidentes;

    return *this;
}

bool IncidentCategory::operator==(const IncidentCategory& other) const {
    return (id == other.id
         && text == other.text
         && incidentes == other.incidentes);
}

bool IncidentCategory::operator!=(const IncidentCategory& other) const {
    return !(*this == other);
}

bool IncidentCategory::operator<(const IncidentCategory& other) const {
    return this->id < other.id;
}

bool IncidentCategory::operator>(const IncidentCategory& other) const {
    return this->id > other.id;
}


int IncidentCategory::getId() {
    return this->id;
}

QString IncidentCategory::getText() {
    return this->text;
}

QList<int> IncidentCategory::getIncidentesId() {
    return this->incidentes;
}
