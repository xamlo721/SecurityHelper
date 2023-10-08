#ifndef ININCIDENTEVENTWIDGETSTORAGE_H
#define ININCIDENTEVENTWIDGETSTORAGE_H

#include "src/ui/admin/incidents/includedEvents/InIncidentEventWidget.h"

class InIncidentEventWidgetStorage {

    private:
        QList<InIncidentEventWidget*> eventWidgets;
        QList<quint32> widgetNumbers;

        void sortWidgetNumbers();

    public:
        InIncidentEventWidgetStorage();

        void appendWidget(InIncidentEventWidget *eventWidget);
        void removeWidget(quint32 widgetID);

        void clear();

        InIncidentEventWidget *getEventWidget(quint32 widgetID);

};

#endif // ININCIDENTEVENTWIDGETSTORAGE_H
