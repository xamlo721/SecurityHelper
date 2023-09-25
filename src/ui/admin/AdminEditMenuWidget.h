#ifndef ADMINEDITMENUWIDGET_H
#define ADMINEDITMENUWIDGET_H

#include <QWidget>

#include "qboxlayout.h"
#include "src/ui/admin/categories/UneditableEventCategoryWidget.h"
#include "src/ui/admin/categories/EditableEventCategoryWidget.h"

namespace Ui {
class AdminEditMenuWidget;
}

class AdminEditMenuWidget : public QWidget {

    Q_OBJECT

    public:
        explicit AdminEditMenuWidget(QWidget *parent = nullptr);
        ~AdminEditMenuWidget();

        void addCategory(UneditableEventCategoryWidget *uneditableCategory);
        void clearCategories();

        void makeCategoryEditable(UneditableEventCategoryWidget *uneditableCategory);
        void makeCategoryUneditable(EditableEventCategoryWidget *editableCategory);

    public slots:

    private:
        QVBoxLayout *box_layout;
        Ui::AdminEditMenuWidget *ui;

        void initUneditableCategory(UneditableEventCategoryWidget *uneditableCategory);
        void initEditableCategory(EditableEventCategoryWidget *editableCategory);
    private slots:

    signals:
        /// Сигнал, сообщающий о вызове в контекстном меню действия Редактировать
        void signalEditCategory(UneditableEventCategoryWidget * uneditableCategory);
        /// Сигнал, сообщающий о вызове в контекстном меню действия Удалить
        void signalDeleteCategory();

        /// Сигнал, сообщающий о завершении редактирования виджета
        void editingFinished(EditableEventCategoryWidget * editableCategory);

};

#endif // ADMINEDITMENUWIDGET_H
