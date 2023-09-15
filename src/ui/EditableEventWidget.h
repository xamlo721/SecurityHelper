#ifndef EDITABLEEVENTWIDGET_H
#define EDITABLEEVENTWIDGET_H

#include <QWidget>

#include "EventWidget.h"

namespace Ui {
class EditableEventWidget;
}

class EditableEventWidget : public QWidget {

    Q_OBJECT

public:
    explicit EditableEventWidget(EventWidget * eventWidget, QWidget * parent = nullptr);
    ~EditableEventWidget();

private:
    quint32 id;
    Ui::EditableEventWidget *ui;

};

#endif // EDITABLEEVENTWIDGET_H
