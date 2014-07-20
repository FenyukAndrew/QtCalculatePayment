#ifndef CONTROL_PAYMENTS_H
#define CONTROL_PAYMENTS_H

#include <QDialog>

namespace Ui {
class Control_Payments;
}

class Control_Payments : public QDialog
{
    Q_OBJECT

public:
    explicit Control_Payments(QWidget *parent = 0);
    ~Control_Payments();

private:
    Ui::Control_Payments *ui;
};

#endif // CONTROL_PAYMENTS_H
