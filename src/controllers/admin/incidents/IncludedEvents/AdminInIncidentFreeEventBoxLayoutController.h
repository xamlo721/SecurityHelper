#ifndef ADMINININCIDENTFREEEVENTBOXLAYOUTCONTROLLER_H
#define ADMINININCIDENTFREEEVENTBOXLAYOUTCONTROLLER_H

#include <QObject>

#include "src/items/SecurityEvent.h"

#include "src/ui/admin/incidents/includedEvents/InIncidentEventWidget.h"

#include "src/ui/admin/incidents/includedEvents/AdminInIncidentEventBoxLayout.h"

#include "src/ui/admin/incidents/includedEvents/InIncidentEventWidgetStorage.h"

class AdminInIncidentFreeEventBoxLayoutController : public QObject {

    Q_OBJECT

    private:
        AdminInIncidentEventBoxLayout *boxLayoutEvents;

        QList<SecurityEvent> freeEvents;
        QList<SecurityEvent> selectedFreeEvents;

        InIncidentEventWidgetStorage widgetStorage;

        SecurityEvent addFreeEvent(SecurityEvent event);
        void addFreeEventWidget(SecurityEvent event);

        void deleteFreeEvent(quint32 eventID);
        void deleteFreeEventWidget(quint32 eventID);

    private slots:
        void onFreeEventSelected(const quint32 eventID);
        void onFreeEventUnselected(const quint32 eventID);

    public:
        explicit AdminInIncidentFreeEventBoxLayoutController(QObject *parent = nullptr);
        ~AdminInIncidentFreeEventBoxLayoutController();

        void init(QVBoxLayout *editMenuBoxLayoutInCategoryFreeEvents);

    public slots:
        void setFreeEventList(const QList<SecurityEvent> events);

        void slotUnincludeEventsFromIncident(QList<SecurityEvent> includedEvents);
        void slotAddSelectedEventsToIncidentButtonPressed();

        void slotAddFreeEvent(quint32 eventID, QString eventTitle);
        void slotDeleteFreeEvent(quint32 eventID);
        void renameFreeEvent(const quint32 eventID, QString newEventTitle);

        void addDisabledFreeEvent(SecurityEvent event);

        void unselectAllFreeEvents();

        void disableAllFreeEvents();

        void enableAllFreeEvents();

        void clearFreeEventList(const quint32 incidentID);

    signals:
        void signalSelectedFreeEventsNotEmpty();
        void signalSelectedFreeEventsEmpty();

        void freeEventsIncludedInIncident(const QList<SecurityEvent> includedEvents);

};

#endif // ADMINININCIDENTFREEEVENTBOXLAYOUTCONTROLLER_H
