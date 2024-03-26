#ifndef ADMINSCENARIESDIALOG_H
#define ADMINSCENARIESDIALOG_H

#include <QDialog>

namespace Ui {
    class AdminScenariesDialog;
}

class AdminScenariesDialog : public QDialog {

    Q_OBJECT

    private:
        Ui::AdminScenariesDialog *ui;

    public:
        AdminScenariesDialog(QWidget *parent = nullptr);
        ~AdminScenariesDialog();

        void setEditableText(QString name);

};

#endif // ADMINSCENARIESDIALOG_H
