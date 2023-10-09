#ifndef INSCENARIOINCIDENTWIDGET_H
#define INSCENARIOINCIDENTWIDGET_H

#include <QWidget>

#include "src/items/BaseItem.h"

namespace Ui {
class InScenarioIncidentWidget;
}

class InScenarioIncidentWidget : public QWidget, public BaseItem {

    Q_OBJECT

    private:
        Ui::InScenarioIncidentWidget *ui;
        QString text;

    private slots:
        void onCheckBoxClicked();

    public:
        InScenarioIncidentWidget(const quint32 id, const QString text, const QString title, QWidget *parent = nullptr);
        ~InScenarioIncidentWidget();

        void setUnselected();

        void setTitle(const QString text) override;

    public slots:


    signals:
        void signalIncidentSelected(const quint32 incidentID);
        void signalIncidentUnselected(const quint32 incidentID);
};

#endif // INSCENARIOINCIDENTWIDGET_H
