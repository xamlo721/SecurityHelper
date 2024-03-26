#ifndef ADMINRECOMMENDATIONDIALOG_H
#define ADMINRECOMMENDATIONDIALOG_H

#include <QDialog>

namespace Ui {
    class AdminRecommendationDialog;
}

class AdminRecommendationDialog : public QDialog {

    Q_OBJECT
    private:
        Ui::AdminRecommendationDialog *ui;

    public:
        AdminRecommendationDialog(QWidget *parent = nullptr);
        ~AdminRecommendationDialog();

        void setEditableText(QString name);



};

#endif // ADMINRECOMMENDATIONDIALOG_H
