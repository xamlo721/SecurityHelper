#ifndef INCIDENTWIDGETSTORAGE_H
#define INCIDENTWIDGETSTORAGE_H

#include "EditableIncidentWidget.h"
#include "UneditableIncidentWidget.h"

class IncidentWidgetStorage {

    private:
        QList<UneditableIncidentWidget*> uneditableWidgets;
        QList<EditableIncidentWidget*> editableWidgets;
        QList<quint32> widgetNumbers;

        void sortWidgetNumbers();

    public:
        explicit IncidentWidgetStorage();

        void appendWidget(UneditableIncidentWidget *uneditableWidget, EditableIncidentWidget *editableWidget);
        void removeWidget(quint32 widgetID);

        UneditableIncidentWidget *getUneditableWidget(quint32 widgetID);
        EditableIncidentWidget *getEditableWidget(quint32 widgetID);
};

#endif // INCIDENTWIDGETSTORAGE_H
