#include "EditableEventWidget.h"
#include "ui_EditableEventWidget.h"

EditableEventWidget::EditableEventWidget(const quint32 id, const QString title, QWidget * parent) : QWidget(parent), ui(new Ui::EditableEventWidget) {
    ui->setupUi(this);
    /// Устанавливаем минимальный размер кнопки
    this->ui->lineEdit_event->setMinimumSize(200, 60);
    /// Инициализируем поля класса
    this->id = id;
    this->title = title;
    /// Устанавливаем доступность строки редактирования и её текст
    this->ui->lineEdit_event->setEnabled(true);
    this->ui->lineEdit_event->setText(title);

    /// Связываем сигнал editingFinished с slotEditingFinished
    QObject::connect(this->ui->lineEdit_event, &QLineEdit::returnPressed, this, &EditableEventWidget::slotEditingFinished);
}

int EditableEventWidget::slotEditingFinished() {
    /// Если виджет пустой, то запускаем процесс удаления и завершаем метод
    if(this->ui->lineEdit_event->text().isEmpty()) {
        emit emptyWidget(this);
        return 1;
    }

    this->title = this->ui->lineEdit_event->text();

    /// Отправляем сигнал о завершении редактирования с указателем на данный редактируемый виджет
    emit editingFinished(this);
    return 0;
}

EditableEventWidget::~EditableEventWidget() {
    delete ui;
}

void EditableEventWidget::setFocus() {
    this->ui->lineEdit_event->setFocus();
}

bool EditableEventWidget::hasFocus() {
    return this->ui->lineEdit_event->hasFocus();
}
