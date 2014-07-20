#include "control_payments.h"
#include "ui_control_payments.h"

Control_Payments::Control_Payments(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Control_Payments)
{
    ui->setupUi(this);
}

Control_Payments::~Control_Payments()
{
    delete ui;
}
