#include "tariffsdb.h"

TariffsDB::TariffsDB()
{
}

bool TariffsDB::create_cursor()
{
    if (!a_query->exec("SELECT ShowName,Value FROM Tariffs order by ShowName"))
    {
        qDebug() << "Error select Tariffs";
        return false;
    }
    return true;
}


bool TariffsDB::get_next_record(QString& name,double& tariff)
{
    if (a_query->next())
    {
        QSqlRecord rec = a_query->record();
        name=a_query->value(rec.indexOf("ShowName")).toString();
        tariff=a_query->value(rec.indexOf("Value")).toDouble();

        return true;
    }
    return false;
}

void TariffsDB::update_new_record(QString& name,double& tariff)
{
    a_query->prepare("UPDATE Tariffs"
                     " SET Value=:tariff"
                     " WHERE ShowName=:name");
    a_query->bindValue(":name", name);
    a_query->bindValue(":tariff", tariff);
    if (!a_query->exec())
    {
        qDebug() << "Error update Tariffs";
    }
}
