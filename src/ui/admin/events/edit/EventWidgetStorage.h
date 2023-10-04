#ifndef EVENTWIDGETSTORAGE_H
#define EVENTWIDGETSTORAGE_H

#include "EditableEventWidget.h"
#include "UneditableEventWidget.h"

class EventWidgetStorage {

    private:
        QList<UneditableEventWidget*> uneditableWidgets;
        QList<EditableEventWidget*> editableWidgets;
        QList<quint32> widgetNumbers;

        void sortWidgetNumbers();

    public:
        explicit EventWidgetStorage();

        void appendWidget(UneditableEventWidget *uneditableWidget, EditableEventWidget *editableWidget);
        void removeWidget(quint32 widgetID);

        UneditableEventWidget *getUneditableWidget(quint32 widgetID);
        EditableEventWidget *getEditableWidget(quint32 widgetID);
};

#endif // EVENTWIDGETSTORAGE_H
