#include "electricity.h"
#include "ui_electricity.h"
#include "Database/electricitydb.h"
#include <QLocale>
#include "dialog_input_new_value.h"

Electricity::Electricity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Electricity)
{
    ui->setupUi(this);

    m_ElectricityDB=new ElectricityDB();
    show_last_record();
}

void Electricity::show_last_record()
{
    if (m_ElectricityDB->get_last_record(&m_electricity_record))
    {

    QLocale russain_locale(QLocale::Russian);

    ui->Date_Input_Value->setText(russain_locale.toString(m_electricity_record.Date_Input_Value,"dd.MM.yyyy hh:mm:ss"));
    ui->Month_Year_Payment->setText(russain_locale.toString(m_electricity_record.Month_Year_Payment,"MM\\yyyy"));

    ui->Value_Day->setText(russain_locale.toString(m_electricity_record.Value_Day));
    ui->Value_Night->setText(russain_locale.toString(m_electricity_record.Value_Night));
    ui->Value_External->setText(russain_locale.toString(m_electricity_record.Value_External));
    ui->Delta_devices->setText(russain_locale.toString(m_electricity_record.delta_devices));

    ui->Sum->setText(russain_locale.toString(m_electricity_record.Sum,'f',3));
    if (m_electricity_record.Date_Payment.isValid())
    {
        //Вывод когда была произведена оплата
        ui->checkBox_HavePaid->setText("ОПЛАЧЕНО "+russain_locale.toString(m_electricity_record.Date_Payment,"dd.MM.yyyy hh:mm:ss"));
        ui->checkBox_HavePaid->setChecked(1);
        ui->checkBox_HavePaid->setEnabled(0);//Подавление, чтобы нельзя бы изменить состояние
        ui->pushButton_InputNewValue->setEnabled(1);
    }
    else
    {
        ui->checkBox_HavePaid->setText("ОПЛАТИТЬ");
        ui->checkBox_HavePaid->setChecked(0);
        ui->checkBox_HavePaid->setEnabled(1);
        ui->pushButton_InputNewValue->setEnabled(0);//Подавление, чтобы нельзя бы перейти к вводу нового значения
    }
    }
}

Electricity::~Electricity()
{
    delete ui;
    delete m_ElectricityDB;
}

void Electricity::on_pushButton_InputNewValue_clicked()
{
    std::list<QString> name_counters;
    name_counters.push_back(QString("Значение счетчика День:"));
    name_counters.push_back(QString("Значение счетчика Ночь:"));
    name_counters.push_back(QString("Значение счетчика Внешний:"));
    Dialog_Input_New_Value m_dialog_input_new_value(name_counters);
    int retCode = m_dialog_input_new_value.exec();

    if (retCode==QDialog::Accepted)
    {
        Electricity_record m_electricity_record;
        std::vector<double> values=m_dialog_input_new_value.get_Value();
        m_electricity_record.Value_Day=values[0];
        m_electricity_record.Value_Night=values[1];
        m_electricity_record.Value_External=values[2];
        m_electricity_record.Month_Year_Payment=m_dialog_input_new_value.get_Date();
        m_ElectricityDB->insert_new_record(&m_electricity_record);

        show_last_record();
    }
}

void Electricity::on_pushButton_OK_clicked()
{
    if (!m_electricity_record.Date_Payment.isValid())
    {//Только в случае первого ввода данных
        if (ui->checkBox_HavePaid->isChecked())
        {//Update делается только если подтвержден платеж
            m_ElectricityDB->update_new_record(&m_electricity_record);
        };
    };
    close();
}
