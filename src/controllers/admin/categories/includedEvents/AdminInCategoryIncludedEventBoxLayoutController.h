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

        void unselectAllIncludedEvents();

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

        void addIncludedEvent(SecurityEvent event);
        void renameIncludedEvent(const quint32 eventID, QString newEventTitle);
        void deleteIncludedEvent(quint32 eventID);

        void clearIncludedEventList(const quint32 categoryID);

    signals:
        void signalSelectedIncludedEventsNotEmpty();
        void signalSelectedIncludedEventsEmpty();

        void eventsRemovedFromCategory(const QList<SecurityEvent> removedEvents);

        /// Сигнал о принудительном сохранении в базу данных событий, входящих в данную категорию, при закрытии категории
        void categoryEventsMustBeSaved(const quint32 categoryID, QList<SecurityEvent> categoryEvents);

};

#endif // ADMININCATEGORYINCLUDEDEVENTBOXLAYOUTCONTROLLER_H
