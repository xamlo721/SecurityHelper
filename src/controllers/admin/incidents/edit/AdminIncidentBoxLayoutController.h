#ifndef ADMININCIDENTBOXLAYOUTCONTROLLER_H
#define ADMININCIDENTBOXLAYOUTCONTROLLER_H

#include <QObject>

#include "src/items/SecurityIncident.h"

#include "src/ui/admin/incidents/edit/UneditableIncidentWidget.h"
#include "src/ui/admin/incidents/edit/EditableIncidentWidget.h"

#include "src/ui/admin/incidents/edit/AdminIncidentBoxLayout.h"

#include "src/ui/admin/incidents/edit/IncidentWidgetStorage.h"

class AdminIncidentBoxLayoutController : public QObject {

    Q_OBJECT

    private:
        /// Управляемый бокс событий
        AdminIncidentBoxLayout *boxLayoutIncidents;

        /// Список событий, полученных из ядра программы
        QList<SecurityIncident> incidents;
        /// Список выбранных администратором событий
        QList<SecurityIncident> selectedIncidents;
        /// Хранилище пар не редактирумого и редактируемого виджета
        IncidentWidgetStorage widgetStorage;

        SecurityIncident addIncident();
        void addIncidentWidget(SecurityIncident incident);

        void deleteIncident(const quint32 incidentID);
        void deleteIncidentWidget(const quint32 incidentID);

        void renameIncident(const quint32 widgetID, const QString widgetTitle, const QString widgetText);

        void unselectAllIncidents();

        void enableAllIncidents();
        void disableAllIncidents();

    private slots:
        void slotShowEditableWidget(UneditableIncidentWidget *uneditableWidget);
        void slotShowUneditableWidget(EditableIncidentWidget *editableWidget);

        void slotDeleteIncident(UneditableIncidentWidget * uneditableWidget);

        void onIncidentSelected(const quint32 incidentID);
        void onIncidentUnselected(const quint32 incidentID);

    public:
        explicit AdminIncidentBoxLayoutController(QObject *parent = nullptr);

        void init(QVBoxLayout *editMenuBoxLayoutIncidents);

    public slots:
        void setIncidentList(const QList<SecurityIncident> incidents);

        void slotAddIncidentButtonPressed();
        void slotDeleteSelectedIncidentsButtonPressed();

    signals:
        void signalSelectedIncidentsNotEmpty();
        void signalSelectedIncidentsEmpty();

        void incidentIsActive();
        void incidentIsNotActive();

        void incidentIsOpened(quint32 incidentID);
        void incidentIsClosed(const quint32 incidentID);

        void incidentAdded(SecurityIncident newIncident);
        void incidentRenamed(const quint32 incidentID, QString newIncidentTitle, QString newIncidentText);

        void incidentsMustBeSaved(const QList<SecurityIncident> incidents);
};

#endif // ADMININCIDENTBOXLAYOUTCONTROLLER_H
