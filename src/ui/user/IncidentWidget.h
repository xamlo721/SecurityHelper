#ifndef INCIDENT_WIDGET_H
#define INCIDENT_WIDGET_H

#include <QWidget>

namespace Ui {
    class IncidentWidget;
}

class IncidentWidget : public QWidget {

    Q_OBJECT

    public:
        explicit IncidentWidget(quint32 id, QString text, QWidget *parent = nullptr);
        ~IncidentWidget();

    signals:
        void signalIncidentOpen(quint32 incidentId);

    private slots:
        void onPuttonClicked();

    private:
        quint32 id;
        Ui::IncidentWidget *ui;
};

#endif // INCIDENT_H
