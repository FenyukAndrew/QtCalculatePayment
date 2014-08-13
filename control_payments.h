#ifndef CONTROL_PAYMENTS_H
#define CONTROL_PAYMENTS_H

#include <QDialog>

namespace Ui {
class Control_Payments;
}

class QLocale;

class Control_Payments : public QDialog
{
    Q_OBJECT

public:
    explicit Control_Payments(double sum_payments[],QWidget *parent = 0);
    ~Control_Payments();

private slots:
    void on_amount_before_textChanged(const QString &arg1);

private:
    Ui::Control_Payments *ui;

    void calculate();

    double total_sum_payments;

    QLocale* russain_locale;

};

#endif // CONTROL_PAYMENTS_H
