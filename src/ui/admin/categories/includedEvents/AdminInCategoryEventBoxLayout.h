#ifndef ADMININCATEGORYEVENTBOXLAYOUTS_H
#define ADMININCATEGORYEVENTBOXLAYOUTS_H

#include <QObject>
#include "qboxlayout.h"

#include "src/ui/SelectedWidget.h"

class AdminInCategoryEventBoxLayout : public QObject {

    Q_OBJECT

    private:
        QVBoxLayout *boxLayoutEvents;

        QList<QVBoxLayout*> widgetBoxLayout;


        void initEventWidget(SelectedWidget *eventWidget);

    private slots:

    public:
        explicit AdminInCategoryEventBoxLayout(QObject *parent = nullptr);


        void init(QVBoxLayout *boxLayout);

        void addEventWidget(SelectedWidget *eventWidget);
        void renameEventWidget(SelectedWidget *eventWidget);
        void deleteEventWidget(SelectedWidget *eventWidget);

        void clearEvents();

        void unselectEventWidget(SelectedWidget *eventWidget);

        void enableEventWidget(SelectedWidget *eventWidget);
        void disableEventWidget(SelectedWidget *eventWidget);

    public slots:

    signals:
        void signalEventSelected(const quint32 eventID);
        void signalEventUnselected(const quint32 eventID);

};

#endif // ADMININCATEGORYEVENTBOXLAYOUTS_H
