#ifndef ININCIDENTEVENTWIDGETSTORAGE_H
#define ININCIDENTEVENTWIDGETSTORAGE_H

#include "src/ui/SelectedWidget.h"

class InIncidentEventWidgetStorage {

    private:
        QList<SelectedWidget*> eventWidgets;
        QList<quint32> widgetNumbers;

        void sortWidgetNumbers();

    public:
        InIncidentEventWidgetStorage();

        void appendWidget(SelectedWidget *eventWidget);
        void removeWidget(quint32 widgetID);

        void clear();

        SelectedWidget *getEventWidget(quint32 widgetID);

};

#endif // ININCIDENTEVENTWIDGETSTORAGE_H
