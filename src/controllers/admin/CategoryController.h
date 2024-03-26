#ifndef CATEGORYCONTROLLER_H
#define CATEGORYCONTROLLER_H

#include <QObject>
#include <QMap>

#include "src/items/SecurityEventCategory.h"
#include "src/items/SecurityEvent.h"

#include "src/logic/Database.h"

#include "src/ui/admin/AdminCategoriesWidget.h"
#include "src/ui/admin/dialogs/AdminEditCatorgyDialog.h"

class CategoryController : public QObject {

    Q_OBJECT

    private:
        Database copyDatabase;
        AdminCategoriesWidget *ui;
        AdminEditCatorgyDialog * editDialog;
        QMap<quint32, SecurityEventCategory> categories;
        QMap<quint32, SecurityEvent> allEvents;
        QList<SecurityEvent> availableEvents;
        QList<SecurityEvent> selectedEvents;

        ///ID выбранной каьешлоии
        quint32 categoryEventID;

    public:
        explicit CategoryController(QObject *parent = nullptr);

        void init(AdminCategoriesWidget *categoryWidget);

    private:
        void resetSelectedEvents(QList<SecurityEvent> freeEvents);
        void resetAvailableEvents(QList<SecurityEvent> freeEvents);

    public slots:

        void onDatabaseUpdated(const Database & db);


    private slots:

        /**
         * @brief slotItemNameEdited - случает, когда меняется имя
         * @param name - новое имя объекта
         */
        void slotItemNameEdited(QString name);

        void onCetegorySelected(quint32 categoryID);
        void onCetegoryUnselected(quint32 categoryID);
        void onCategoryAdded();
        void onCategoryEditRequest(quint32 categoryID);
        void onCategoryUpdated(quint32 categoryID, QString categoryName);
        void onCategoryDeleted(quint32 categoryID);
        void onEventSelected(quint32 eventID);
        void onEventUnselected(quint32 eventID);

    signals:
        /**
         * @brief signalAdminAddCategory - сигнал вызывается
         * при кажатии добавлении администратором новой категории
         */
        void signalAdminAddCategory();

        /**
         * @brief signalAdminUpdateCategory - сигнал вызывается
         * при изменении администратором существующей категории
         * @param categoryID - ID выбранной категории
         * @param category - изменённая категория
         */
        void signalAdminUpdateCategory(quint32 categoryID, SecurityEventCategory category);

        /**
         * @brief signalAdminDeleteCategory - сигнал вызывается
         * при удалении администратором существующей категории
         * @param categoryID - ID выбранной категории
         */
        void signalAdminDeleteCategory(quint32 categoryID);

};

#endif // CATEGORYCONTROLLER_H
