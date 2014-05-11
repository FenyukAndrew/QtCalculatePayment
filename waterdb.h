#ifndef WATERDB_H
#define WATERDB_H

#include <QtSql>

class WaterDB
{
public:
    WaterDB();
    ~WaterDB();
    void get_last_data();

private:
    QSqlDatabase dbase;
    QSqlQuery* a_query;
};

#endif // WATERDB_H
