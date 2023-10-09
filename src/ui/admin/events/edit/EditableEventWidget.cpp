#include "EditableEventWidget.h"
#include "ui_EditableEventWidget.h"

EditableEventWidget::EditableEventWidget(const quint32 id, const QString title, QWidget * parent) : QWidget(parent), ui(new Ui::EditableEventWidget) {
    ui->setupUi(this);

    this->ui->lineEdit_event->setMinimumSize(200, 60);

    this->id = id;
    this->title = title;

    this->ui->lineEdit_event->setEnabled(true);
    this->ui->lineEdit_event->setText(title);


    QObject::connect(this->ui->lineEdit_event, &QLineEdit::returnPressed, this, &EditableEventWidget::slotEditingFinished);
}

EditableEventWidget::~EditableEventWidget() {
    delete ui;
}

int EditableEventWidget::slotEditingFinished() {
    if(!this->ui->lineEdit_event->text().isEmpty())
        this->title = this->ui->lineEdit_event->text();

    emit editingFinished(this);
    return 0;
}

void EditableEventWidget::setFocus() {
    this->ui->lineEdit_event->setFocus();
}

bool EditableEventWidget::hasFocus() {
    return this->ui->lineEdit_event->hasFocus();
}
