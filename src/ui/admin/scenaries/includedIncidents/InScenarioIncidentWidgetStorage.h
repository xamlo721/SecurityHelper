#ifndef INSCENARIOINCIDENTWIDGETSTORAGE_H
#define INSCENARIOINCIDENTWIDGETSTORAGE_H

#include "src/ui/SelectedWidget.h"

class InScenarioIncidentWidgetStorage {

    private:
        QList<SelectedWidget*> incidentWidgets;
        QList<quint32> widgetNumbers;

        void sortWidgetNumbers();

    public:
        InScenarioIncidentWidgetStorage();

        void appendWidget(SelectedWidget *incidentWidget);
        void removeWidget(quint32 widgetID);

        void clear();

        SelectedWidget *getIncidentWidget(quint32 widgetID);

};

#endif // INSCENARIOINCIDENTWIDGETSTORAGE_H
