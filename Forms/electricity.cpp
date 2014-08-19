#include "electricity.h"
#include "ui_electricity.h"
#include "Database/electricitydb.h"
#include "dialog_input_new_value.h"
#include "Common_parameters.h"

Electricity::Electricity(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Electricity)
{
    ui->setupUi(this);

    ANDROID_MAKE_WINDOW_FULL_SCREEN;

    m_ElectricityDB=new ElectricityDB();
    show_last_record();
}

void Electricity::show_last_record()
{
    sum_payment=0;//По умолчанию считается, что платеж не совершен

    if (m_ElectricityDB->get_last_record(&m_electricity_record))
    {

        ui->Date_Input_Value->setText(system_locale.toString(m_electricity_record.Date_Input_Value,c_format_Date_Input_Value));
        ui->Month_Year_Payment->setText(system_locale.toString(m_electricity_record.Month_Year_Payment,c_format_Date_Month_Year_Payment));

        ui->Last_Value_Day->setText(system_locale.toString(m_electricity_record.Last_Value_Day));
        ui->Value_Day->setText(system_locale.toString(m_electricity_record.Value_Day));
        ui->Last_Value_Night->setText(system_locale.toString(m_electricity_record.Last_Value_Night));
        ui->Value_Night->setText(system_locale.toString(m_electricity_record.Value_Night));
        ui->Value_External->setText(system_locale.toString(m_electricity_record.Value_External));
        ui->Delta_devices->setText(system_locale.toString(m_electricity_record.delta_devices));
        ui->sum_Saving->setText(system_locale.toString(m_electricity_record.Savings,'f',2));

        ui->Sum->setText(system_locale.toString(m_electricity_record.Sum,'f',3));
        if (m_electricity_record.Date_Payment.isValid())
        {
            //Вывод когда была произведена оплата
            ui->checkBox_HavePaid->setText("ОПЛАЧЕНО "+system_locale.toString(m_electricity_record.Date_Payment,c_format_Date_checkBox_HavePaid));
            ui->checkBox_HavePaid->setChecked(1);
            ui->checkBox_HavePaid->setEnabled(0);//Подавление, чтобы нельзя бы изменить состояние
            ui->pushButton_InputNewValue->setEnabled(1);
            if (QDateTime::currentDateTime().secsTo(m_electricity_record.Date_Payment)<C_TIME_FROM_PAYMENT)
            {
                //Если оплата была произведена недавно добавить ее в список для вычисления Конроль
                sum_payment=m_electricity_record.Sum;
            }
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
    name_counters.push_back(QString("Счетчик День:"));
    name_counters.push_back(QString("Счетчик Ночь:"));
    name_counters.push_back(QString("Счетчик Внешний:"));
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
    {
        //Только в случае первого ввода данных
        if (ui->checkBox_HavePaid->isChecked())
        {
            //Update делается только если подтвержден платеж
            m_ElectricityDB->update_new_record(&m_electricity_record);
        };
    };
    close();
}
