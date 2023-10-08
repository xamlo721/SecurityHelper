#ifndef ADMINININCIDENTEVENTBOXLAYOUTS_H
#define ADMINININCIDENTEVENTBOXLAYOUTS_H

#include <QObject>
#include "qboxlayout.h"

#include "src/ui/admin/incidents/includedEvents/InIncidentEventWidget.h"

class AdminInIncidentEventBoxLayout : public QObject {

    Q_OBJECT

    private:
        QVBoxLayout *boxLayoutEvents;

        QList<QVBoxLayout*> widgetBoxLayout;


        void initEventWidget(InIncidentEventWidget *eventWidget);

    private slots:

    public:
        explicit AdminInIncidentEventBoxLayout(QObject *parent = nullptr);


        void init(QVBoxLayout *boxLayout);

        void addEventWidget(InIncidentEventWidget *eventWidget);
        void renameEventWidget(InIncidentEventWidget *eventWidget);
        void deleteEventWidget(InIncidentEventWidget *eventWidget);

        void clearEvents();

        void unselectEventWidget(InIncidentEventWidget *eventWidget);

        void enableEventWidget(InIncidentEventWidget *eventWidget);
        void disableEventWidget(InIncidentEventWidget *eventWidget);

    public slots:

    signals:
        void signalEventSelected(const quint32 eventID);
        void signalEventUnselected(const quint32 eventID);

};

#endif // ADMINININCIDENTEVENTBOXLAYOUTS_H
