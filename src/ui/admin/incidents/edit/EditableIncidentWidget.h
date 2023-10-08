#ifndef EDITABLEINCIDENTWIDGET_H
#define EDITABLEINCIDENTWIDGET_H

#include <QWidget>
#include <QLineEdit>

#include "src/items/BaseItem.h"

namespace Ui {
class EditableIncidentWidget;
}

class EditableIncidentWidget : public QWidget, public BaseItem {

    Q_OBJECT

    private:
        Ui::EditableIncidentWidget *ui;
        QString text;

    private slots:
        int slotEditingFinished();

    public:
        EditableIncidentWidget(const quint32 id, const QString title, const QString text, QWidget * parent = nullptr);
        ~EditableIncidentWidget();

        QString getText();

        void setFocus();

        bool hasFocus();

    public slots:

    signals:

        void editingFinished(EditableIncidentWidget * editableWidget);

};

#endif // EDITABLEINCIDENTWIDGET_H
