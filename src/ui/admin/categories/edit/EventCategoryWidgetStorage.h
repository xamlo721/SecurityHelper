#ifndef EVENTCATEGORYWIDGETSTORAGE_H
#define EVENTCATEGORYWIDGETSTORAGE_H

#include "EditableEventCategoryWidget.h"
#include "UneditableEventCategoryWidget.h"

class EventCategoryWidgetStorage{

    private:
        QList<UneditableEventCategoryWidget*> uneditableWidgets;
        QList<EditableEventCategoryWidget*> editableWidgets;
        QList<quint32> widgetNumbers;

        void sortWidgetNumbers();

    public:
        explicit EventCategoryWidgetStorage();

        void appendWidget(UneditableEventCategoryWidget *uneditableWidget, EditableEventCategoryWidget *editableWidget);
        void removeWidget(quint32 widgetID);

        UneditableEventCategoryWidget *getUneditableWidget(quint32 widgetID);
        EditableEventCategoryWidget *getEditableWidget(quint32 widgetID);
};

#endif // EVENTCATEGORYWIDGETSTORAGE_H
