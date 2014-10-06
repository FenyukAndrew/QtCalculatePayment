#ifndef GASDB_H
#define GASDB_H

#include "Common_Struct_data.h"
#include "commondb.h"

class GasDB : public CommonDB
{
public:
    GasDB();
    ~GasDB();

    bool get_last_record(Gas_record* m_gas_record);
    void insert_new_record(Gas_record* m_gas_record);
    void update_new_record(Gas_record* m_gas_record);
    void update_last_record(Gas_record* m_gas_record);

    void create_table();//Создание новой базы

private:
    double cur_tariff;
};

#endif // GASDB_H
