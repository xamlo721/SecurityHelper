#ifndef ADMININCATEGORYFREEEVENTBOXLAYOUTCONTROLLER_H
#define ADMININCATEGORYFREEEVENTBOXLAYOUTCONTROLLER_H

#include <QObject>

#include "src/items/SecurityEvent.h"


#include "src/ui/admin/categories/includedEvents/AdminInCategoryEventBoxLayout.h"

#include "src/ui/admin/categories/includedEvents/InCategoryEventWidgetStorage.h"

class AdminInCategoryFreeEventBoxLayoutController : public QObject {

    Q_OBJECT

    private:
        AdminInCategoryEventBoxLayout *boxLayoutEvents;

        QList<SecurityEvent> freeEvents;
        QList<SecurityEvent> selectedFreeEvents;

        InCategoryEventWidgetStorage widgetStorage;

        SecurityEvent addFreeEvent(SecurityEvent event);
        void addFreeEventWidget(SecurityEvent event);

        void deleteFreeEvent(quint32 eventID);
        void deleteFreeEventWidget(quint32 eventID);

    private slots:
        void onFreeEventSelected(const quint32 eventID);
        void onFreeEventUnselected(const quint32 eventID);

    public:
        explicit AdminInCategoryFreeEventBoxLayoutController(QObject *parent = nullptr);
        ~AdminInCategoryFreeEventBoxLayoutController();

        void init(QVBoxLayout *editMenuBoxLayoutInCategoryFreeEvents);

    public slots:
        void setFreeEventList(const QList<SecurityEvent> events);

        void slotUnincludeEventsFromCategory(QList<SecurityEvent> includedEvents);
        void slotAddSelectedEventsToCategoryButtonPressed();

        void slotAddFreeEvent(quint32 eventID, QString eventTitle);
        void slotDeleteFreeEvent(quint32 eventID);
        void renameFreeEvent(const quint32 eventID, QString newEventTitle);

        void addDisabledFreeEvent(SecurityEvent event);

        void addFreeEventsFromDeletedCategory(const QList<SecurityEvent> newFreeEvents);

        void unselectAllFreeEvents();

        void disableAllFreeEvents();

        void enableAllFreeEvents();

    signals:
        void signalSelectedFreeEventsNotEmpty();
        void signalSelectedFreeEventsEmpty();

        void freeEventsIncludedInCategory(const QList<SecurityEvent> includedEvents);

};

#endif // ADMININCATEGORYFREEEVENTBOXLAYOUTCONTROLLER_H
