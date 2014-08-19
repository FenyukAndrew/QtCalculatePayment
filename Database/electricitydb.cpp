#include "electricitydb.h"

ElectricityDB::ElectricityDB()
{
    cur_tariff_Day=get_tariff("Electricity_Day");
    cur_tariff_Night=get_tariff("Electricity_Night");
    cur_tariff_Common=get_tariff("Electricity_Common");
}

ElectricityDB::~ElectricityDB()
{
}

bool ElectricityDB::get_last_record(Electricity_record* m_electricity_record)
{
    //Записи сортируются по _id = иначе неправильный ввод значения может все испортить
    //Записи идут в обратном порядке - вначале самая последняя, затем предпоследняя
    if (!a_query->exec("SELECT Date_Input_Value,Value_Day,Value_Night,Value_External,Sum,Date_Payment,TariffDay,TariffNight,TariffCommon,Savings,Month_Payment,Year_Payment FROM Electricity order by _id DESC limit 2"))
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
        m_electricity_record->TariffCommon=a_query->value(rec.indexOf("TariffCommon")).toDouble();
        m_electricity_record->Savings=a_query->value(rec.indexOf("Savings")).toDouble();
        int month=a_query->value(rec.indexOf("Month_Payment")).toInt();
        int year=a_query->value(rec.indexOf("Year_Payment")).toInt();
        m_electricity_record->Month_Year_Payment=QDate(year,month,1);

        if (a_query->next())
        {
            //Получение значения за преведущий месяц
            m_electricity_record->Last_Value_Day=a_query->value(rec.indexOf("Value_Day")).toInt();
            m_electricity_record->Last_Value_Night=a_query->value(rec.indexOf("Value_Night")).toInt();
            int value_External_last_month=a_query->value(rec.indexOf("Value_External")).toInt();

            m_electricity_record->Calculate_delta_devices(value_External_last_month);

            //Вычисления суммы производяться когда есть преведущее значение
            if (!m_electricity_record->Date_Payment.isValid())
            {
                //Если оплата не произведена - производяться вычисления
                //Чтоб их было видно перед добавлением в базу
                //и они были актуальны на время оплаты
                m_electricity_record->TariffDay=cur_tariff_Day;
                m_electricity_record->TariffNight=cur_tariff_Night;
                m_electricity_record->TariffCommon=cur_tariff_Common;

                m_electricity_record->Calculate_Sum_and_Saving();
            }
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
                     " SET Date_Payment=(datetime('now', 'localtime')),Sum=:total_sum,"
                     "TariffDay=:tariffDay,TariffNight=:tariffNight,TariffCommon=:tariffCommon,"
                     "Savings=:Savings"
                     " WHERE _id=(select max(_id) from Electricity)");
    a_query->bindValue(":total_sum", m_electricity_record->Sum);
    a_query->bindValue(":tariffDay",  m_electricity_record->TariffDay);
    a_query->bindValue(":tariffNight",  m_electricity_record->TariffNight);
    a_query->bindValue(":tariffCommon",  m_electricity_record->TariffCommon);
    a_query->bindValue(":Savings",  m_electricity_record->Savings);
    if (!a_query->exec())
    {
        qDebug() << "Error update Electricity";
    }
}
