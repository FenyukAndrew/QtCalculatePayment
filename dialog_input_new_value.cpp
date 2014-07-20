#include "dialog_input_new_value.h"
#include "ui_dialog_input_new_value.h"

Dialog_Input_New_Value::Dialog_Input_New_Value(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Input_New_Value)
{
    ui->setupUi(this);
}

Dialog_Input_New_Value::~Dialog_Input_New_Value()
{
    delete ui;
}

void Dialog_Input_New_Value::on_pushButton_OK_clicked()
{
    value=ui->lineEditValue->text().toDouble();
    date_input=ui->dateEdit->date();

    close();
}
