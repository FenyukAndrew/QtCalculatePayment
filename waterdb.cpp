#include "waterdb.h"
#include "Common.h"

WaterDB::WaterDB() : dbase(QSqlDatabase::addDatabase("QSQLITE"))
{
    dbase.setDatabaseName(pathDB);
    if (!dbase.open())
    {
        qDebug() << "Error connect!";
        return;
    }

    a_query=new QSqlQuery(dbase);
}

WaterDB::~WaterDB()
{
    delete a_query;
}

//Получение 3 последних значений - преведущие 2 для получения разницы значений, последнее вывод на экран
//Вода оплачивается за преведущий месяц

void WaterDB::get_last_data()
{
   if (!a_query->exec("SELECT * FROM Water order by Value limit 3"))
    {
        qDebug() << "Error select.";
        return;
    }
    QSqlRecord rec = a_query->record();
    int number = 0,
            age = 0;
    QString address = "";

    while (a_query->next())
    {
        /*number = a_query.value(rec.indexOf("number")).toInt();
        age = a_query.value(rec.indexOf("age")).toInt();
        address = a_query.value(rec.indexOf("address")).toString();

        qDebug() << "number is " << number
                 << ". age is " << age
                 << ". address" << address;*/
        qDebug() << "_id= " << a_query->value(rec.indexOf("_id")).toString()
                 << "Value= " << a_query->value(rec.indexOf("Value")).toString()
                 << "Sum= " << a_query->value(rec.indexOf("Sum")).toString();
    }

}
