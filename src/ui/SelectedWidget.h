#ifndef SELECTEDWIDGET_H
#define SELECTEDWIDGET_H

#include <QObject>
#include <QWidget>

namespace Ui {
    class SelectedWidget;
}


class SelectedWidget : public QWidget {

    Q_OBJECT

    public:
        SelectedWidget(quint32 id, QString title, QWidget *parent = nullptr);

        SelectedWidget(quint32 id, QString title, bool isSelected, QWidget *parent = nullptr);

        ~SelectedWidget();

        quint32 getId();

        QString getText();

        void setText(QString title);

        void select();

        void unselect();

    public slots:
        void onOpenIncidentButtonClicked();

    signals:
        void signalSelected(quint32 incidentId, const bool isForAdminMode = false);
        void signalUnselected(quint32 incidentId, const bool isForAdminMode = false);

    private:
        quint32 id;
        QString text;
        Ui::SelectedWidget *ui;

};

#endif // SELECTEDWIDGET_H
