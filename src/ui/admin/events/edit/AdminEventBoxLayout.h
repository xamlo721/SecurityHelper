#ifndef ADMINEVENTBOXLAYOUT_H
#define ADMINEVENTBOXLAYOUT_H

#include <QObject>
#include "qboxlayout.h"

#include "UneditableEventWidget.h"
#include "EditableEventWidget.h"

class AdminEventBoxLayout : public QObject {

    Q_OBJECT

    private:
        /// Бокс категорий, над которым производятся действия
        QVBoxLayout *boxLayoutEvents;
        /// Лист с боксами пар виджетов
        QList<QVBoxLayout*> widgetBoxLayout;


        void initUneditableWidget(UneditableEventWidget *uneditableWidget);

        void initEditableWidget(EditableEventWidget *editableWidget);

    private slots:

    public:
        explicit AdminEventBoxLayout(QObject *parent = nullptr);


        void init(QVBoxLayout *boxLayout);

        void addEventWidget(UneditableEventWidget *uneditableWidget, EditableEventWidget *editableWidget);
        void deleteEventWidget(UneditableEventWidget *uneditableWidget);

        void clearEvents();

        void showEditableWidget(UneditableEventWidget *uneditableWidget, EditableEventWidget *editableWidget);
        void showUneditableWidget(EditableEventWidget *editableWidget, UneditableEventWidget *uneditableWidget);

    public slots:

    signals:
        void signalEditEvent(UneditableEventWidget * uneditableWidget);
        void editingFinished(EditableEventWidget * editableWidget);

        void signalDeleteEvent(UneditableEventWidget * uneditableWidget);
        void emptyWidget(EditableEventWidget * editableWidget);

        void signalEventSelected(const quint32 eventID);
        void signalEventUnselected(const quint32 categoryID);
};

#endif // ADMINEVENTBOXLAYOUT_H
