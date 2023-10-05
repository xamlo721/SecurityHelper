#ifndef INCIDENTCATEGORY_WIDGET_H
#define INCIDENTCATEGORY_WIDGET_H

#include <QWidget>

namespace Ui {
    class EventCategoryWidget;
}

class EventCategoryWidget : public QWidget {

    Q_OBJECT

    public:
        explicit EventCategoryWidget(quint32 id, QString title, QWidget *parent = nullptr);
        ~EventCategoryWidget();

        quint32 getId();

        QString getText();

    public slots:
        void onOpenIncidentButtonClicked();

    signals:
        void signalOpenIncident(quint32 incidentId, const bool isForAdminMode = false);

    private:
        quint32 id;
        QString text;
        Ui::EventCategoryWidget *ui;

};

#endif // INCIDENTCATEGORY_WIDGET_H
