#ifndef UNEDITABLEINCIDENTWIDGET_H
#define UNEDITABLEINCIDENTWIDGET_H

#include <QWidget>

#include "src/items/BaseItem.h"
#include "src/ui/admin/UneditableItemMenu.h"

namespace Ui {
class UneditableIncidentWidget;
}

class UneditableIncidentWidget : public QWidget, public BaseItem {

    Q_OBJECT

    private:
        /// Переменная кастомизированного контекстного меню
        UneditableItemMenu *customMenu;
        /// Переменная, хранящая в себе данные интерфейса
        Ui::UneditableIncidentWidget *ui;

    private slots:
        void onCheckBoxClicked();

    public:
        UneditableIncidentWidget(const quint32 id, const QString title, QWidget *parent = nullptr);
        ~UneditableIncidentWidget();

        void initMenu();

        void callCustomMenu(const QPoint mousePosition);

        void setTitle(const QString title) override;

        void setUnselected();

    public slots:
        void slotEditIncident();

        void slotDeleteIncident();

    signals:
        void signalEditIncident(UneditableIncidentWidget * uneditableWidget);

        void signalDeleteIncident(UneditableIncidentWidget * uneditableWidget);

        void signalIncidentSelected(const quint32 incidentID);
        void signalIncidentUnselected(const quint32 incidentID);

};

#endif // UNEDITABLEINCIDENTWIDGET_H
