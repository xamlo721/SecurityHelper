#ifndef INSCENARIOINCIDENTWIDGETSTORAGE_H
#define INSCENARIOINCIDENTWIDGETSTORAGE_H

#include "src/ui/admin/scenaries/includedIncidents/InScenarioIncidentWidget.h"

class InScenarioIncidentWidgetStorage {

    private:
        QList<InScenarioIncidentWidget*> incidentWidgets;
        QList<quint32> widgetNumbers;

        void sortWidgetNumbers();

    public:
        InScenarioIncidentWidgetStorage();

        void appendWidget(InScenarioIncidentWidget *incidentWidget);
        void removeWidget(quint32 widgetID);

        void clear();

        InScenarioIncidentWidget *getIncidentWidget(quint32 widgetID);

};

#endif // INSCENARIOINCIDENTWIDGETSTORAGE_H
