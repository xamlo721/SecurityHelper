#ifndef ADMINEVENTCATEGORYBOXLAYOUTCONTROLLER_H
#define ADMINEVENTCATEGORYBOXLAYOUTCONTROLLER_H

#include <QObject>

#include "src/items/SecurityEventCategory.h"

#include "src/ui/admin/categories/UneditableEventCategoryWidget.h"
#include "src/ui/admin/categories/EditableEventCategoryWidget.h"

#include "src/ui/admin/AdminEventCategoryBoxLayout.h"

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

    private slots:
        /**
         *  @brief makeCategoryEditable - приватный слот для изменения не редактируемого виджета на редактируемый
         *  для возможности изменения имени категории.
         *  @param uneditableCategory - не редактируемый виджет категории, который необходимо изменить.
         *      Срабатывает при получении сигнала от не редактируемого виджета о запросе администратора.
         */
        void makeCategoryEditable(UneditableEventCategoryWidget *uneditableCategory);
        /**
         *  @brief makeCategoryUneditable - приватный слот для изменения редактируемого виджета на не редактируемый
         *  при завершении редактирования администратором.
         *  @param editableCategory - редактируемый виджет категории, который необходимо изменить.
         *      Срабатывает при получении сигнала от редактируемого виджета о завершении редактирования
         *    администратором .
         */
        void makeCategoryUneditable(EditableEventCategoryWidget *editableCategory);

    public:
        /**
         *  @brief AdminEventCategoryBoxLayoutController - не изменяемый конструктор по умолчанию
         *  @param parent - родительский объект в иерархии Qt.
         */
        explicit AdminEventCategoryBoxLayoutController(QObject *parent = nullptr);

        /**
         *  @brief init - метод, инициализирующий бокс категорий в данном классе
         *  из бокса категорий уже находящегося в AdminEditMenuWidget для его управления
         *  данным классом.
         *  @param boxLayout - бокс категорий, находящийся в AdminEditMenuWidget.
         */
        void init(QVBoxLayout *editMenuBoxLayoutCategories);

    public slots:
        /**
         *  @brief setCategoryList - публичный слот, устанавливающий список виджетов категорий в
         *  боксе категорий.
         *  @param categories - список категорий.
         *      Срабатывает при получении сигнала от ядра программы, по которому передается
         *    список категорий.
         */
        void setCategoryList(QList<SecurityEventCategory> categories);

    signals:

};

#endif // ADMINEVENTCATEGORYBOXLAYOUTCONTROLLER_H
