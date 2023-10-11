#ifndef ADMINEVENTCATEGORYBOXLAYOUT_H
#define ADMINEVENTCATEGORYBOXLAYOUT_H

#include <QObject>
#include "qboxlayout.h"

#include "src/ui/SelectedWidget.h" //Почему-то нормально не инклюдит

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

        /// Лист с боксами пар виджетов
        QList<QVBoxLayout*> widgetBoxLayouts;


        /**
         *  @brief initUneditableCategory - метод, инициализирующий связь сигналов
         *  не редактируемого виджета категории с данным классом, для сообщения о запросе
         *  администратором на редактирование или удаление категории.
         *  @param uneditableCategory - не редактируемый виджет категории.
         */
        void initUneditableWidget(SelectedWidget *uneditableWidget);
        /**
         *  @brief initEditableCategory - метод, инициализирующий связь сигналов
         *  редактируемого виджета категории с данным классом, для сообщения о завершении
         *  редактирования.
         *  @param editableCategory - редактируемый виджет категории.
         */
        //void initEditableWidget(EditableEventCategoryWidget *editableWidget);

    private slots:


    public:
        /**
         *  @brief AdminEventCategoryBoxLayout - не изменяемый конструктор по умолчанию
         *  @param parent - родительский объект в иерархии Qt.
         */
        explicit AdminEventCategoryBoxLayout(QObject *parent = nullptr);



        void init(QVBoxLayout *boxLayout);

        //void addCategoryWidget(SelectedWidget *uneditableWidget, EditableEventCategoryWidget *editableWidget);

        /**
         *  @brief deleteCategoryWidget - Удаление виджета категории.
         *  @param uneditableCategory - не редактируемый виджет категории, предназначенный
         *  для удаления.
         */
        void deleteCategoryWidget(SelectedWidget *uneditableWidget);

        /**
         *  @brief clearCategories - очистка списка виджетов категорий.
         */
        void clearCategories();

       // void showEditableWidget(SelectedWidget *uneditableWidget, EditableEventCategoryWidget *editableWidget);

        //void showUneditableWidget(EditableEventCategoryWidget *editableWidget, SelectedWidget *uneditableWidget);

        void unselectUneditableWidget(SelectedWidget *uneditableWidget);

        void enableUneditableWidget(SelectedWidget *uneditableWidget);
        void disableUneditableWidget(SelectedWidget *uneditableWidget);

    public slots:

    signals:
        /**
         *  @brief signalEditCategory - сигнал, сообщающий о вызове в контекстном меню
         *  действия Редактировать.
         *  @param uneditableCategory - не редактируемый виджет категории, который необходимо изменить
         *  для возможности редактирования.
         */
        void signalEditCategory(SelectedWidget * uneditableCategory);

        /**
         *  @brief signalDeleteCategory - сигнал, сообщающий о вызове в контекстном меню
         *  действия Удалить.
         *  @param uneditableCategory - не редактируемый виджет категории, который необходимо удалить.
         */
        void signalDeleteCategory(SelectedWidget * uneditableCategory);


        /**
         *  @brief editingFinished - сигнал, сообщающий о завершении редактирования виджета.
         *  @param editableCategory - редактируемый виджет категории, редактирование которого
         *  завершено.
         */
        //void editingFinished(EditableEventCategoryWidget * editableCategory);

        void signalCategorySelected(const quint32 categoryID);
        void signalCategoryUnselected(const quint32 categoryID);
};

#endif // ADMINEVENTCATEGORYBOXLAYOUT_H
