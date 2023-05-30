#ifndef INCIDENT_H
#define INCIDENT_H

#include <QWidget>

namespace Ui {
    class Incident;
}

class Incident : public QWidget {

    Q_OBJECT

    public:
        explicit Incident(QWidget *parent = nullptr);
        ~Incident();

    private:
        Ui::Incident *ui;
};

#endif // INCIDENT_H
