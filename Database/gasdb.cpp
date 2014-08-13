#include "gasdb.h"

GasDB::GasDB()
{
    cur_tariff=get_tariff("Gas");
}

GasDB::~GasDB()
{
}

bool GasDB::get_last_record(Gas_record* m_gas_record)
{
    //Записи сортируются по _id = иначе неправильный ввод значения может все испортить
    //Записи идут в обратном порядке - вначале самая последняя, затем предпоследняя
    if (!a_query->exec("SELECT Date_Input_Value,Value,Sum,Date_Payment,Tariff,Month_Payment,Year_Payment FROM Gas order by _id DESC limit 2"))
     {
         qDebug() << "Error select Gas";
         return false;
     }
     QSqlRecord rec = a_query->record();

     if (a_query->next())
     {
         m_gas_record->Init();//Все значения возвращаются в исходные
         m_gas_record->Date_Input_Value=a_query->value(rec.indexOf("Date_Input_Value")).toDateTime();
         m_gas_record->Value=a_query->value(rec.indexOf("Value")).toInt();
         m_gas_record->Sum=a_query->value(rec.indexOf("Sum")).toDouble();
         m_gas_record->Date_Payment=a_query->value(rec.indexOf("Date_Payment")).toDateTime();
         m_gas_record->Tariff=a_query->value(rec.indexOf("Tariff")).toDouble();
         int month=a_query->value(rec.indexOf("Month_Payment")).toInt();
         int year=a_query->value(rec.indexOf("Year_Payment")).toInt();
         m_gas_record->Month_Year_Payment=QDate(year,month,1);

         int value_last_month=0;
         if (a_query->next())
         {//Получение значения за преведущий месяц
             value_last_month=a_query->value(rec.indexOf("Value")).toInt();
         }

         if (!m_gas_record->Date_Payment.isValid())
         {//Если оплата не произведена - производяться вычисления
             //Чтоб их было видно перед добавлением в базу
             //и они были актуальны на время оплаты
             m_gas_record->Tariff=cur_tariff;
             m_gas_record->Sum=m_gas_record->Tariff*(m_gas_record->Value-value_last_month);
         }
         return true;
     }
     return false;
}

void GasDB::insert_new_record(Gas_record* m_gas_record)
{
    a_query->prepare("INSERT INTO Gas (Date_Input_Value,Value,Month_Payment,Year_Payment)"
                  " VALUES (datetime('now','localtime'),:value_payment,:month_payment,:year_payment)");
    a_query->bindValue(":value_payment", m_gas_record->Value);
    a_query->bindValue(":month_payment", m_gas_record->Month_Year_Payment.month());
    a_query->bindValue(":year_payment",  m_gas_record->Month_Year_Payment.year());
    if (!a_query->exec())
    {
            qDebug() << "Error insert Gas";
    }
}

void GasDB::update_new_record(Gas_record* m_gas_record)
{
    a_query->prepare("UPDATE Gas"
                    " SET Date_Payment=(datetime('now', 'localtime')),Sum=:total_sum,Tariff=:tariff"
                  " WHERE _id=(select max(_id) from Gas)");
    a_query->bindValue(":total_sum", m_gas_record->Sum);
    a_query->bindValue(":tariff",  m_gas_record->Tariff);
    if (!a_query->exec())
    {
            qDebug() << "Error update Gas";
    }
}
