#ifndef INCIDENTCATEGORYWIDGET_H
#define INCIDENTCATEGORYWIDGET_H

#include <QWidget>

namespace Ui {
    class IncidentCategoryWidget;
}

class IncidentCategoryWidget : public QWidget {

    Q_OBJECT

    public:
        explicit IncidentCategoryWidget(int id, QString title, QWidget *parent = nullptr);
        ~IncidentCategoryWidget();

        void getId();

    private:
        int id;
        Ui::IncidentCategoryWidget *ui;

};

#endif // INCIDENTCATEGORYWIDGET_H
