#ifndef INCIDENTCONTROLLER_H
#define INCIDENTCONTROLLER_H

#include <QObject>

class IncidentController : public QObject
{
    Q_OBJECT
public:
    explicit IncidentController(QObject *parent = nullptr);

signals:

};

#endif // INCIDENTCONTROLLER_H
