#ifndef ADMINSCENARIOBOXLAYOUTCONTROLLER_H
#define ADMINSCENARIOBOXLAYOUTCONTROLLER_H

#include <QObject>

#include "src/items/SecurityIncident.h"

#include "src/ui/admin/incidents/edit/UneditableIncidentWidget.h"
#include "src/ui/admin/incidents/edit/EditableIncidentWidget.h"

#include "src/ui/admin/incidents/edit/AdminIncidentBoxLayout.h"

#include "src/ui/admin/incidents/edit/IncidentWidgetStorage.h"

#include "src/items/SecurityScenario.h"

#include "src/ui/admin/scenaries/edit/UneditableScenarioWidget.h"
#include "src/ui/admin/scenaries/edit/EditableScenarioWidget.h"

#include "src/ui/admin/scenaries/edit/AdminScenarioBoxLayout.h"

#include "src/ui/admin/scenaries/edit/ScenarioWidgetStorage.h"

class AdminScenarioBoxLayoutController : public QObject {

    Q_OBJECT

    private:

        AdminScenarioBoxLayout *boxLayoutScenaries;


        QList<SecurityScenario> scenaries;

        QList<SecurityScenario> selectedScenaries;

        ScenarioWidgetStorage widgetStorage;

        SecurityScenario addScenario();
        void addScenarioWidget(SecurityScenario scenario);

        void deleteScenario(const quint32 scenarioID);
        void deleteScenarioWidget(const quint32 scenarioID);

        void renameScenario(const quint32 widgetID, const QString widgetTitle, const QString widgetText);

        void unselectAllScenaries();

        void enableAllScenaries();
        void disableAllScenaries();

    private slots:
        void slotShowEditableWidget(UneditableScenarioWidget *uneditableWidget);
        void slotShowUneditableWidget(EditableScenarioWidget *editableWidget);

        void slotDeleteScenario(UneditableScenarioWidget * uneditableWidget);

        void onScenarioSelected(const quint32 scenarioID);
        void onScenarioUnselected(const quint32 scenarioID);

    public:
        explicit AdminScenarioBoxLayoutController(QObject *parent = nullptr);

        void init(QVBoxLayout *editMenuBoxLayoutScenaries);

    public slots:
        void setScenarioList(const QList<SecurityScenario> scenaries);

        void slotAddScenarioButtonPressed();
        void slotDeleteSelectedScenariesButtonPressed();

    signals:
        void signalSelectedScenariesNotEmpty();
        void signalSelectedScenariesEmpty();

        void scenarioIsActive();
        void scenarioIsNotActive();

        void scenarioIsOpened(quint32 scenarioID);
        void scenarioIsClosed(const quint32 scenarioID);

        void scenarioAdded(SecurityScenario newScenario);
        void scenarioRenamed(const quint32 scenarioID, QString newScenarioTitle, QString newScenarioText);

        void scenariesMustBeSaved(const QList<SecurityScenario> scenaries);
};

#endif // ADMINSCENARIOBOXLAYOUTCONTROLLER_H
