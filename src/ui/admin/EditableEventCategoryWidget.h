#ifndef EDITABLEEVENTCATEGORYWIDGET_H
#define EDITABLEEVENTCATEGORYWIDGET_H

#include <QWidget>
#include <QLineEdit>

#include "../user/EventCategoryWidget.h"

namespace Ui {
class EditableEventCategoryWidget;
}

// EditableEventCategoryWidget - класс для режима редактирования категорий администратором
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
