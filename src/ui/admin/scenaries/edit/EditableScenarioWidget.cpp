#include "EditableScenarioWidget.h"
#include "ui_EditableScenarioWidget.h"

EditableScenarioWidget::EditableScenarioWidget(const quint32 id, const QString title, const QString text, QWidget * parent) : QWidget(parent), ui(new Ui::EditableScenarioWidget) {
    ui->setupUi(this);

    this->ui->lineEdit_scenario->setMinimumSize(200, 60);
    this->ui->textEdit_scenario->setMinimumSize(200, 200);

    this->id = id;
    this->title = title;
    this->text = text;

    this->ui->lineEdit_scenario->setEnabled(true);
    this->ui->lineEdit_scenario->setText(title);

    this->ui->textEdit_scenario->setEnabled(true);
    this->ui->textEdit_scenario->setText(text);


    QObject::connect(this->ui->lineEdit_scenario, &QLineEdit::returnPressed, this, &EditableScenarioWidget::slotEditingFinished);
}

EditableScenarioWidget::~EditableScenarioWidget() {
    delete ui;
}

QString EditableScenarioWidget::getText() {
    return this->text;
}

int EditableScenarioWidget::slotEditingFinished() {

    if(!this->ui->lineEdit_scenario->text().isEmpty())
        this->title = this->ui->lineEdit_scenario->text();

    if(!this->ui->textEdit_scenario->toPlainText().isEmpty())
        this->text = this->ui->textEdit_scenario->toPlainText();

    emit editingFinished(this);
    return 0;
}

void EditableScenarioWidget::setFocus() {
    this->ui->lineEdit_scenario->setFocus();
}

bool EditableScenarioWidget::hasFocus() {
    return this->ui->lineEdit_scenario->hasFocus();
}
