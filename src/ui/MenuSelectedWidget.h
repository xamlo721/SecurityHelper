#ifndef MENUSELECTEDWIDGET_H
#define MENUSELECTEDWIDGET_H

#include <QWidget>
#include <QMap>

#include "SelectedWidget.h"

namespace Ui {
    class MenuSelectedWidget;
}

class MenuSelectedWidget : public QWidget {

    Q_OBJECT

    private:
        Ui::MenuSelectedWidget *ui;
        qint32 selectedID;

    protected:
        QMap<quint32 , SelectedWidget * > widgets;

    public:
        explicit MenuSelectedWidget(QWidget *parent = nullptr);
        ~MenuSelectedWidget();

        void addWidgets(QList<SelectedWidget *> widgets);

        void addWidget(qint32 widgetID,  SelectedWidget * widget);

        SelectedWidget * getSelectedWidget();

        quint32 getSelectedWidgetID();

        void removeWidget(qint32 widgetID);

        void unselect();

        void select(quint32 widgetID);

        void clear();

    signals:
        void signalOnWidgetSelected(qint32 widgetID);

        void signalOnWidgetUnselected(qint32 widgetID);



    private slots:
        void onWidgetSelected(qint32 widgetID);
        void onWidgetUnselected(qint32 widgetID);

};

#endif // MENUSELECTEDWIDGET_H
