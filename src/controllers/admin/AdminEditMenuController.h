#ifndef ADMINEDITMENUCONTROLLER_H
#define ADMINEDITMENUCONTROLLER_H

#include <QObject>

#include "src/items/SecurityEventCategory.h"

#include "src/ui/admin/AdminEditMenuWidget.h"
#include "src/ui/admin/categories/UneditableEventCategoryWidget.h"
#include "src/ui/admin/categories/EditableEventCategoryWidget.h"

class AdminEditMenuController : public QObject {

    Q_OBJECT

    public:
        explicit AdminEditMenuController(QObject *parent = nullptr);

        void init(AdminEditMenuWidget *editMenu);

    public slots:
        void setCategoryList(QList<SecurityEventCategory> categories);

        void makeCategoryEditable(UneditableEventCategoryWidget *uneditableCategory);
        void makeCategoryUneditable(EditableEventCategoryWidget *editableCategory);

    private:
        AdminEditMenuWidget *editMenuWidget;
        QList<SecurityEventCategory> categories;
        QMap<quint32, SecurityEventCategory> active_categories;
        quint32 categories_number = 0;

    private slots:


    signals:

};

#endif // ADMINEDITMENUCONTROLLER_H
