#ifndef ADMININCIDENTSWIDGET_H
#define ADMININCIDENTSWIDGET_H

#include <QWidget>

namespace Ui {
class AdminIncidentsWidget;
}

class AdminIncidentsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminIncidentsWidget(QWidget *parent = nullptr);
    ~AdminIncidentsWidget();

private:
    Ui::AdminIncidentsWidget *ui;
};

#endif // ADMININCIDENTSWIDGET_H
