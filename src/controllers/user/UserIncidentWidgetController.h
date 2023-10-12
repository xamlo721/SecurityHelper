#ifndef USERINCIDENTWIDGETCONTROLLER_H
#define USERINCIDENTWIDGETCONTROLLER_H

#include <QObject>

#include "src/ui/user/IncidentMenuWidget.h"
#include "src/items/SecurityIncident.h"

class UserIncidentController : public QObject {

    Q_OBJECT

    public:
        explicit UserIncidentController(QObject *parent = nullptr);


        void init(IncidentMenuWidget *incidentWidget);

    public slots:
        void setIncidentList(QList<SecurityIncident> incidents);

    private:
        IncidentMenuWidget *incidentMenuWidget;

    signals:
        void signalOpenIncident(quint32 id);
};

#endif // USERINCIDENTWIDGETCONTROLLER_H
