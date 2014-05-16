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
//SELECT * FROM Water order by _id DESC limit 3 - При расчете
//TOP = DESC LIMIT 1

water_record* WaterDB::get_last_data()
{
    //Лучше сортировать не по значению, а по _id = иначе неправильный ввод значения может все испортить
   if (!a_query->exec("SELECT Date_Input_Value,Value,Sum,Sum_Commission,Date_Payment FROM Water order by _id DESC limit 1"))//Value
       //SELECT * FROM Water order by _id DESC limit 1
    {
        qDebug() << "Error select.";
        return 0;
    }
    QSqlRecord rec = a_query->record();

    while (a_query->next())
    {
        water_record* m_water_record=new water_record();
        m_water_record->Date_Input_Value=a_query->value(rec.indexOf("Date_Input_Value")).toDateTime();
        m_water_record->Value=a_query->value(rec.indexOf("Value")).toDouble();
        m_water_record->Sum=a_query->value(rec.indexOf("Sum")).toDouble();
        m_water_record->Sum_Commission=a_query->value(rec.indexOf("Sum_Commission")).toDouble();
        m_water_record->Date_Payment=a_query->value(rec.indexOf("Date_Payment")).toDateTime();
        //m_water_record->Tariff=a_query->value(rec.indexOf("Tariff")).toDouble();

        //qDebug() << "Date_Input_Value= " << a_query->value(rec.indexOf("Date_Input_Value")).toString();
        //qDebug() << "Date_Payment= " << a_query->value(rec.indexOf("Date_Payment")).toDateTime();
        return m_water_record;
    }
    return 0;
}
