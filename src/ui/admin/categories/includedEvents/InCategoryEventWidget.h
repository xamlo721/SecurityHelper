#ifndef INCATEGORYEVENTWIDGET_H
#define INCATEGORYEVENTWIDGET_H

#include <QWidget>

#include "src/items/BaseItem.h"

namespace Ui {
class InCategoryEventWidget;
}

class InCategoryEventWidget : public QWidget, public BaseItem {

    Q_OBJECT

    private:
        Ui::InCategoryEventWidget *ui;

    private slots:
        void onCheckBoxClicked();

    public:
        InCategoryEventWidget(const quint32 id, const QString title, QWidget *parent = nullptr);
        ~InCategoryEventWidget();

        void setUnselected();

        void setTitle(const QString text) override;

    public slots:


    signals:
        void signalEventSelected(const quint32 eventID);
        void signalEventUnselected(const quint32 eventID);
};

#endif // INCATEGORYEVENTWIDGET_H
