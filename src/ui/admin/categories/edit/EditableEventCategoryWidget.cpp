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

EditableEventCategoryWidget::EditableEventCategoryWidget(const quint32 id, const QString title, QWidget * parent) : QWidget(parent), ui(new Ui::EditableEventCategoryWidget) {
    ui->setupUi(this);
    /// Устанавливаем минимальный размер кнопки
    this->ui->lineEdit_category->setMinimumSize(200, 60);
    /// Инициализируем поля класса
    this->id = id;
    this->title = title;
    /// Устанавливаем доступность строки редактирования и её текст
    this->ui->lineEdit_category->setEnabled(true);
    this->ui->lineEdit_category->setText(title);

    /// Связываем сигнал editingFinished с slotEditingFinished
    QObject::connect(this->ui->lineEdit_category, &QLineEdit::returnPressed, this, &EditableEventCategoryWidget::slotEditingFinished);
}

/**
 *  @brief ~EditableItemMenu - деструктор по умолчанию, используется для
 * высвобождения памяти.
 */
EditableEventCategoryWidget::~EditableEventCategoryWidget() {
    delete ui;
}

/**
*   @brief slotEditingFinished -  слот, который связывает сигнал editingFinished класса
* QLineEdit с сигналами editingFinished или emptyWidget данного класса, в зависимости от того, что
* необходимо сделать с объектом: редактировать или удалить т.к. он пустой.
*/
int EditableEventCategoryWidget::slotEditingFinished() {    

    if(!this->ui->lineEdit_category->text().isEmpty())
        this->title = this->ui->lineEdit_category->text();


    /// Отправляем сигнал о завершении редактирования с указателем на данный редактируемый виджет
    emit editingFinished(this);
    return 0;
}

/**
 *  @brief setFocus - метод, устанавливающий фокус QLineEdit.
 */
void EditableEventCategoryWidget::setFocus() {
    this->ui->lineEdit_category->setFocus();
}

/**
 *  @brief hasFocus - метод, показывающий имеет ли QLineEdit фокус.
 */
bool EditableEventCategoryWidget::hasFocus() {
    return this->ui->lineEdit_category->hasFocus();
}
