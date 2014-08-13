#ifndef GAS_H
#define GAS_H

#include <QDialog>
#include "Common_Struct_data.h"

class GasDB;

namespace Ui {
class Gas;
}

class Gas : public QDialog
{
    Q_OBJECT

public:
    explicit Gas(QWidget *parent = 0);
    ~Gas();

    double get_sum_payment() {return m_gas_record.Sum;}

private slots:
    void on_pushButton_InputNewValue_clicked();

    void on_pushButton_OK_clicked();

private:
    Ui::Gas *ui;

    void show_last_record();

    GasDB* m_GasDB;

    Gas_record m_gas_record;

};

#endif // GAS_H
