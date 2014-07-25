#ifndef COMMONDB_H
#define COMMONDB_H

#include <QtSql>

class CommonDB
{
public:
    CommonDB();
    virtual ~CommonDB();//на случай, если будет вызван delete производного класса, но со ссылкой на базовый класс (избегание частично удаленных объектов)

    double get_tariff(const std::string name_tariff);

//private:
protected:
    QSqlDatabase dbase;
    QSqlQuery* a_query;
};

#endif // COMMONDB_H
