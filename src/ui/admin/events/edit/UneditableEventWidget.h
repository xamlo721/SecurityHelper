#ifndef UNEDITABLEEVENTWIDGET_H
#define UNEDITABLEEVENTWIDGET_H

#include <QWidget>

#include "src/items/BaseItem.h"
#include "src/ui/admin/UneditableItemMenu.h"

namespace Ui {
class UneditableEventWidget;
}

class UneditableEventWidget : public QWidget, public BaseItem {

    Q_OBJECT

    private:
        /// Переменная кастомизированного контекстного меню
        UneditableItemMenu *customMenu;
        /// Переменная, хранящая в себе данные интерфейса
        Ui::UneditableEventWidget *ui;

    private slots:
        void onCheckBoxClicked();

    public:
        explicit UneditableEventWidget(const quint32 id, const QString title, QWidget *parent = nullptr);
        ~UneditableEventWidget();


        void initMenu();

        void callCustomMenu(const QPoint mousePosition);

        void setText(const QString text) override;

    public slots:
        void slotEditCategory();

        void slotDeleteCategory();

    signals:
        void signalEditCategory(UneditableEventWidget * uneditableCategory);

        void signalDeleteCategory(UneditableEventWidget * uneditableCategory);

        void signalCategorySelected(const quint32 categoryID);
        void signalCategoryUnselected(const quint32 categoryID);
};

#endif // UNEDITABLEEVENTWIDGET_H
