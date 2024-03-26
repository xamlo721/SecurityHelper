#ifndef ADMININCIDENTDIALOG_H
#define ADMININCIDENTDIALOG_H

#include <QDialog>

namespace Ui {
    class AdminIncidentDialog;
}

class AdminIncidentDialog : public QDialog {

    Q_OBJECT

    private:
        Ui::AdminIncidentDialog *ui;

    public:
        AdminIncidentDialog(QWidget *parent = nullptr);
        ~AdminIncidentDialog();

        void setEditableText(QString name);

    private slots:

        void onSaveButtonPressed();

    signals:
        void signalItemNameChanged(QString name);

};

#endif // ADMININCIDENTDIALOG_H
