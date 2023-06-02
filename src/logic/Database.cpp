#include "Database.h"

Database::Database(QMap<int, SecurityEvent> events, QMap<int, SecurityEventCategory> categories,
                   QMap<int, SecurityIncident> incidents, QMap<int, SecurityRecommendations> recommendations,
                   QMap<int, SecurityScenario> scenaries, QObject *parent) : QObject(parent) {

    this->events = events;
    this->categories = categories;
    this->incidents = incidents;
    this->recommendations = recommendations;
    this->scenaries = scenaries;
}

Database::Database(const Database& other)
    : QObject(other.parent()), events(other.events), categories(other.categories),
      incidents(other.incidents), recommendations(other.recommendations), scenaries(other.scenaries) {

}

Database& Database::operator=(const Database& other) {
    if (&other == this)
        return *this;

    QObject::setParent(other.parent());
    events = other.events;
    categories = other.categories;
    incidents = other.incidents;
    recommendations = other.recommendations;
    scenaries = other.scenaries;

    return *this;
}

bool Database::operator==(const Database& other) const {
    return (events == other.events
         && categories == other.categories
            && incidents == other.incidents
            && recommendations == other.recommendations
            && scenaries == other.scenaries);
}

bool Database::operator!=(const Database& other) const {
    return !(*this == other);
}
