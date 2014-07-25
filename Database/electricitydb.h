#ifndef ELECTRICITYDB_H
#define ELECTRICITYDB_H

#include "Common_Struct_data.h"
#include "commondb.h"

class ElectricityDB : public CommonDB
{
public:
    ElectricityDB();
    ~ElectricityDB();

    void get_last_record(Electricity_record* m_electricity_record);
    void insert_new_record(Electricity_record* m_electricity_record);
    void update_new_record(Electricity_record* m_electricity_record);

    void create_table();//Создание новой базы

private:
    double cur_tariff_Day;
    double cur_tariff_Night;
};

#endif // ELECTRICITYDB_H
