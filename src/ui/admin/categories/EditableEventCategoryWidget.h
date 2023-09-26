#ifndef EDITABLEEVENTCATEGORYWIDGET_H
#define EDITABLEEVENTCATEGORYWIDGET_H

#include <QWidget>
#include <QLineEdit>

#include "src/items/BaseItem.h"

namespace Ui {
class EditableEventCategoryWidget;
}

/**
 *      @brief EditableEventCategoryWidget - класс-виджет, который позволяет
 * администратору редактировать категорию событий. Данный виджет является
 * редактируемой версией UneditableEventCategoryWidget, с которым используется
 * совместно и не имеет своего контекстного меню.
 *      Наследуется публично от классов QWidget и BaseItem.
 */
class EditableEventCategoryWidget : public QWidget, public BaseItem {

    Q_OBJECT

    private:
        /// Переменная, хранящая в себе данные интерфейса
        Ui::EditableEventCategoryWidget * ui;

    private slots:
        /**
        *   @brief slotEditingFinished -  слот, который связывает сигнал editingFinished класса
        * QLineEdit с сигналом editingFinished данного класса, чтобы иметь возможность
        * передать себя в качестве параметра для дальнейшей эксплуатации.
        */
        void slotEditingFinished();

    public:
        /**
         *      @brief EditableItemMenu - конструктор по умолчанию
         *  @param id - Цифровой целочисленный ID для однозначной идентификации и учёта объекта
         *  @param title - Текстовое описание категории, задаваемое администратором
         *  @param parent - родительский объект в иерархии Qt.
         *  В данном конструкторе задается размер виджета, текст виджета и инициализация
         * полей id и text ( см. класс BaseItem ), а так же связывание сигнала editingFinished класса
         * QLineEdit с со слотом slotEditingFinished данного класса.
         */
        explicit EditableEventCategoryWidget(quint32 id, QString title, QWidget * parent = nullptr);

        /**
         *  @brief ~EditableItemMenu - деструктор по умолчанию, используется для
         * высвобождения памяти.
         */
        ~EditableEventCategoryWidget();

    public slots:

    signals:
        /// Сигнал, сообщающий о завершении редактирования виджета
        void editingFinished(EditableEventCategoryWidget * editableCategory);

};

#endif // EDITABLEEVENTCATEGORYWIDGET_H
