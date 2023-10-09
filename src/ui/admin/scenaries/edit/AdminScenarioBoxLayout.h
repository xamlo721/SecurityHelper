#ifndef ADMINSCENARIOBOXLAYOUT_H
#define ADMINSCENARIOBOXLAYOUT_H

#include <QObject>
#include "qboxlayout.h"

#include "src/ui/admin/scenaries/edit/UneditableScenarioWidget.h"
#include "src/ui/admin/scenaries/edit/EditableScenarioWidget.h"

class AdminScenarioBoxLayout : public QObject {

    Q_OBJECT

    private:
        QVBoxLayout *boxLayoutScenaries;

        QList<QVBoxLayout*> widgetBoxLayout;


        void initUneditableWidget(UneditableScenarioWidget *uneditableWidget);

        void initEditableWidget(EditableScenarioWidget *editableWidget);

    private slots:

    public:
        explicit AdminScenarioBoxLayout(QObject *parent = nullptr);


        void init(QVBoxLayout *boxLayout);

        void addScenarioWidget(UneditableScenarioWidget *uneditableWidget, EditableScenarioWidget *editableWidget);
        void deleteScenarioWidget(UneditableScenarioWidget *uneditableWidget);

        void clearScenaries();

        void showEditableWidget(UneditableScenarioWidget *uneditableWidget, EditableScenarioWidget *editableWidget);
        void showUneditableWidget(EditableScenarioWidget *editableWidget, UneditableScenarioWidget *uneditableWidget);

        void unselectUneditableWidget(UneditableScenarioWidget *uneditableWidget);

        void enableUneditableWidget(UneditableScenarioWidget *uneditableWidget);
        void disableUneditableWidget(UneditableScenarioWidget *uneditableWidget);

    public slots:

    signals:
        void signalEditScenario(UneditableScenarioWidget * uneditableWidget);
        void editingFinished(EditableScenarioWidget * editableWidget);

        void signalDeleteScenario(UneditableScenarioWidget * uneditableWidget);

        void signalScenarioSelected(const quint32 incidentID);
        void signalScenarioUnselected(const quint32 incidentID);
};

#endif // ADMINSCENARIOBOXLAYOUT_H
