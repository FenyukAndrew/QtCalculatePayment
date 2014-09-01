#include "Common_parameters.h"
#include "waterdb.h"

WaterDB::WaterDB()
{
    cur_tariff=get_tariff("Water");
}

WaterDB::~WaterDB()
{
}

//Получение 3 последних значений - преведущие 2 для получения разницы значений, последнее вывод на экран
//Вода оплачивается за преведущий месяц
//SELECT * FROM Water order by _id DESC limit 3 - При расчете
//TOP = DESC LIMIT 1

//НЕВЕРНО - вычисления производяться за преведущий месяц
/*bool WaterDB::get_last_record(Water_record* m_water_record)
{
    //if (!m_water_record) return;
    //Лучше сортировать не по значению, а по _id = иначе неправильный ввод значения может все испортить
    //Записи идут в обратном порядке - вначале самая последняя, затем предпоследняя
    if (!a_query->exec("SELECT Date_Input_Value,Value,Sum,Sum_Commission,Date_Payment,Tariff,Month_Payment,Year_Payment FROM Water order by _id DESC limit 3"))//Value
        //SELECT * FROM Water order by _id DESC limit 1
    {
        qDebug() << "Error select Water";
        return false;
    }
    QSqlRecord rec = a_query->record();

    if (a_query->next())
    {
        //вычисления производяться на основе 2 преведущих месяцев!!!
        m_water_record->Init();//Все значения возвращаются в исходные
        m_water_record->Date_Input_Value=a_query->value(rec.indexOf("Date_Input_Value")).toDateTime();
        m_water_record->Value=a_query->value(rec.indexOf("Value")).toInt();
        m_water_record->Sum=a_query->value(rec.indexOf("Sum")).toDouble();
        m_water_record->Sum_Commission=a_query->value(rec.indexOf("Sum_Commission")).toDouble();
        m_water_record->Date_Payment=a_query->value(rec.indexOf("Date_Payment")).toDateTime();
        m_water_record->Tariff=a_query->value(rec.indexOf("Tariff")).toDouble();
        int month=a_query->value(rec.indexOf("Month_Payment")).toInt();
        int year=a_query->value(rec.indexOf("Year_Payment")).toInt();
        m_water_record->Month_Year_Payment=QDate(year,month,1);

        //qDebug() << "Date_Input_Value= " << a_query->value(rec.indexOf("Date_Input_Value")).toString();
        //qDebug() << "Date_Payment= " << a_query->value(rec.indexOf("Date_Payment")).toDateTime();

        int value_last_month=0;
        if (a_query->next())
        {
            //Получение значения за преведущий месяц
            value_last_month=a_query->value(rec.indexOf("Value")).toInt();

            int value_two_month_ago=0;
            if (a_query->next())
            {
                //Получение значения за 2 месяц назад
                value_two_month_ago=a_query->value(rec.indexOf("Value")).toInt();
            }

            //Вычисления суммы производяться когда есть преведущее значение
            if (!m_water_record->Date_Payment.isValid())
            {
                //Если оплата не произведена - производяться вычисления
                //Чтоб их было видно перед добавлением в базу
                //и они были актуальны на время оплаты
                m_water_record->Tariff=cur_tariff;
                m_water_record->Sum=m_water_record->Tariff*(value_last_month-value_two_month_ago);
                m_water_record->Sum_Commission=(m_water_record->Sum)*c_percent_Sberbank;//(1+0.01);
            }
        }
        return true;
    }
    return false;
}*/

//Исправленная версия - теперь сумма вычисляется за текущий месяц, а не за прошедший
bool WaterDB::get_last_record(Water_record* m_water_record)
{
    //if (!m_water_record) return;
    //Лучше сортировать не по значению, а по _id = иначе неправильный ввод значения может все испортить
    //Записи идут в обратном порядке - вначале самая последняя, затем предпоследняя
    if (!a_query->exec("SELECT Date_Input_Value,Value,Sum,Sum_Commission,Date_Payment,Tariff,Month_Payment,Year_Payment FROM Water order by _id DESC limit 2"))//Value
    {
        qDebug() << "Error select Water";
        return false;
    }
    QSqlRecord rec = a_query->record();

    if (a_query->next())
    {
        //вычисления производяться на основе 2 преведущих месяцев!!!
        m_water_record->Init();//Все значения возвращаются в исходные
        m_water_record->Date_Input_Value=a_query->value(rec.indexOf("Date_Input_Value")).toDateTime();
        m_water_record->Value=a_query->value(rec.indexOf("Value")).toInt();
        m_water_record->Sum=a_query->value(rec.indexOf("Sum")).toDouble();
        m_water_record->Sum_Commission=a_query->value(rec.indexOf("Sum_Commission")).toDouble();
        m_water_record->Date_Payment=a_query->value(rec.indexOf("Date_Payment")).toDateTime();
        m_water_record->Tariff=a_query->value(rec.indexOf("Tariff")).toDouble();
        int month=a_query->value(rec.indexOf("Month_Payment")).toInt();
        int year=a_query->value(rec.indexOf("Year_Payment")).toInt();
        m_water_record->Month_Year_Payment=QDate(year,month,1);

        //qDebug() << "Date_Input_Value= " << a_query->value(rec.indexOf("Date_Input_Value")).toString();
        //qDebug() << "Date_Payment= " << a_query->value(rec.indexOf("Date_Payment")).toDateTime();

        int value_last_month=0;
        if (a_query->next())
        {
            //Получение значения за преведущий месяц
            value_last_month=a_query->value(rec.indexOf("Value")).toInt();

            //Вычисления суммы производяться когда есть преведущее значение
            if (!m_water_record->Date_Payment.isValid())
            {
                //Если оплата не произведена - производяться вычисления
                //Чтоб их было видно перед добавлением в базу
                //и они были актуальны на время оплаты
                m_water_record->Tariff=cur_tariff;
                m_water_record->Sum=m_water_record->Tariff*(m_water_record->Value-value_last_month);
                m_water_record->Sum_Commission=(m_water_record->Sum)*c_percent_Sberbank;//(1+0.01);
            }
        }
        return true;
    }
    return false;
}

//Вставка записи при вводе показания
void WaterDB::insert_new_record(Water_record* m_water_record)
{
    //if (!m_water_record) return;
    a_query->prepare("INSERT INTO Water (Date_Input_Value,Value,Month_Payment,Year_Payment)"
                     " VALUES (datetime('now','localtime'),:value_payment,:month_payment,:year_payment)");
    a_query->bindValue(":value_payment", m_water_record->Value);
    a_query->bindValue(":month_payment", m_water_record->Month_Year_Payment.month());
    a_query->bindValue(":year_payment",  m_water_record->Month_Year_Payment.year());
    if (!a_query->exec())
    {
        qDebug() << "Error insert Water";
    }
}

//Обновление последней записи после совершения оплаты
void WaterDB::update_new_record(Water_record* m_water_record)
{
    //if (!m_water_record) return;
    a_query->prepare("UPDATE Water"
                     " SET Date_Payment=(datetime('now', 'localtime')),Sum=:total_sum,Sum_Commission=:sum_commission,Tariff=:tariff"
                     " WHERE _id=(select max(_id) from Water)");
    a_query->bindValue(":total_sum", m_water_record->Sum);
    a_query->bindValue(":sum_commission", m_water_record->Sum_Commission);
    a_query->bindValue(":tariff",  m_water_record->Tariff);
    if (!a_query->exec())
    {
        qDebug() << "Error update Water";
    }
}

//ПРИ записи SQL выражения в несколько строк - вставлять пробелы после (или перед) каждой новой строки
//Иначе возникает ошибка при выполнении запроса
