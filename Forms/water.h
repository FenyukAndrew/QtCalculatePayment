#ifndef WATER_H
#define WATER_H

#include <QDialog>
#include "Common_Struct_data.h"

class WaterDB;

namespace Ui {
class water;
}

class water : public QDialog
{
    Q_OBJECT
    
public:
    explicit water(QWidget *parent = 0);
    ~water();
    
    double get_sum_payment() {return m_water_record.Sum_Commission;}

private slots:
    void on_checkBox_HavePaid_stateChanged(int arg1);

    void on_checkBox_HavePaid_clicked();

    void on_pushButton_InputNewValue_clicked();

    void on_pushButton_OK_clicked();

private:

    Ui::water *ui;

    void show_last_record();

    WaterDB* m_WaterDB;

    Water_record m_water_record;
};

#endif // WATER_H
