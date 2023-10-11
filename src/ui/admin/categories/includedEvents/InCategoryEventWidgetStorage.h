#ifndef INCATEGORYEVENTWIDGETSTORAGE_H
#define INCATEGORYEVENTWIDGETSTORAGE_H

#include "src/ui/SelectedWidget.h"

class InCategoryEventWidgetStorage {

    private:
        QList<SelectedWidget*> eventWidgets;
        QList<quint32> widgetNumbers;

        void sortWidgetNumbers();

    public:
        InCategoryEventWidgetStorage();

        void appendWidget(SelectedWidget *eventWidget);
        void removeWidget(quint32 widgetID);

        void clear();

        SelectedWidget *getEventWidget(quint32 widgetID);

};

#endif // INCATEGORYEVENTWIDGETSTORAGE_H
