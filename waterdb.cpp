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

    //cur_tariff=get_tariff("Water");

}

WaterDB::~WaterDB()
{
    delete a_query;
}

double WaterDB::get_tariff(const std::string name_tariff)
{
    a_query->prepare("SELECT Value FROM tariffs where NameTable=:name_table");
    a_query->bindValue(":name_table", name_tariff.c_str());
    if (!a_query->exec())
    {
        qDebug() << "Error select.";
        return 0;
    }
    QSqlRecord rec = a_query->record();

    while (a_query->next())
    {
        return a_query->value(rec.indexOf("Value")).toDouble();
    }
    return 0;
}


//Получение 3 последних значений - преведущие 2 для получения разницы значений, последнее вывод на экран
//Вода оплачивается за преведущий месяц
//SELECT * FROM Water order by _id DESC limit 3 - При расчете
//TOP = DESC LIMIT 1

water_record* WaterDB::get_last_record()
{
    //Лучше сортировать не по значению, а по _id = иначе неправильный ввод значения может все испортить
    //Записи идут в обратном порядке - вначале самая последняя, затем предпоследняя
   if (!a_query->exec("SELECT Date_Input_Value,Value,Sum,Sum_Commission,Date_Payment FROM Water order by _id DESC limit 2"))//Value
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
        m_water_record->Tariff=a_query->value(rec.indexOf("Tariff")).toDouble();

        //qDebug() << "Date_Input_Value= " << a_query->value(rec.indexOf("Date_Input_Value")).toString();
        //qDebug() << "Date_Payment= " << a_query->value(rec.indexOf("Date_Payment")).toDateTime();

        if (a_query->next())
        {//Получение преведущего значения
            m_water_record->last_Value=a_query->value(rec.indexOf("Value")).toDouble();
        }

        if (!m_water_record->Date_Payment.isValid())
        {//Если оплата не произведена - производяться вычисления
            //Чтоб их было видно перед добавлением в базу
            //и они были актуальны на время оплаты
            m_water_record->Tariff=cur_tariff;
            m_water_record->Sum=m_water_record->Tariff*(m_water_record->Value-m_water_record->last_Value);
            m_water_record->Sum_Commission=(m_water_record->Sum)*0.01;
        }

        return m_water_record;
    }
    return 0;
}

//Вставка записи при вводе показания
void WaterDB::insert_new_record(water_record* m_water_record)
{
    if (!m_water_record) return;
    a_query->prepare("INSERT INTO Water (Date_Input_Value,Value,Month_Payment,Year_Payment)"
                  "VALUES (datetime('now','localtime'),:value_payment,:month_payment,:year_payment)");
    a_query->bindValue(":value_payment", m_water_record->Value);
    a_query->bindValue(":month_payment", m_water_record->Month_Year_Payment.month());
    a_query->bindValue(":year_payment",  m_water_record->Month_Year_Payment.year());
    a_query->exec();
}

//Обновление последней записи после совершения оплаты
void WaterDB::update_new_record(water_record* m_water_record)
{
    if (!m_water_record) return;
    a_query->prepare("UPDATE Water"
                    "SET Date_Payment=(datetime('now', 'localtime')),Sum=:total_sum,Sum_Commission=:sum_commission,Tariff=:tariff"
                  "WHERE _id=(select max(_id) from Water)");
    a_query->bindValue(":total_sum", m_water_record->Sum);
    a_query->bindValue(":sum_commission", m_water_record->Sum_Commission);
    a_query->bindValue(":tariff",  m_water_record->Tariff);
    a_query->exec();
}
