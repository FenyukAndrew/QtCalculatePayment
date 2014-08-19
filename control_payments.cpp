#include "control_payments.h"
#include "ui_control_payments.h"

#include "Common_parameters.h"
#include <limits>

Control_Payments::Control_Payments(double sum_payments[],QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Control_Payments)
{
    ui->setupUi(this);

    ANDROID_MAKE_WINDOW_FULL_SCREEN;

    ui->amount_before->setText(system_locale.toString(0.00,'f',2));
    ui->amount_before->setValidator(new QDoubleValidator(0, std::numeric_limits<double>::max(), 2, this));//2 знака после запятой

    total_sum_payments=0;
    for(short i=0; i<c_types_of_payments; i++)
    {
        total_sum_payments+=sum_payments[i];
    }
    ui->label_total_payment->setText(system_locale.toString(total_sum_payments,'f',3));
    calculate();
}

void Control_Payments::calculate()
{
    bool ok;
    //double amount_before=ui->amount_before->text().toDouble(&ok);
    double amount_before=system_locale.toDouble(ui->amount_before->text(),&ok);
    if (ok)
    {
        ui->amount_after->setText(system_locale.toString(amount_before-total_sum_payments,'f',3));
    }
    else
    {
        ui->amount_after->setText("--.--");
    }
}

Control_Payments::~Control_Payments()
{
    delete ui;
}

void Control_Payments::on_amount_before_textChanged(const QString &arg1)
{
    calculate();
}

void Control_Payments::on_pushButton_OK_clicked()
{
    QDialog::accept();
}
