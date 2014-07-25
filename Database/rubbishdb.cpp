#include "rubbishdb.h"

RubbishDB::RubbishDB()
{
    cur_tariff=get_tariff("Rubbish");
}

RubbishDB::~RubbishDB()
{
}

void RubbishDB::get_last_record(Rubbish_record* m_rubbish_record)
{
    //Записи сортируются по _id = иначе неправильный ввод значения может все испортить
    //Записи идут в обратном порядке - вначале самая последняя, затем предпоследняя
   if (!a_query->exec("SELECT Date_Input_Value,Sum,Date_Payment,Month_Payment,Year_Payment FROM Rubbish order by _id DESC limit 1"))
    {
        qDebug() << "Error select Rubbish";
        return;
    }
    QSqlRecord rec = a_query->record();

    if (a_query->next())
    {
        m_rubbish_record->Init();//Все значения возвращаются в исходные
        m_rubbish_record->Date_Input_Value=a_query->value(rec.indexOf("Date_Input_Value")).toDateTime();
        m_rubbish_record->Sum=a_query->value(rec.indexOf("Sum")).toDouble();
        m_rubbish_record->Date_Payment=a_query->value(rec.indexOf("Date_Payment")).toDateTime();
        int month=a_query->value(rec.indexOf("Month_Payment")).toInt();
        int year=a_query->value(rec.indexOf("Year_Payment")).toInt();
        m_rubbish_record->Month_Year_Payment=QDate(year,month,1);

        if (!m_rubbish_record->Date_Payment.isValid())
        {//Если оплата не произведена - производяться вычисления
            //Чтоб их было видно перед добавлением в базу
            //и они были актуальны на время оплаты
            m_rubbish_record->Sum=cur_tariff;
        }
    }
}

void RubbishDB::insert_new_record(Rubbish_record* m_rubbish_record)
{
    a_query->prepare("INSERT INTO Rubbish (Date_Input_Value,Month_Payment,Year_Payment)"
                  " VALUES (datetime('now','localtime'),:month_payment,:year_payment)");
    a_query->bindValue(":month_payment", m_rubbish_record->Month_Year_Payment.month());
    a_query->bindValue(":year_payment",  m_rubbish_record->Month_Year_Payment.year());
    if (!a_query->exec())
    {
            qDebug() << "Error insert Rubbish";
    }
}

void RubbishDB::update_new_record(Rubbish_record* m_rubbish_record)
{
    a_query->prepare("UPDATE Rubbish"
                    " SET Date_Payment=(datetime('now', 'localtime')),Sum=:total_sum"
                  " WHERE _id=(select max(_id) from Rubbish)");
    a_query->bindValue(":total_sum", m_rubbish_record->Sum);
    if (!a_query->exec())
    {
            qDebug() << "Error update Rubbish";
    }
}
