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
        UneditableEventWidget(const quint32 id, const QString title, QWidget *parent = nullptr);
        ~UneditableEventWidget();

        void initMenu();

        void callCustomMenu(const QPoint mousePosition);

        void setTitle(const QString title) override;

        void setUnselected();

    public slots:
        void slotEditEvent();

        void slotDeleteEvent();

    signals:
        void signalEditEvent(UneditableEventWidget * uneditableWidget);

        void signalDeleteEvent(UneditableEventWidget * uneditableWidget);

        void signalEventSelected(const quint32 eventID);
        void signalEventUnselected(const quint32 eventID);

};

#endif // UNEDITABLEEVENTWIDGET_H
