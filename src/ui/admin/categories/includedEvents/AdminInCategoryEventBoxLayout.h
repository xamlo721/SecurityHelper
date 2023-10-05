#ifndef ADMININCATEGORYEVENTBOXLAYOUTS_H
#define ADMININCATEGORYEVENTBOXLAYOUTS_H

#include <QObject>
#include "qboxlayout.h"

#include "src/ui/admin/categories/includedEvents/InCategoryEventWidget.h"

class AdminInCategoryEventBoxLayout : public QObject {

    Q_OBJECT

    private:
        QVBoxLayout *boxLayoutEvents;

        QList<QVBoxLayout*> widgetBoxLayout;


        void initEventWidget(InCategoryEventWidget *eventWidget);

    private slots:

    public:
        explicit AdminInCategoryEventBoxLayout(QObject *parent = nullptr);


        void init(QVBoxLayout *boxLayout);

        void addEventWidget(InCategoryEventWidget *eventWidget);
        void renameEventWidget(InCategoryEventWidget *eventWidget);
        void deleteEventWidget(InCategoryEventWidget *eventWidget);

        void clearEvents();

        void unselectEventWidget(InCategoryEventWidget *eventWidget);

        void enableEventWidget(InCategoryEventWidget *eventWidget);
        void disableEventWidget(InCategoryEventWidget *eventWidget);

    public slots:

    signals:
        void signalEventSelected(const quint32 eventID);
        void signalEventUnselected(const quint32 eventID);

};

#endif // ADMININCATEGORYEVENTBOXLAYOUTS_H
