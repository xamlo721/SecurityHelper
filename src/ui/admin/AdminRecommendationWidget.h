#ifndef ADMINRECOMMENDATIONWIDGET_H
#define ADMINRECOMMENDATIONWIDGET_H

#include <QWidget>

namespace Ui {
class AdminRecommendationWidget;
}

class AdminRecommendationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AdminRecommendationWidget(QWidget *parent = nullptr);
    ~AdminRecommendationWidget();

private:
    Ui::AdminRecommendationWidget *ui;
};

#endif // ADMINRECOMMENDATIONWIDGET_H
