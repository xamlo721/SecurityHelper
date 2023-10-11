#ifndef ADMININSCENARIOINCLUDEDINCIDENTBOXLAYOUTCONTROLLER_H
#define ADMININSCENARIOINCLUDEDINCIDENTBOXLAYOUTCONTROLLER_H

#include <QObject>

#include "src/items/SecurityEvent.h"

#include "src/ui/SelectedWidget.h"

#include "src/ui/admin/incidents/includedEvents/AdminInIncidentEventBoxLayout.h"

#include "src/ui/admin/incidents/includedEvents/InIncidentEventWidgetStorage.h"

#include "src/items/SecurityIncident.h"

#include "src/ui/admin/scenaries/includedIncidents/AdminInScenarioIncidentBoxLayout.h"

#include "src/ui/admin/scenaries/includedIncidents/InScenarioIncidentWidgetStorage.h"

class AdminInScenarioIncludedIncidentBoxLayoutController : public QObject {

    Q_OBJECT

    private:
        AdminInScenarioIncidentBoxLayout *boxLayoutIncidents;

        QList<SecurityIncident> includedIncidents;
        QList<SecurityIncident> selectedIncludedIncidents;

        InScenarioIncidentWidgetStorage widgetStorage;

        void deleteIncludedIncident(quint32 incidentID);
        void deleteIncludedIncidentWidget(quint32 incidentID);

        void unselectAllIncludedIncidents();

        SecurityIncident addIncludedIncident(SecurityIncident incident);
        void addIncludedIncidentWidget(SecurityIncident incident);

        void enableAllIncludedIncidents();
        void disableAllIncludedIncidents();

    private slots:
        void onIncludedIncidentSelected(const quint32 incidentID);
        void onIncludedIncidentUnselected(const quint32 incidentID);

    public:
        explicit AdminInScenarioIncludedIncidentBoxLayoutController(QObject *parent = nullptr);
        ~AdminInScenarioIncludedIncidentBoxLayoutController();

        void init(QVBoxLayout *editMenuBoxLayoutInScenarioIncludedIncidents);

    public slots:
        void setIncludedIncidentList(const QList<SecurityIncident> incidents);

        void slotIncludeFreeIncidentsToScenario(QList<SecurityIncident> freeIncidents);
        void slotRemoveSelectedIncidentsFromScenarioButtonPressed();

        void slotAddIncludedIncident(quint32 incidentID, QString incidentText, QString incidentTitle, QList<quint32> incidentEvents);
        void slotDeleteIncludedIncident(quint32 incidentID);
        void renameIncludedIncident(const quint32 incidentID, QString newIncidentTitle);

        void clearIncludedIncidentList(const quint32 scenarioID);

    signals:
        void signalSelectedIncludedIncidentsNotEmpty();
        void signalSelectedIncludedIncidentsEmpty();

        void incidentsRemovedFromScenario(const QList<SecurityIncident> removedIncidents);

        /// Сигнал о принудительном сохранении в базу данных событий, входящих в данный инцидент при его закрытии
        void scenarioIncidentsMustBeSaved(const quint32 scenarioID, QList<SecurityIncident> scenarioIncidents);

};

#endif // ADMININSCENARIOINCLUDEDINCIDENTBOXLAYOUTCONTROLLER_H
