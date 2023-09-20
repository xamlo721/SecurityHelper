#ifndef INCIDENTMENU_WIDGET_H
#define INCIDENTMENU_WIDGET_H

#include <QWidget>

#include "src/ui/user/IncidentWidget.h"

namespace Ui {
    class IncidentMenuWidget;
}

class IncidentMenuWidget : public QWidget {

    Q_OBJECT

    public:
        explicit IncidentMenuWidget(QWidget *parent = nullptr);
        ~IncidentMenuWidget();

        void clear();
        void addcIncidentWidget(IncidentWidget * widget);

    private:
        Ui::IncidentMenuWidget *ui;
};

#endif // INCIDENTMENU_WIDGET_H
