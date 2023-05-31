#ifndef INCIDENTMENU_H
#define INCIDENTMENU_H

#include <QWidget>

namespace Ui {
    class IncidentMenu;
}

class IncidentMenu : public QWidget {

    Q_OBJECT

    public:
        explicit IncidentMenu(QWidget *parent = nullptr);
        ~IncidentMenu();

    private:
        Ui::IncidentMenu *ui;
};

#endif // INCIDENTMENU_H
