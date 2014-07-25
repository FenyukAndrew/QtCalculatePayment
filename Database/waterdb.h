#ifndef WATERDB_H
#define WATERDB_H

#include "Common_Struct_data.h"
#include "commondb.h"

class WaterDB : public CommonDB
{
public:
    WaterDB();
    ~WaterDB();

    void get_last_record(Water_record* m_water_record);
    void insert_new_record(Water_record* m_water_record);
    void update_new_record(Water_record* m_water_record);

    void create_table();//Создание новой базы

private:
    double cur_tariff;

};

#endif // WATERDB_H
