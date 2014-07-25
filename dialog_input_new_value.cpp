#include "dialog_input_new_value.h"
#include "ui_dialog_input_new_value.h"

#include <limits>

Dialog_Input_New_Value::Dialog_Input_New_Value(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Input_New_Value)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());
    ui->lineEditValue->setText("0");

    //Можно ограничить число символов, т.к. разрядность счетчика ограничена
    //ui->lineEditValue->setInputMask("00009");
    //ui->lineEditValue->setMaxLength(5);

    int max_int=std::numeric_limits<int>::max();//или LONG_MAX
    ui->lineEditValue->setValidator( new QIntValidator(0, max_int, this) );
    //myLineEdit->setValidator( new QDoubleValidator(0, 100, this) )
}

Dialog_Input_New_Value::~Dialog_Input_New_Value()
{
    delete ui;
}

void Dialog_Input_New_Value::on_pushButton_OK_clicked()
{
    value=ui->lineEditValue->text().toDouble();
    date_input=ui->dateEdit->date();

    QDialog::accept();
}

void Dialog_Input_New_Value::on_pushButton_Cancel_clicked()
{
    //this->close();
    QDialog::reject();
}
