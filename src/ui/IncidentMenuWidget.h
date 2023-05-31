#ifndef INCIDENTMENU_WIDGET_H
#define INCIDENTMENU_WIDGET_H

#include <QWidget>

namespace Ui {
    class IncidentMenuWidget;
}

class IncidentMenuWidget : public QWidget {

    Q_OBJECT

    public:
        explicit IncidentMenuWidget(QWidget *parent = nullptr);
        ~IncidentMenuWidget();

    private:
        Ui::IncidentMenuWidget *ui;
};

#endif // INCIDENTMENU_WIDGET_H
