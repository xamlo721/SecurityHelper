#ifndef INCIDENT_WIDGET_H
#define INCIDENT_WIDGET_H

#include <QWidget>

namespace Ui {
    class IncidentWidget;
}

class IncidentWidget : public QWidget {

    Q_OBJECT

    public:
        explicit IncidentWidget(QWidget *parent = nullptr);
        ~IncidentWidget();

    private:
        Ui::IncidentWidget *ui;
};

#endif // INCIDENT_H
