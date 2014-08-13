#ifndef RUBBISHDB_H
#define RUBBISHDB_H

#include "Common_Struct_data.h"
#include "commondb.h"

class RubbishDB : public CommonDB
{
public:
    RubbishDB();
    ~RubbishDB();

    bool get_last_record(Rubbish_record* m_rubbish_record);
    void insert_new_record(Rubbish_record* m_rubbish_record);
    void update_new_record(Rubbish_record* m_rubbish_record);

    void create_table();//Создание новой базы

private:
    double cur_tariff;
};

#endif // RUBBISHDB_H
