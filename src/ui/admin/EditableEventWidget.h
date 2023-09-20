#ifndef EDITABLEEVENTWIDGET_H
#define EDITABLEEVENTWIDGET_H

#include <QWidget>

#include "../user/EventWidget.h"

namespace Ui {
class EditableEventWidget;
}

// EditableEventWidget - класс для режима редактирования событий администратором
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
