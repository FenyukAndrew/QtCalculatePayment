#ifndef ELECTRICITY_H
#define ELECTRICITY_H

#include <QDialog>
#include "Common_Struct_data.h"

class ElectricityDB;

namespace Ui {
class Electricity;
}

class Electricity : public QDialog
{
    Q_OBJECT
    
public:
    explicit Electricity(QWidget *parent = 0);
    ~Electricity();

    double get_sum_payment() {return m_electricity_record.Sum;}
    
private slots:
    void on_pushButton_InputNewValue_clicked();

    void on_pushButton_OK_clicked();

private:
    Ui::Electricity *ui;

    void show_last_record();

    ElectricityDB* m_ElectricityDB;

    Electricity_record m_electricity_record;

    double value_payment;//Значение совершенного платежа
};

#endif // ELECTRICITY_H
