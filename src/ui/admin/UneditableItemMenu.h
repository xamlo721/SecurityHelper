#ifndef UNEDITABLEITEMMENU_H
#define UNEDITABLEITEMMENU_H

#include <QObject>
#include <QMenu>
#include <QAction>
#include <QPoint>

/**
 *      @brief UneditableItemMenu - класс-меню, предназначенный
 * для вызова контекстного меню нередактируемого виджета.
 */
class UneditableItemMenu : public QObject {

    Q_OBJECT

    private:
        /// Меню, которое кастомизируется под нужды виджета
        QMenu *menu;

        /// Переменная, хранящая себе информацию о действии Редактировать
        QAction *editAction;
        /// Переменная, хранящая себе информацию о действии Удалить
        QAction *deleteAction;

    private slots:

    public:
        /**
         *      @brief UneditableItemMenu - конструктор по умолчанию,
         * в котором инициализируется меню.
         *  @param parent - родительский объект в иерархии Qt.
         */
        explicit UneditableItemMenu(QObject *parent = nullptr);

        /**
         * @brief setup - метод, устанавливающий действия (QAction) в меню.
         */
        void setup();
        /**
         *      @brief init - инициализация связи сигналов
         * действий (QAction) с сигналами класса UneditableItemMenu.
         * В данном случае, связываются слоты triggered класса QAction,
         * что позволит при нажатии на действии в меню отправить сигнал
         * вверх по иерархии интерфейса.
         */
        void init();
    public slots:
        /**
         *      @brief call - публичный слот, который выплоняет вызов
         * кастомизированного меню по позиции курсора.
         */
        void call(QPoint mousePosition);

    signals:
        /// Сигнал, сообщающий о вызове в меню действия Редактировать
        void signalEditCategory();
        /// Сигнал, сообщающий о вызове в меню действия Удалить
        void signalDeleteCategory();

};

#endif // UNEDITABLEITEMMENU_H
