#ifndef ADMINEVENTCATEGORYBOXLAYOUT_H
#define ADMINEVENTCATEGORYBOXLAYOUT_H

#include <QObject>
#include "qboxlayout.h"

#include "src/ui/admin/categories/UneditableEventCategoryWidget.h"
#include "src/ui/admin/categories/EditableEventCategoryWidget.h"


/**
 * @brief AdminEventCategoryBoxLayout - класс-виджет бокса, хранящего в себе
 * категории событий. Имеет возможность добавлять и удалять категории, трансформирует
 * виджеты не редактируемого и редактируемого виджетов для администратора. Способен очистить
 * список категорий событий.
 */
class AdminEventCategoryBoxLayout : public QObject {

    Q_OBJECT

    private:
        /// Бокс категорий, над которым производятся действия
        QVBoxLayout *boxLayoutCategories;

        /**
         *  @brief initUneditableCategory - метод, инициализирующий связь сигналов
         *  не редактируемого виджета категории с данным классом, для сообщения о запросе
         *  администратором на редактирование или удаление категории.
         *  @param uneditableCategory - не редактируемый виджет категории.
         */
        void initUneditableCategory(UneditableEventCategoryWidget *uneditableCategory);
        /**
         *  @brief initEditableCategory - метод, инициализирующий связь сигналов
         *  редактируемого виджета категории с данным классом, для сообщения о завершении
         *  редактирования.
         *  @param editableCategory - редактируемый виджет категории.
         */
        void initEditableCategory(EditableEventCategoryWidget *editableCategory);

    private slots:


    public:
        /**
         *  @brief AdminEventCategoryBoxLayout - не изменяемый конструктор по умолчанию
         *  @param parent - родительский объект в иерархии Qt.
         */
        explicit AdminEventCategoryBoxLayout(QObject *parent = nullptr);

        /**
         *  @brief init - метод, инициализирующий бокс категорий в данном классе
         *  из бокса категорий уже находящегося в AdminEditMenuWidget.
         *  @param boxLayout - бокс категорий, находящийся в AdminEditMenuWidget.
         */
        void init(QVBoxLayout *boxLayout);

        /**
         *  @brief addCategory - добавление категории событий в бокс категорий меню.
         *  @param uneditableCategory - не редактируемый виджет категории.
         *      Добавляется категория в качестве не редактируемого виджета, чтобы
         *  интерфейс был более удобным и понятным, если администратор ранее использовал
         *  какие-либо программы редактирования.
         */
        void addCategory(UneditableEventCategoryWidget *uneditableCategory);
        /**
         *  @brief clearCategories - очистка списка виджетов категорий.
         */
        void clearCategories();

        /**
         *  @brief makeCategoryEditable - изменение не редактируемого виджета на редактируемый
         *  для возможности изменения имени категории.
         *  @param uneditableCategory - не редактируемый виджет категории, который необходимо изменить.
         */
        void makeCategoryEditable(UneditableEventCategoryWidget *uneditableCategory);
        /**
         *  @brief makeCategoryUneditable - изменение редактируемого виджета на не редактируемый
         *  при завершении редактирования администратором.
         *  @param editableCategory - редактируемый виджет категории, который необходимо изменить.
         */
        void makeCategoryUneditable(EditableEventCategoryWidget *editableCategory);

    signals:
        /**
         *  @brief signalEditCategory - сигнал, сообщающий о вызове в контекстном меню
         *  действия Редактировать.
         *  @param uneditableCategory - не редактируемый виджет категории, который необходимо изменить
         *  для возможности редактирования.
         */
        void signalEditCategory(UneditableEventCategoryWidget * uneditableCategory);
        /**
         *  @brief signalDeleteCategory - сигнал, сообщающий о вызове в контекстном меню
         *  действия Удалить.
         *  @param uneditableCategory - не редактируемый виджет категории, который необходимо удалить.
         */
        void signalDeleteCategory();

        /**
         *  @brief editingFinished - сигнал, сообщающий о завершении редактирования виджета.
         *  @param editableCategory - редактируемый виджет категории, редактирование которого
         *  завершено.
         */
        void editingFinished(EditableEventCategoryWidget * editableCategory);
};

#endif // ADMINEVENTCATEGORYBOXLAYOUT_H
