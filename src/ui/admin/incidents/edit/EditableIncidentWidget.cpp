#include "EditableIncidentWidget.h"
#include "ui_EditableIncidentWidget.h"

EditableIncidentWidget::EditableIncidentWidget(const quint32 id, const QString title, const QString text, QWidget * parent) : QWidget(parent), ui(new Ui::EditableIncidentWidget) {
    ui->setupUi(this);

    this->ui->lineEdit_incident->setMinimumSize(200, 60);
    this->ui->textEdit_incident->setMinimumSize(200, 200);

    this->id = id;
    this->title = title;
    this->text = text;

    this->ui->lineEdit_incident->setEnabled(true);
    this->ui->lineEdit_incident->setText(title);

    this->ui->textEdit_incident->setEnabled(true);
    this->ui->textEdit_incident->setText(text);


    QObject::connect(this->ui->lineEdit_incident, &QLineEdit::returnPressed, this, &EditableIncidentWidget::slotEditingFinished);
}

EditableIncidentWidget::~EditableIncidentWidget() {
    delete ui;
}

QString EditableIncidentWidget::getText() {
    return this->text;
}

int EditableIncidentWidget::slotEditingFinished() {

    if(!this->ui->lineEdit_incident->text().isEmpty())
        this->title = this->ui->lineEdit_incident->text();

    if(!this->ui->textEdit_incident->toPlainText().isEmpty())
        this->text = this->ui->textEdit_incident->toPlainText();

    emit editingFinished(this);
    return 0;
}

void EditableIncidentWidget::setFocus() {
    this->ui->lineEdit_incident->setFocus();
}

bool EditableIncidentWidget::hasFocus() {
    return this->ui->lineEdit_incident->hasFocus();
}
