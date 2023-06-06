#ifndef INCIDENT_WIDGET_H
#define INCIDENT_WIDGET_H

#include <QWidget>

namespace Ui {
    class IncidentWidget;
}

class IncidentWidget : public QWidget {

    Q_OBJECT

    public:
        explicit IncidentWidget(int id, QString text, QWidget *parent = nullptr);
        ~IncidentWidget();

    signals:
        void signalIncidentOpen(int incidentId);

    private slots:
        void onPuttonClicked();

    private:
        int id;
        Ui::IncidentWidget *ui;
};

#endif // INCIDENT_H
