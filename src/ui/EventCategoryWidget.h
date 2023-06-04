#ifndef INCIDENTCATEGORY_WIDGET_H
#define INCIDENTCATEGORY_WIDGET_H

#include <QWidget>

namespace Ui {
    class EventCategoryWidget;
}

class EventCategoryWidget : public QWidget {

    Q_OBJECT

    public:
        explicit EventCategoryWidget(int id, QString title, QWidget *parent = nullptr);
        ~EventCategoryWidget();

        int getId();

    public slots:
        void onOpenIncidentButtonClicked();

    signals:
        void signalOpenIncident(int incidentId);

    private:
        int id;
        Ui::EventCategoryWidget *ui;

};

#endif // INCIDENTCATEGORY_WIDGET_H
