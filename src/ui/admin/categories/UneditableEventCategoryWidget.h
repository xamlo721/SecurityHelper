#ifndef UNEDITABLEEVENTCATEGORYWIDGET_H
#define UNEDITABLEEVENTCATEGORYWIDGET_H

#include <QWidget>

#include "src/ui/admin/BaseItem.h"
#include "src/ui/admin/UneditableItemMenu.h"

namespace Ui {
class UneditableEventCategoryWidget;
}

/**
 *      @brief UneditableEventCategoryWidget - класс-виджет, который выполняет
 * функцию взаимодействия администратора с категорией событий с помощью
 * кастомного меню. Данный виджет нельзя редактировать, но его можно
 * добавить, удалить и превратить в EditableEventCategoryWidget, с которым
 * данный класс используется совместно.
 *      Наследуется публично от классов QWidget и BaseItem.
 */
class UneditableEventCategoryWidget : public QWidget, public BaseItem {

    Q_OBJECT

    private:
        /// Переменная кастомизированного контекстного меню
        UneditableItemMenu *customMenu;
        /// Переменная, хранящая в себе данные интерфейса
        Ui::UneditableEventCategoryWidget *ui;

    private slots:

    public:
        /**
         *      @brief UneditableItemMenu - конструктор по умолчанию
         *  @param id - Цифровой целочисленный ID для однозначной идентификации и учёта объекта
         *  @param title - Текстовое описание категории, задаваемое администратором
         *  @param parent - родительский объект в иерархии Qt.
         *  В данном конструкторе задается размер виджета, текст виджета и инициализация
         * полей id и text ( см. класс BaseItem ).
         */
        explicit UneditableEventCategoryWidget(quint32 id, QString title, QWidget *parent = nullptr);

        /**
         *  @brief ~UneditableItemMenu - деструктор по умолчанию, используется для высвобождения
         * памяти.
         */
        ~UneditableEventCategoryWidget();

        /**
         * @brief initMenu - метод инициализации кастомного контекстного меню.
         */
        void initMenu();

        /**
         * @brief callCustomMenu - метод вызова кастомного контекстного меню.
         */
        void callCustomMenu(QPoint mousePosition);

    public slots:
        /**
        *       @brief slotEditCategory -  слот, который связывает сигнал signalEditCategory класса
        * UneditableItemMenu с сигналом signalEditCategory данного класса, чтобы иметь возможность
        * передать себя в качестве параметра для дальнейшей эксплуатации.
        */
        void slotEditCategory();

    signals:
        /// Сигнал, сообщающий о вызове в контекстном меню действия Редактировать
        void signalEditCategory(UneditableEventCategoryWidget * uneditableCategory);
        /// Сигнал, сообщающий о вызове в контекстном меню действия Удалить
        void signalDeleteCategory();
};

#endif // UNEDITABLEEVENTCATEGORYWIDGET_H
