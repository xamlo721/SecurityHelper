#ifndef EDITCATORGYDIALOG_H
#define EDITCATORGYDIALOG_H

#include <QDialog>

namespace Ui {
    class AdminEditCatorgyDialog;
}

class AdminEditCatorgyDialog : public QDialog {

    Q_OBJECT

    private:
        Ui::AdminEditCatorgyDialog *ui;

    public:
        AdminEditCatorgyDialog(QWidget *parent = nullptr);
        ~AdminEditCatorgyDialog();

        void setEditableText(QString name);

    private slots:

        void onSaveButtonPressed();

    signals:
        void signalItemNameChanged(QString name);

};

#endif // EDITCATORGYDIALOG_H
