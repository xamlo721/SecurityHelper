#ifndef ADMINEVENTCATEGORYBOXLAYOUTCONTROLLER_H
#define ADMINEVENTCATEGORYBOXLAYOUTCONTROLLER_H

#include <QObject>
#include <QMessageBox>

#include "src/items/SecurityEventCategory.h"

#include "src/ui/admin/categories/edit/UneditableEventCategoryWidget.h"
#include "src/ui/admin/categories/edit/EditableEventCategoryWidget.h"

#include "src/ui/admin/categories/edit/AdminEventCategoryBoxLayout.h"

#include "src/ui/admin/categories/edit/EventCategoryWidgetStorage.h"
/**
 * @brief AdminEventCategoryBoxLayoutController - контроллер бокса категорий событий.
 * Устанавливает список виджетов в боксе и изменением виджетов в соответствии с нуждами
 * администратора.
 */
class AdminEventCategoryBoxLayoutController : public QObject {

    Q_OBJECT

    private:
        /// Управляемый бокс событий
        AdminEventCategoryBoxLayout *boxLayoutCategories;

        /// Список категорий, полученных из ядра программы
        QList<SecurityEventCategory> categories;
        /// Список выбранных администратором категорий
        QList<SecurityEventCategory> selectedCategories;
        /// Хранилище пар не редактирумого и редактируемого виджета
        EventCategoryWidgetStorage widgetStorage;

        void addCategory();

        /**
         *  @brief deleteCategory - метод для удаления категорий из списка контроллера
         *  @param categoryID - id категории.
         *      Внутренний метод, вызывается в slotEmptyWidget и slotDeleteCategory.
         */
        void deleteCategory(const quint32 categoryID);

        /**
         *  @brief renameCategory - метод для переименования категорий из списка контроллера
         *  @param uneditableCategory - не редактируемый виджет категории, категорию которого
         *  нужно переименовать в списке.
         *      Внутренний метод, вызывается в slotMakeCategoryUneditable.
         */
        void renameCategory(const quint32 widgetID, const QString widgetText);

        void unselectAllCategories();

        void enableAllCategories();
        void disableAllCategories();

    private slots:
        void slotShowEditableWidget(UneditableEventCategoryWidget *uneditableWidget);

        void slotShowUneditableWidget(EditableEventCategoryWidget *editableWidget);

        /**
         *  @brief slotEmptyWidget - приватный слот для удаления пустого редактируемого виджета.
         *  @param editableCategory - редактируемый виджет категории, который необходимо удалить.
         *      Срабатывает при получении сигнала от редактируемого виджета о том, что при завершении
         *     редактирования виджета он остался пустым.
         */
        void slotEmptyWidget(EditableEventCategoryWidget * editableWidget);

        /**
         *  @brief slotDeleteCategory - приватный слот для удаления не редактируемого виджета по
         *  запросу администратора через контекстное меню.
         *  @param uneditableCategory - не редактируемый виджет категории, который необходимо удалить.
         *      Срабатывает при получении сигнала от не редактируемого виджета о выборе действия Удалить в
         *     контекстном меню.
         */
        void slotDeleteCategory(UneditableEventCategoryWidget * uneditableWidget);

        void onCategorySelected(const quint32 categoryID);
        void onCategoryUnselected(const quint32 categoryID);

    public:
        /**
         *  @brief AdminEventCategoryBoxLayoutController - не изменяемый конструктор по умолчанию
         *  @param parent - родительский объект в иерархии Qt.
         */
        explicit AdminEventCategoryBoxLayoutController(QObject *parent = nullptr);

        void init(QVBoxLayout *editMenuBoxLayoutCategories);

    public slots:
        /**
         *  @brief setCategoryList - публичный слот, устанавливающий список виджетов категорий в
         *  боксе категорий.
         *  @param categories - список категорий.
         *      Срабатывает при получении сигнала от ядра программы, по которому передается
         *    список категорий.
         */
        void setCategoryList(const QList<SecurityEventCategory> categories);

        void slotAddCategoryButtonPressed();
        void slotDeleteSelectedCategoriesButtonPressed();

    signals:
        void signalSelectedCategoriesNotEmpty();
        void signalSelectedCategoriesEmpty();

        void categoriesSet();

        void categoryIsActive();
        void categoryIsNotActive();

};

#endif // ADMINEVENTCATEGORYBOXLAYOUTCONTROLLER_H
