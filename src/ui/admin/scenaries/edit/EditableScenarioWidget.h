#ifndef EDITABLESCENARIOWIDGET_H
#define EDITABLESCENARIOWIDGET_H

#include <QWidget>
#include <QLineEdit>

#include "src/items/BaseItem.h"

namespace Ui {
class EditableScenarioWidget;
}

class EditableScenarioWidget : public QWidget, public BaseItem {

    Q_OBJECT

    private:
        Ui::EditableScenarioWidget *ui;
        QString text;

    private slots:
        int slotEditingFinished();

    public:
        EditableScenarioWidget(const quint32 id, const QString title, const QString text, QWidget * parent = nullptr);
        ~EditableScenarioWidget();

        QString getText();

        void setFocus();

        bool hasFocus();

    public slots:

    signals:
        void editingFinished(EditableScenarioWidget * editableWidget);

};
#endif // EDITABLESCENARIOWIDGET_H
