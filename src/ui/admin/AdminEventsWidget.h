#ifndef ADMINEVENTSWIDGET_H
#define ADMINEVENTSWIDGET_H

#include <QWidget>

namespace Ui {
class AdminEventsWidget;
}

class AdminEventsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminEventsWidget(QWidget *parent = nullptr);
    ~AdminEventsWidget();

private:
    Ui::AdminEventsWidget *ui;
};

#endif // ADMINEVENTSWIDGET_H
