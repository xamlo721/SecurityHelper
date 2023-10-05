#ifndef INCATEGORYEVENTWIDGETSTORAGE_H
#define INCATEGORYEVENTWIDGETSTORAGE_H

#include "src/ui/admin/categories/includedEvents/InCategoryEventWidget.h"

class InCategoryEventWidgetStorage {

    private:
        QList<InCategoryEventWidget*> eventWidgets;
        QList<quint32> widgetNumbers;

        void sortWidgetNumbers();

    public:
        InCategoryEventWidgetStorage();

        void appendWidget(InCategoryEventWidget *eventWidget);
        void removeWidget(quint32 widgetID);

        void clear();

        InCategoryEventWidget *getEventWidget(quint32 widgetID);

};

#endif // INCATEGORYEVENTWIDGETSTORAGE_H
