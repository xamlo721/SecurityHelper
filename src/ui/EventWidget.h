#ifndef EVENTWIDGET_WIDGET_H
#define EVENTWIDGET_WIDGET_H

#include <QWidget>

namespace Ui {
    class EventWidget;
}

class EventWidget : public QWidget {

    Q_OBJECT

    public:
        explicit EventWidget(quint32 id, QString text, bool isChecked, QWidget *parent = nullptr);
        ~EventWidget();

        quint32 getId();

        QString getText();

    signals:
        void signalEventSelected(quint32 eventID);

    private slots:
        void onCheckBoxClicked();

    private:
        quint32 id;
        QString text;
        Ui::EventWidget *ui;
};

#endif // EVENTWIDGET_WIDGET_H
