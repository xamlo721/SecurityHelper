#ifndef SCENARIOWIDGETSTORAGE_H
#define SCENARIOWIDGETSTORAGE_H

#include "src/ui/admin/scenaries/edit/EditableScenarioWidget.h"
#include "src/ui/admin/scenaries//edit/UneditableScenarioWidget.h"

class ScenarioWidgetStorage {

    private:
        QList<UneditableScenarioWidget*> uneditableWidgets;
        QList<EditableScenarioWidget*> editableWidgets;
        QList<quint32> widgetNumbers;

        void sortWidgetNumbers();

    public:
        explicit ScenarioWidgetStorage();

        void appendWidget(UneditableScenarioWidget *uneditableWidget, EditableScenarioWidget *editableWidget);
        void removeWidget(quint32 widgetID);

        UneditableScenarioWidget *getUneditableWidget(quint32 widgetID);
        EditableScenarioWidget *getEditableWidget(quint32 widgetID);
};

#endif // SCENARIOWIDGETSTORAGE_H
