#ifndef ADMININSCENARIOINCIDENTBOXLAYOUTS_H
#define ADMININSCENARIOINCIDENTBOXLAYOUTS_H

#include <QObject>
#include "qboxlayout.h"

#include "src/ui/admin/scenaries/includedIncidents/InScenarioIncidentWidget.h"

class AdminInScenarioIncidentBoxLayout : public QObject {

    Q_OBJECT

    private:
        QVBoxLayout *boxLayoutIncidents;

        QList<QVBoxLayout*> widgetBoxLayout;


        void initEventWidget(InScenarioIncidentWidget *incidentWidget);

    private slots:

    public:
        explicit AdminInScenarioIncidentBoxLayout(QObject *parent = nullptr);


        void init(QVBoxLayout *boxLayout);

        void addIncidentWidget(InScenarioIncidentWidget *incidentWidget);
        void renameIncidentWidget(InScenarioIncidentWidget *incidentWidget);
        void deleteIncidentWidget(InScenarioIncidentWidget *incidentWidget);

        void clearIncidents();

        void unselectIncidentWidget(InScenarioIncidentWidget *incidentWidget);

        void enableIncidentWidget(InScenarioIncidentWidget *incidentWidget);
        void disableIncidentWidget(InScenarioIncidentWidget *incidentWidget);

    public slots:

    signals:
        void signalIncidentSelected(const quint32 incidentID);
        void signalIncidentUnselected(const quint32 incidentID);

};

#endif // ADMININSCENARIOINCIDENTBOXLAYOUTS_H
