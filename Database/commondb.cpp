#include "commondb.h"
#include "Common.h"

CommonDB::CommonDB() : dbase(QSqlDatabase::addDatabase("QSQLITE"))
{
    dbase.setDatabaseName(pathDB);
    if (!dbase.open())
    {
        qDebug() << "Error connect!";
        return;
    }

    a_query=new QSqlQuery(dbase);
}

CommonDB::~CommonDB()
{
    delete a_query;
}

double CommonDB::get_tariff(const std::string name_tariff)
{
    a_query->prepare("SELECT Value FROM tariffs where NameTable=:name_table");
    a_query->bindValue(":name_table", name_tariff.c_str());
    if (!a_query->exec())
    {
        qDebug() << "Error SELECT Value FROM tariffs.";
        return 0;
    }
    QSqlRecord rec = a_query->record();

    while (a_query->next())
    {
        return a_query->value(rec.indexOf("Value")).toDouble();
    }
    return 0;
}

