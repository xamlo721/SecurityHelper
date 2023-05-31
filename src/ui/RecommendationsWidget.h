#ifndef RECOMMENDATIONS_WIDGETS_H
#define RECOMMENDATIONS_WIDGETS_H

#include <QWidget>

namespace Ui {
    class RecommendationsWidget;
}

class RecommendationsWidget : public QWidget {

    Q_OBJECT

    public:
        explicit RecommendationsWidget(QWidget *parent = nullptr);
        ~RecommendationsWidget();

    private:
        Ui::RecommendationsWidget *ui;

};

#endif // RECOMMENDATIONS_WIDGETS_H
