#ifndef ADMININCIDENTBOXLAYOUT_H
#define ADMININCIDENTBOXLAYOUT_H

#include <QObject>
#include "qboxlayout.h"

#include "UneditableIncidentWidget.h"
#include "EditableIncidentWidget.h"

class AdminIncidentBoxLayout : public QObject {

    Q_OBJECT

    private:
        QVBoxLayout *boxLayoutIncidents;
        /// Лист с боксами пар виджетов
        QList<QVBoxLayout*> widgetBoxLayout;


        void initUneditableWidget(UneditableIncidentWidget *uneditableWidget);

        void initEditableWidget(EditableIncidentWidget *editableWidget);

    private slots:

    public:
        explicit AdminIncidentBoxLayout(QObject *parent = nullptr);


        void init(QVBoxLayout *boxLayout);

        void addIncidentWidget(UneditableIncidentWidget *uneditableWidget, EditableIncidentWidget *editableWidget);
        void deleteIncidentWidget(UneditableIncidentWidget *uneditableWidget);

        void clearIncidents();

        void showEditableWidget(UneditableIncidentWidget *uneditableWidget, EditableIncidentWidget *editableWidget);
        void showUneditableWidget(EditableIncidentWidget *editableWidget, UneditableIncidentWidget *uneditableWidget);

        void unselectUneditableWidget(UneditableIncidentWidget *uneditableWidget);

        void enableUneditableWidget(UneditableIncidentWidget *uneditableWidget);
        void disableUneditableWidget(UneditableIncidentWidget *uneditableWidget);

    public slots:

    signals:
        void signalEditIncident(UneditableIncidentWidget * uneditableWidget);
        void editingFinished(EditableIncidentWidget * editableWidget);

        void signalDeleteIncident(UneditableIncidentWidget * uneditableWidget);

        void signalIncidentSelected(const quint32 incidentID);
        void signalIncidentUnselected(const quint32 incidentID);
};

#endif // ADMININCIDENTBOXLAYOUT_H
