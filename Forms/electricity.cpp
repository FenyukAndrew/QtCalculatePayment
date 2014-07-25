#include "electricity.h"
#include "ui_electricity.h"
#include "Common.h"

//#include <QtGui/QApplication>
#include <QtSql>
#include <QTableView>

Electricity::Electricity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Electricity)
{
    ui->setupUi(this);
}

Electricity::~Electricity()
{
    delete ui;
}

void Electricity::on_pushButton_clicked()
{
    //Не сработало - таблица не вывелась
    /*QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(pathDB);
    if (!dbase.open()) {
        qDebug() << "Что-то не так с соединением!";
        return;
    }

    QTableView& view=*(ui->tableView);
    QSqlTableModel model;

    model.setTable("Water");
    model.select();
    model.setEditStrategy(QSqlTableModel::OnFieldChange);

    view.setModel(&model);
    //view.show();
    qDebug() << "Try connect7!";*/
}

//Между запусками программы таблицы сохраняются - путь был не верен
void Electricity::on_pushButton_2_clicked()
{
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName(pathDB);
    if (!dbase.open()) {
        qDebug() << "Error connect!";
        return;
    }

    QSqlQuery a_query;
    /*// DDL query
    QString str = "CREATE TABLE my_table3 ("
            "number integer PRIMARY KEY NOT NULL, "
            "address VARCHAR(255), "
            "age integer"
            ");";
    bool b = a_query.exec(str);
    if (!b) {
        qDebug() << "Error create table!";
    }*/

    // DML
    /*QString str_insert = "INSERT INTO my_table(number, address, age) "
            "VALUES (%1, '%2', %3);";
    str = str_insert.arg("14")
            .arg("hello world str.")
            .arg("37");
    b = a_query.exec(str);
    if (!b) {
        qDebug() << "Кажется данные не вставляются, проверьте дверь, может она закрыта?";
    }*/
    //.....
    if (!a_query.exec("SELECT * FROM Water")) {
        qDebug() << "Error select.";
        return;
    }
    QSqlRecord rec = a_query.record();
    int number = 0,
            age = 0;
    QString address = "";

    while (a_query.next())
    {
        /*number = a_query.value(rec.indexOf("number")).toInt();
        age = a_query.value(rec.indexOf("age")).toInt();
        address = a_query.value(rec.indexOf("address")).toString();

        qDebug() << "number is " << number
                 << ". age is " << age
                 << ". address" << address;*/
        qDebug() << "_id= " << a_query.value(rec.indexOf("_id")).toString()
                 << "Value= " << a_query.value(rec.indexOf("Value")).toString()
                 << "Sum= " << a_query.value(rec.indexOf("Sum")).toString();

/*        _id INTEGER PRIMARY KEY AUTOINCREMENT,
        Date_Input_Value DateTime,
        Value real,
        Sum real,
        Sum_Commission real,
        Date_Payment DateTime,
        Tariff real,
        Month_Payment char,
        Year_Payment char
        , "DatePayment" DATETIME)*/

    }
}
