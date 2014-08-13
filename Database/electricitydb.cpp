#include "electricitydb.h"

ElectricityDB::ElectricityDB()
{
    cur_tariff_Day=get_tariff("Electricity_Day");
    cur_tariff_Night=get_tariff("Electricity_Night");
}

ElectricityDB::~ElectricityDB()
{
}

bool ElectricityDB::get_last_record(Electricity_record* m_electricity_record)
{
    //Записи сортируются по _id = иначе неправильный ввод значения может все испортить
    //Записи идут в обратном порядке - вначале самая последняя, затем предпоследняя
    if (!a_query->exec("SELECT Date_Input_Value,Value_Day,Value_Night,Value_External,Sum,Date_Payment,TariffDay,TariffNight,Month_Payment,Year_Payment FROM Electricity order by _id DESC limit 2"))
     {
         qDebug() << "Error select Electricity";
         return false;
     }
     QSqlRecord rec = a_query->record();

     if (a_query->next())
     {
         m_electricity_record->Init();//Все значения возвращаются в исходные
         m_electricity_record->Date_Input_Value=a_query->value(rec.indexOf("Date_Input_Value")).toDateTime();
         m_electricity_record->Value_Day=a_query->value(rec.indexOf("Value_Day")).toInt();
         m_electricity_record->Value_Night=a_query->value(rec.indexOf("Value_Night")).toInt();
         m_electricity_record->Value_External=a_query->value(rec.indexOf("Value_External")).toInt();
         m_electricity_record->Sum=a_query->value(rec.indexOf("Sum")).toDouble();
         m_electricity_record->Date_Payment=a_query->value(rec.indexOf("Date_Payment")).toDateTime();
         m_electricity_record->TariffDay=a_query->value(rec.indexOf("TariffDay")).toDouble();
         m_electricity_record->TariffNight=a_query->value(rec.indexOf("TariffNight")).toDouble();
         int month=a_query->value(rec.indexOf("Month_Payment")).toInt();
         int year=a_query->value(rec.indexOf("Year_Payment")).toInt();
         m_electricity_record->Month_Year_Payment=QDate(year,month,1);

         int value_Day_last_month=0;
         int value_Night_last_month=0;
         int value_External_last_month=0;
         if (a_query->next())
         {//Получение значения за преведущий месяц
             value_Day_last_month=a_query->value(rec.indexOf("Value_Day")).toInt();
             value_Night_last_month=a_query->value(rec.indexOf("Value_Night")).toInt();
             value_External_last_month=a_query->value(rec.indexOf("Value_External")).toInt();
         }

         if (!m_electricity_record->Date_Payment.isValid())
         {//Если оплата не произведена - производяться вычисления
             //Чтоб их было видно перед добавлением в базу
             //и они были актуальны на время оплаты
             m_electricity_record->TariffDay=cur_tariff_Day;
             m_electricity_record->TariffNight=cur_tariff_Night;
             m_electricity_record->Sum=
                     m_electricity_record->TariffDay*(m_electricity_record->Value_Day-value_Day_last_month)+
                     m_electricity_record->TariffNight*(m_electricity_record->Value_Night-value_Night_last_month);
             m_electricity_record->delta_devices=
                (m_electricity_record->Value_Day+m_electricity_record->Value_Night-m_electricity_record->Value_External)-
                (value_Day_last_month+value_Night_last_month-value_External_last_month);
             //Разница в показаниях счетчиков: двухтарифный и входной
             //Лучше считать с начальным месяцем в базе, но для этого нужно делать дополнительный запрос
         }
         return true;
     }
     return false;
}

void ElectricityDB::insert_new_record(Electricity_record* m_electricity_record)
{
    a_query->prepare("INSERT INTO Electricity (Date_Input_Value,Value_Day,Value_Night,Value_External,Month_Payment,Year_Payment)"
                  " VALUES (datetime('now','localtime'),:value_Day_payment,:value_Night_payment,:value_External_payment,:month_payment,:year_payment)");
    a_query->bindValue(":value_Day_payment", m_electricity_record->Value_Day);
    a_query->bindValue(":value_Night_payment", m_electricity_record->Value_Night);
    a_query->bindValue(":value_External_payment", m_electricity_record->Value_External);
    a_query->bindValue(":month_payment", m_electricity_record->Month_Year_Payment.month());
    a_query->bindValue(":year_payment",  m_electricity_record->Month_Year_Payment.year());
    if (!a_query->exec())
    {
            qDebug() << "Error insert Electricity";
    }
}

void ElectricityDB::update_new_record(Electricity_record* m_electricity_record)
{
    a_query->prepare("UPDATE Electricity"
                    " SET Date_Payment=(datetime('now', 'localtime')),Sum=:total_sum,TariffDay=:tariffDay,TariffNight=:tariffNight"
                  " WHERE _id=(select max(_id) from Electricity)");
    a_query->bindValue(":total_sum", m_electricity_record->Sum);
    a_query->bindValue(":tariffDay",  m_electricity_record->TariffDay);
    a_query->bindValue(":tariffNight",  m_electricity_record->TariffNight);
    if (!a_query->exec())
    {
            qDebug() << "Error update Electricity";
    }
}
