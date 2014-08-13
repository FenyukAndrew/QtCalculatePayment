#include "control_payments.h"
#include "ui_control_payments.h"

#include "Common_parameters.h"
#include <limits>

#include <QLocale>

Control_Payments::Control_Payments(double sum_payments[],QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Control_Payments)
{
    ui->setupUi(this);

    russain_locale=new QLocale(QLocale::Russian);

    ui->amount_before->setText("0.00");
    ui->amount_before->setValidator(new QDoubleValidator(0, std::numeric_limits<double>::max(), 2, this));//2 знака после запятой

    total_sum_payments=0;
    for(short i=0;i<c_types_of_payments;i++)
    {
        total_sum_payments+=sum_payments[i];
    }
    ui->label_total_payment->setText(russain_locale->toString(total_sum_payments,'f',3));
    calculate();
}

void Control_Payments::calculate()
{
    bool ok;
    double amount_before=ui->amount_before->text().toDouble(&ok);
    if (ok)
    {
        ui->amount_after->setText(russain_locale->toString(amount_before-total_sum_payments,'f',3));
    }
    else
    {
        ui->amount_after->setText("--.--");
    }
}

Control_Payments::~Control_Payments()
{
    delete ui;
    delete(russain_locale);
}

void Control_Payments::on_amount_before_textChanged(const QString &arg1)
{
    calculate();
}
