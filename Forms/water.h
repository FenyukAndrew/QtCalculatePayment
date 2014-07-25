#ifndef WATER_H
#define WATER_H

#include <QDialog>
#include "Common_Struct_data.h"

class WaterDB;
class Water_record;

namespace Ui {
class water;
}

class water : public QDialog
{
    Q_OBJECT
    
public:
    explicit water(QWidget *parent = 0);
    ~water();
    
private slots:
    void on_checkBox_HavePaid_stateChanged(int arg1);

    void on_checkBox_HavePaid_clicked();

    void on_pushButton_InputNewValue_clicked();

    void on_pushButton_OK_clicked();

private:

    void show_last_record();

    Ui::water *ui;

    WaterDB* m_WaterDB;

    Water_record m_water_record;
};

#endif // WATER_H
