#ifndef ADMINEVENTDIALOG_H
#define ADMINEVENTDIALOG_H

#include <QDialog>

namespace Ui {
    class AdminEventDialog;
}

class AdminEventDialog : public QDialog {

    Q_OBJECT

    private:
        Ui::AdminEventDialog *ui;

    public:
        AdminEventDialog(QWidget *parent = nullptr);
        ~AdminEventDialog();

};

#endif // ADMINEVENTDIALOG_H
