#include "SecurityScenario.h"

SecurityScenario::SecurityScenario(int id, QString text, QObject *parent) : QObject(parent) {
    this->id = id;
    this->text = text;
}


SecurityScenario::SecurityScenario(const SecurityScenario& other)
    : QObject(other.parent()), id(other.id), text(other.text) {


}

SecurityScenario& SecurityScenario::operator=(const SecurityScenario& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    id = other.id;
    text = other.text;

    return *this;
}

bool SecurityScenario::operator==(const SecurityScenario& other) const {
    return (id == other.id
         && text == other.text);
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


int SecurityScenario::getId() {
    return this->id;
}

QString SecurityScenario::getText() {
    return this->text;
}
