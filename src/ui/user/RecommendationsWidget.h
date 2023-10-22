#ifndef RECOMMENDATIONS_WIDGETS_H
#define RECOMMENDATIONS_WIDGETS_H

#include <QWidget>

namespace Ui {
    class RecommendationsWidget;
}

class RecommendationsWidget : public QWidget {

    Q_OBJECT

    public:
        RecommendationsWidget(QWidget *parent = nullptr);
        RecommendationsWidget(QString textContainment, QString textFixes, QString textRestore, QWidget *parent = nullptr);
        ~RecommendationsWidget();

        void setTextContaiment(QString textContainment);
        void setTextFixes(QString textFixes);
        void setTextRestore(QString textRestore);

        void clear();

    private:
        Ui::RecommendationsWidget *ui;

};

#endif // RECOMMENDATIONS_WIDGETS_H
