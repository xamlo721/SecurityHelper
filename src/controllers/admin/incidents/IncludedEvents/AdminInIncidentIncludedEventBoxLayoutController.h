#ifndef ADMINININCIDENTINCLUDEDEVENTBOXLAYOUTCONTROLLER_H
#define ADMINININCIDENTINCLUDEDEVENTBOXLAYOUTCONTROLLER_H

#include <QObject>

#include "src/items/SecurityEvent.h"


#include "src/ui/admin/incidents/includedEvents/AdminInIncidentEventBoxLayout.h"

#include "src/ui/admin/incidents/includedEvents/InIncidentEventWidgetStorage.h"

class AdminInIncidentIncludedEventBoxLayoutController : public QObject {

    Q_OBJECT

    private:
        AdminInIncidentEventBoxLayout *boxLayoutEvents;

        QList<SecurityEvent> includedEvents;
        QList<SecurityEvent> selectedIncludedEvents;

        InIncidentEventWidgetStorage widgetStorage;


        void deleteIncludedEvent(quint32 eventID);
        void deleteIncludedEventWidget(quint32 eventID);

        void unselectAllIncludedEvents();

        SecurityEvent addIncludedEvent(SecurityEvent event);
        void addIncludedEventWidget(SecurityEvent event);

        void enableAllIncludedEvents();
        void disableAllIncludedEvents();

    private slots:
        void onIncludedEventSelected(const quint32 eventID);
        void onIncludedEventUnselected(const quint32 eventID);

    public:
        explicit AdminInIncidentIncludedEventBoxLayoutController(QObject *parent = nullptr);
        ~AdminInIncidentIncludedEventBoxLayoutController();

        void init(QVBoxLayout *editMenuBoxLayoutInCategoryIncludedEvents);

    public slots:
        void setIncludedEventList(const QList<SecurityEvent> events);

        void slotIncludeFreeEventsToIncident(QList<SecurityEvent> freeEvents);
        void slotRemoveSelectedEventsFromIncidentButtonPressed();

        void slotAddIncludedEvent(quint32 eventID, QString eventTitle);
        void slotDeleteIncludedEvent(quint32 eventID);
        void renameIncludedEvent(const quint32 eventID, QString newEventTitle);

        void clearIncludedEventList(const quint32 incidentID);

    signals:
        void signalSelectedIncludedEventsNotEmpty();
        void signalSelectedIncludedEventsEmpty();

        void eventsRemovedFromIncident(const QList<SecurityEvent> removedEvents);


        void incidentEventsMustBeSaved(const quint32 incidentID, QList<SecurityEvent> incidentEvents);

};

#endif // ADMINININCIDENTINCLUDEDEVENTBOXLAYOUTCONTROLLER_H
