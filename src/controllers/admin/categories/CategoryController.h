#ifndef CATEGORYCONTROLLER_H
#define CATEGORYCONTROLLER_H

#include <QObject>
#include <QMap>

#include "src/ui/admin/AdminCategoriesWidget.h"
#include "src/items/SecurityEventCategory.h"
#include "src/items/SecurityEvent.h"

class CategoryController : public QObject {

    Q_OBJECT

    private:
        AdminCategoriesWidget *ui;
        QMap<quint32, SecurityEventCategory> categories;
        QMap<quint32, SecurityEvent> allEvents;
        QList<SecurityEvent> availableEvents;
        QList<SecurityEvent> selectedEvents;

    public:
        explicit CategoryController(QObject *parent = nullptr);

        void init(AdminCategoriesWidget *categoryWidget);

        void setCategoryList(QMap<quint32, SecurityEventCategory> categories);


    private slots:
        void onCetegorySelected(quint32 categoryID);
        void onEventSelected(quint32 eventID);
        void onEventUnselected(quint32 eventID);

    signals:

};

#endif // CATEGORYCONTROLLER_H
