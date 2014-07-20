#ifndef WATERDB_H
#define WATERDB_H

#include <QtSql>

struct water_record
{
    QDateTime Date_Input_Value;
    double Value;
    double last_Value;
    double Sum;
    double Sum_Commission;
    QDateTime Date_Payment;
    QDate Month_Year_Payment;
    double Tariff;
};


class WaterDB
{
public:
    WaterDB();
    ~WaterDB();

    water_record* get_last_record();
    void insert_new_record(water_record* m_water_record);
    void update_new_record(water_record* m_water_record);

    double get_tariff(const std::string name_tariff);

private:
    double cur_tariff;

    QSqlDatabase dbase;
    QSqlQuery* a_query;
};

#endif // WATERDB_H
