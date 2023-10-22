#ifndef INCIDENTMENU_WIDGET_H
#define INCIDENTMENU_WIDGET_H

#include <QWidget>

#include "src/ui/user/IncidentWidget.h"

namespace Ui {
    class IncidentMenuWidget;
}

class IncidentMenuWidget : public QWidget {

    Q_OBJECT

    private:
        Ui::IncidentMenuWidget *ui;

    public:
        explicit IncidentMenuWidget(QWidget *parent = nullptr);
        ~IncidentMenuWidget();

        void clear();
        void addIncidentWidget(IncidentWidget * widget);

};

#endif // INCIDENTMENU_WIDGET_H
