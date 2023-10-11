#ifndef SELECTEDWIDGETSTORAGE_H
#define SELECTEDWIDGETSTORAGE_H

#include <QObject>
#include "src/ui/SelectedWidget.h"

class SelectedWidgetStorage {

    private:
        QList<SelectedWidget*> incidentWidgets;
        QList<quint32> widgetNumbers;

        void sortWidgetNumbers();

    public:
        SelectedWidgetStorage();

        void appendWidget(SelectedWidget *incidentWidget);
        void removeWidget(quint32 widgetID);

        void clear();

        SelectedWidget *getWidget(quint32 widgetID);

};

#endif // SELECTEDWIDGETSTORAGE_H
