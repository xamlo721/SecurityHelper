#ifndef ADMININSCENARIOINCIDENTBOXLAYOUTS_H
#define ADMININSCENARIOINCIDENTBOXLAYOUTS_H

#include <QObject>
#include "qboxlayout.h"

#include "src/ui/SelectedWidget.h"

class AdminInScenarioIncidentBoxLayout : public QObject {

    Q_OBJECT

    private:
        QVBoxLayout *boxLayoutIncidents;

        QList<QVBoxLayout*> widgetBoxLayout;


        void initEventWidget(SelectedWidget *incidentWidget);

    private slots:

    public:
        explicit AdminInScenarioIncidentBoxLayout(QObject *parent = nullptr);


        void init(QVBoxLayout *boxLayout);

        void addIncidentWidget(SelectedWidget *incidentWidget);
        void renameIncidentWidget(SelectedWidget *incidentWidget);
        void deleteIncidentWidget(SelectedWidget *incidentWidget);

        void clearIncidents();

        void unselectIncidentWidget(SelectedWidget *incidentWidget);

        void enableIncidentWidget(SelectedWidget *incidentWidget);
        void disableIncidentWidget(SelectedWidget *incidentWidget);

    public slots:

    signals:
        void signalIncidentSelected(const quint32 incidentID);
        void signalIncidentUnselected(const quint32 incidentID);

};

#endif // ADMININSCENARIOINCIDENTBOXLAYOUTS_H
