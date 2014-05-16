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
