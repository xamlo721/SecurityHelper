#ifndef EVENTCATEGORYWIDGETSTORAGE_H
#define EVENTCATEGORYWIDGETSTORAGE_H

#include <QObject>

#include "EditableEventCategoryWidget.h"
#include "UneditableEventCategoryWidget.h"

class EventCategoryWidgetStorage : public QObject {

    Q_OBJECT

    private:
        QList<UneditableEventCategoryWidget*> uneditableWidgets;
        QList<EditableEventCategoryWidget*> editableWidgets;
        QList<quint32> widgetNumbers;

        void sortWidgetNumbers();

    public:
        explicit EventCategoryWidgetStorage(QObject *parent = nullptr);

        void appendWidget(UneditableEventCategoryWidget *uneditableWidget, EditableEventCategoryWidget *editableWidget);
        void removeWidget(quint32 widgetID);

        UneditableEventCategoryWidget *getUneditableWidget(quint32 widgetID);
        EditableEventCategoryWidget *getEditableWidget(quint32 widgetID);

    signals:

};

#endif // EVENTCATEGORYWIDGETSTORAGE_H
