#ifndef WATERDB_H
#define WATERDB_H

#include <QtSql>

struct water_record
{
    QDateTime Date_Input_Value;
    double Value;
    double Sum;
    double Sum_Commission;
    QDateTime Date_Payment;
    //double Tariff;
};


class WaterDB
{
public:
    WaterDB();
    ~WaterDB();
    water_record* get_last_data();

private:
    QSqlDatabase dbase;
    QSqlQuery* a_query;
};

#endif // WATERDB_H
