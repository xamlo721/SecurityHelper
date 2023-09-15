#ifndef EDITABLEEVENTCATEGORYWIDGET_H
#define EDITABLEEVENTCATEGORYWIDGET_H

#include <QWidget>
#include <QLineEdit>

#include "EventCategoryWidget.h"

namespace Ui {
class EditableEventCategoryWidget;
}

class EditableEventCategoryWidget : public QWidget {

    Q_OBJECT

public:
    explicit EditableEventCategoryWidget(EventCategoryWidget * categoryWidget, QWidget * parent = nullptr);
    ~EditableEventCategoryWidget();

private:
    quint32 id;
    Ui::EditableEventCategoryWidget * ui;

};

#endif // EDITABLEEVENTCATEGORYWIDGET_H
