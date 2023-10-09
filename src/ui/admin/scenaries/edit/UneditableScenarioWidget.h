#ifndef UNEDITABLESCENARIOWIDGET_H
#define UNEDITABLESCENARIOWIDGET_H

#include <QWidget>

#include "src/items/BaseItem.h"
#include "src/ui/admin/UneditableItemMenu.h"

namespace Ui {
class UneditableScenarioWidget;
}

class UneditableScenarioWidget : public QWidget, public BaseItem {

    Q_OBJECT

    private:

        UneditableItemMenu *customMenu;

        Ui::UneditableScenarioWidget *ui;

    private slots:
        void onCheckBoxClicked();

    public:
        UneditableScenarioWidget(const quint32 id, const QString title, QWidget *parent = nullptr);
        ~UneditableScenarioWidget();

        void initMenu();

        void callCustomMenu(const QPoint mousePosition);

        void setTitle(const QString title) override;

        void setUnselected();

    public slots:
        void slotEditScenario();

        void slotDeleteScenario();

    signals:
        void signalEditScenario(UneditableScenarioWidget * uneditableWidget);

        void signalDeleteScenario(UneditableScenarioWidget * uneditableWidget);

        void signalScenarioSelected(const quint32 incidentID);
        void signalScenarioUnselected(const quint32 incidentID);
};

#endif // UNEDITABLESCENARIOWIDGET_H
