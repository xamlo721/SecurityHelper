#ifndef ADMININSCENARIOFREEINCIDENTBOXLAYOUTCONTROLLER_H
#define ADMININSCENARIOFREEINCIDENTBOXLAYOUTCONTROLLER_H

#include <QObject>

#include "src/items/SecurityIncident.h"

#include "src/ui/SelectedWidget.h"

#include "src/ui/admin/scenaries/includedIncidents/AdminInScenarioIncidentBoxLayout.h"

#include "src/ui/admin/scenaries/includedIncidents/InScenarioIncidentWidgetStorage.h"

class AdminInScenarioFreeIncidentBoxLayoutController : public QObject {

    Q_OBJECT

    private:
        AdminInScenarioIncidentBoxLayout *boxLayoutIncidents;

        QList<SecurityIncident> freeIncidents;
        QList<SecurityIncident> selectedFreeIncidents;

        InScenarioIncidentWidgetStorage widgetStorage;

        SecurityIncident addFreeIncident(SecurityIncident incident);
        void addFreeIncidentWidget(SecurityIncident incident);

        void deleteFreeIncident(quint32 incidentID);
        void deleteFreeIncidentWidget(quint32 incidentID);

    private slots:
        void onFreeIncidentSelected(const quint32 incidentID);
        void onFreeIncidentUnselected(const quint32 incidentID);

    public:
        explicit AdminInScenarioFreeIncidentBoxLayoutController(QObject *parent = nullptr);
        ~AdminInScenarioFreeIncidentBoxLayoutController();

        void init(QVBoxLayout *editMenuBoxLayoutInScenarioFreeIncidents);

    public slots:
        void setFreeIncidentList(const QList<SecurityIncident> incidents);

        void slotUnincludeIncidentsFromScenario(QList<SecurityIncident> includedIncidents);
        void slotAddSelectedIncidentsToScenarioButtonPressed();

        void slotAddFreeIncident(quint32 incidentID, QString incidentText, QString incidentTitle, QList<quint32> incidentEvents);
        void slotDeleteFreeIncident(quint32 incidentID);
        void renameFreeIncident(const quint32 incidentID, QString newIncidentTitle);

        void addDisabledFreeIncident(SecurityIncident incident);

        void unselectAllFreeIncidents();

        void disableAllFreeIncidents();

        void enableAllFreeIncidents();

        void clearFreeIncidentList(const quint32 scenarioID);

    signals:
        void signalSelectedFreeIncidentsNotEmpty();
        void signalSelectedFreeIncidentsEmpty();

        void freeIncidentsIncludedInScenario(const QList<SecurityIncident> includedIncidents);

};

#endif // ADMININSCENARIOFREEINCIDENTBOXLAYOUTCONTROLLER_H
