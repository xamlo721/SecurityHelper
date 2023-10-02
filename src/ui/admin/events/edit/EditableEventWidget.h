#ifndef EDITABLEEVENTWIDGET_H
#define EDITABLEEVENTWIDGET_H

#include <QWidget>
#include <QLineEdit>

#include "src/items/BaseItem.h"

namespace Ui {
class EditableEventWidget;
}


class EditableEventWidget : public QWidget, public BaseItem {

    Q_OBJECT
    private:
        Ui::EditableEventWidget *ui;

    private slots:
        int slotEditingFinished();

    public:
        explicit EditableEventWidget(const quint32 id, const QString title, QWidget * parent = nullptr);

        ~EditableEventWidget();


        void setFocus();

        bool hasFocus();

    public slots:

    signals:

        void editingFinished(EditableEventWidget * editableWidget);

        void emptyWidget(EditableEventWidget * editableWidget);

};

#endif // EDITABLEEVENTWIDGET_H
