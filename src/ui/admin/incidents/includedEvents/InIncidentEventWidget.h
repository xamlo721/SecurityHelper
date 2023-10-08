#ifndef ININCIDENTEVENTWIDGET_H
#define ININCIDENTEVENTWIDGET_H

#include <QWidget>

#include "src/items/BaseItem.h"

namespace Ui {
class InIncidentEventWidget;
}

class InIncidentEventWidget : public QWidget, public BaseItem {

    Q_OBJECT

    private:
        Ui::InIncidentEventWidget *ui;

    private slots:
        void onCheckBoxClicked();

    public:
        InIncidentEventWidget(const quint32 id, const QString title, QWidget *parent = nullptr);
        ~InIncidentEventWidget();

        void setUnselected();

        void setTitle(const QString text) override;

    public slots:


    signals:
        void signalEventSelected(const quint32 eventID);
        void signalEventUnselected(const quint32 eventID);
};

#endif // ININCIDENTEVENTWIDGET_H
