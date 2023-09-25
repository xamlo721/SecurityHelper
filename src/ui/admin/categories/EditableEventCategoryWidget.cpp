#include "EditableEventCategoryWidget.h"
#include "ui_EditableEventCategoryWidget.h"

/**
 *      @brief EditableItemMenu - конструктор по умолчанию
 *  @param id - Цифровой целочисленный ID для однозначной идентификации и учёта объекта
 *  @param title - Текстовое описание категории, задаваемое администратором
 *  @param parent - родительский объект в иерархии Qt.
 *  В данном конструкторе задается размер виджета, текст виджета и инициализация
 * полей id и text ( см. класс BaseItem ), а так же связывание сигнала editingFinished класса
 * QLineEdit с со слотом slotEditingFinished данного класса.
 */
EditableEventCategoryWidget::EditableEventCategoryWidget(quint32 id, QString title, QWidget * parent) : QWidget(parent), ui(new Ui::EditableEventCategoryWidget) {
    ui->setupUi(this);
    /// Устанавливаем минимальный размер кнопки
    this->ui->lineEdit_category->setMinimumSize(200, 60);
    /// Инициализируем поля класса
    this->id = id;
    this->text = title;
    /// Устанавливаем доступность кнопки и её текст
    this->ui->lineEdit_category->setEnabled(true);
    this->ui->lineEdit_category->setText(title);

    /// Связываем сигнал editingFinished с slotEditingFinished
    QObject::connect(this->ui->lineEdit_category, &QLineEdit::editingFinished, this, &EditableEventCategoryWidget::slotEditingFinished);
}

/**
*   @brief slotEditingFinished -  слот, который связывает сигнал editingFinished класса
* QLineEdit с сигналом editingFinished данного класса, чтобы иметь возможность
* передать себя в качестве параметра для дальнейшей эксплуатации.
*/
void EditableEventCategoryWidget::slotEditingFinished() {
    /// Отправляем сигнал о завершении редактирования с указателем на данный редактируемый виджет
    emit editingFinished(this);
}

/**
 *  @brief ~EditableItemMenu - деструктор по умолчанию, используется для
 * высвобождения памяти.
 */
EditableEventCategoryWidget::~EditableEventCategoryWidget() {
    delete ui;
}
