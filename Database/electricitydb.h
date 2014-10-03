#ifndef ELECTRICITYDB_H
#define ELECTRICITYDB_H

#include "Common_Struct_data.h"
#include "commondb.h"

class ElectricityDB : public CommonDB
{
public:
    ElectricityDB();
    ~ElectricityDB();

    bool get_last_record(Electricity_record* m_electricity_record);
    void insert_new_record(Electricity_record* m_electricity_record);
    void update_new_record(Electricity_record* m_electricity_record);
    void update_last_record(Electricity_record* m_electricity_record);
    //bool get_last_paid_month(QDate& m_next_Month_Year_Payment);

    void create_table();//Создание новой базы

private:
    double cur_tariff_Day;
    double cur_tariff_Night;
    double cur_tariff_Common;
};

#endif // ELECTRICITYDB_H
