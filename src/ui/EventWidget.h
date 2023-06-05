#ifndef EVENTWIDGET_WIDGET_H
#define EVENTWIDGET_WIDGET_H

#include <QWidget>

namespace Ui {
    class EventWidget;
}

class EventWidget : public QWidget {

    Q_OBJECT

    public:
        explicit EventWidget(int id, QString text, QWidget *parent = nullptr);
        ~EventWidget();

        int getId();
    signals:
        void signalEventSelected(int eventID);

    private:
        int id;
        QString text;
        Ui::EventWidget *ui;
};

#endif // EVENTWIDGET_WIDGET_H
