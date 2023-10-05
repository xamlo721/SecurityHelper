#ifndef ADMININCATEGORYFREEEVENTBOXLAYOUTCONTROLLER_H
#define ADMININCATEGORYFREEEVENTBOXLAYOUTCONTROLLER_H

#include <QObject>

#include "src/items/SecurityEvent.h"

#include "src/ui/admin/categories//includedEvents/InCategoryEventWidget.h"

#include "src/ui/admin/categories/includedEvents/AdminInCategoryEventBoxLayout.h"

#include "src/ui/admin/categories/includedEvents/InCategoryEventWidgetStorage.h"

class AdminInCategoryFreeEventBoxLayoutController : public QObject {

    Q_OBJECT

    private:
        AdminInCategoryEventBoxLayout *boxLayoutEvents;

        QList<SecurityEvent> freeEvents;
        QList<SecurityEvent> selectedFreeEvents;

        InCategoryEventWidgetStorage widgetStorage;

        void clearSelectedFreeEvents();

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

        void addFreeEvent(SecurityEvent event);
        void renameFreeEvent(const quint32 eventID, QString newEventTitle);
        void deleteFreeEvent(quint32 eventID);

        void unselectAllFreeEvents();

        void disableAllFreeEvents();

        void enableAllFreeEvents();

    signals:
        void signalSelectedFreeEventsNotEmpty();
        void signalSelectedFreeEventsEmpty();

        void freeEventsIncludedInCategory(const QList<SecurityEvent> includedEvents);

};

#endif // ADMININCATEGORYFREEEVENTBOXLAYOUTCONTROLLER_H
