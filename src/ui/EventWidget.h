#ifndef EVENTWIDGET_WIDGET_H
#define EVENTWIDGET_WIDGET_H

#include <QWidget>

namespace Ui {
    class EventWidget;
}

class EventWidget : public QWidget {

    Q_OBJECT

    public:
        explicit EventWidget(QWidget *parent = nullptr);
        ~EventWidget();

    private:
        Ui::EventWidget *ui;
};

#endif // EVENTWIDGET_WIDGET_H
