#include "UneditableEventCategoryWidget.h"
#include "ui_UneditableEventCategoryWidget.h"

/**
 *      @brief UneditableItemMenu - конструктор по умолчанию
 *  @param id - Цифровой целочисленный ID для однозначной идентификации и учёта объекта
 *  @param title - Текстовое описание категории, задаваемое администратором
 *  @param parent - родительский объект в иерархии Qt.
 *  В данном конструкторе задается размер виджета, текст виджета и инициализация
 * полей id и text ( см. класс BaseItem ).
 */
UneditableEventCategoryWidget::UneditableEventCategoryWidget(const quint32 id, const QString title, QWidget *parent) : QWidget(parent), ui(new Ui::UneditableEventCategoryWidget) {
    ui->setupUi(this);
    /// Задаем минимальный размер кнопки
    this->ui->pushButton_category->setMinimumSize(200, 60);
    /// Инициализируем поля класса
    this->id = id;
    this->text = title;
    this->ui->checkBox->setChecked(false);
    /// Устанавливаем текст на кнопке
    this->ui->pushButton_category->setText(text);

    QObject::connect(this->ui->checkBox, &QCheckBox::clicked, this, &UneditableEventCategoryWidget::onCheckBoxClicked);
}

void UneditableEventCategoryWidget::onCheckBoxClicked() {
    switch (this->ui->checkBox->isChecked()) {
    case true:

        emit signalCategorySelected(this->getID());
        break;

    case false:

        emit signalCategoryUnselected(this->getID());
        break;
    }
}

/**
 * @brief initMenu - метод инициализации кастомного контекстного меню.
 */
void UneditableEventCategoryWidget::initMenu() {
    customMenu = new UneditableItemMenu();

    /// Установка и инициализация меню
    customMenu->setup();
    customMenu->init();

    /// Инициализация связи сигналов кастомного меню и класса UneditableEventCategoryWidget
    QObject::connect(this->customMenu, &UneditableItemMenu::signalEditCategory, this, &UneditableEventCategoryWidget::slotEditCategory);
    QObject::connect(this->customMenu, &UneditableItemMenu::signalDeleteCategory, this, &UneditableEventCategoryWidget::slotDeleteCategory);

    /// Инициализация связи сигналов класса QPushButton и класса UneditableEventCategoryWidget
    QObject::connect(this->ui->pushButton_category, &QPushButton::clicked, this, &UneditableEventCategoryWidget::slotEditCategory);
    QObject::connect(this->ui->pushButton_category, &QPushButton::customContextMenuRequested, this, &UneditableEventCategoryWidget::callCustomMenu);

    /// Установка политики меню, позволяющая показывать кастомное контекстное меню и использовать сигнал &QPushButton::customContextMenuRequested
    this->ui->pushButton_category->setContextMenuPolicy(Qt::CustomContextMenu);
}

/**
 * @brief callCustomMenu - метод вызова кастомного контекстного меню.
 */
void UneditableEventCategoryWidget::callCustomMenu(const QPoint mousePosition) {
    /// Вызов кастомного контекстного меню по позиции курсора
    customMenu->call(this->ui->pushButton_category->mapToGlobal(mousePosition));
}

void UneditableEventCategoryWidget::setText(const QString text) {
    this->text = text;
    this->ui->pushButton_category->setText(this->text);
}

void UneditableEventCategoryWidget::setUnselected() {
    /// Делаем checkBox не выбранным
    this->ui->checkBox->setChecked(false);
    /// Отправляем сигнал о том, что выбор checkBox отменяется ( см. UneditableEventCategoryWidget::onCheckBoxClicked() )
    emit this->ui->checkBox->clicked();
}

/**
*       @brief slotEditCategory -  слот, который связывает сигнал signalEditCategory класса
* UneditableItemMenu с сигналом signalEditCategory данного класса, чтобы иметь возможность
* передать себя в качестве параметра для дальнейшей эксплуатации.
*/
void UneditableEventCategoryWidget::slotEditCategory() {
    emit signalEditCategory(this);
}
/**
*       @brief slotDeleteCategory -  слот, который связывает сигнал signalDeleteCategory класса
* UneditableItemMenu с сигналом signalDeleteCategory данного класса, чтобы иметь возможность
* передать себя в качестве параметра для дальнейшей эксплуатации.
*/
void UneditableEventCategoryWidget::slotDeleteCategory() {
    emit signalDeleteCategory(this);
}
/**
 *  @brief ~UneditableItemMenu - деструктор по умолчанию, используется для высвобождения
 * памяти.
 */
UneditableEventCategoryWidget::~UneditableEventCategoryWidget() {
    delete ui;
    delete customMenu;
}
