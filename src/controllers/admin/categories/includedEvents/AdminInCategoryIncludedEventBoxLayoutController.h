#ifndef ADMININCATEGORYINCLUDEDEVENTBOXLAYOUTCONTROLLER_H
#define ADMININCATEGORYINCLUDEDEVENTBOXLAYOUTCONTROLLER_H

#include <QObject>

#include "src/items/SecurityEvent.h"

#include "src/ui/admin/categories//includedEvents/InCategoryEventWidget.h"

#include "src/ui/admin/categories/includedEvents/AdminInCategoryEventBoxLayout.h"

#include "src/ui/admin/categories/includedEvents/InCategoryEventWidgetStorage.h"

class AdminInCategoryIncludedEventBoxLayoutController : public QObject {

    Q_OBJECT

    private:
        AdminInCategoryEventBoxLayout *boxLayoutEvents;

        QList<SecurityEvent> includedEvents;
        QList<SecurityEvent> selectedIncludedEvents;

        InCategoryEventWidgetStorage widgetStorage;

        void clearSelectedIncludedEvents();

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
        explicit AdminInCategoryIncludedEventBoxLayoutController(QObject *parent = nullptr);
        ~AdminInCategoryIncludedEventBoxLayoutController();

        void init(QVBoxLayout *editMenuBoxLayoutInCategoryIncludedEvents);

    public slots:
        void setIncludedEventList(const QList<SecurityEvent> events);

        void slotIncludeFreeEventsToCategory(QList<SecurityEvent> freeEvents);
        void slotRemoveSelectedEventsFromCategoryButtonPressed();

        void slotAddIncludedEvent(quint32 eventID, QString eventTitle);
        void slotDeleteIncludedEvent(quint32 eventID);
        void renameIncludedEvent(const quint32 eventID, QString newEventTitle);

        void clearIncludedEventList(const quint32 categoryID);

    signals:
        void signalSelectedIncludedEventsNotEmpty();
        void signalSelectedIncludedEventsEmpty();

        void eventsRemovedFromCategory(const QList<SecurityEvent> removedEvents);

        /// Сигнал о принудительном сохранении в базу данных событий, входящих в данную категорию, при закрытии категории
        void categoryEventsMustBeSaved(const quint32 categoryID, QList<SecurityEvent> categoryEvents);

};

#endif // ADMININCATEGORYINCLUDEDEVENTBOXLAYOUTCONTROLLER_H
