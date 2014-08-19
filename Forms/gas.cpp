#include "gas.h"
#include "ui_gas.h"
#include "Database/gasdb.h"
#include "dialog_input_new_value.h"
#include "Common_parameters.h"

Gas::Gas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gas)
{
    ui->setupUi(this);

    ANDROID_MAKE_WINDOW_FULL_SCREEN;

    m_GasDB=new GasDB();
    show_last_record();
}

void Gas::show_last_record()
{
    sum_payment=0;//По умолчанию считается, что платеж не совершен

    if (m_GasDB->get_last_record(&m_gas_record))
    {

        ui->Date_Input_Value->setText(system_locale.toString(m_gas_record.Date_Input_Value,c_format_Date_Input_Value));
        ui->Month_Year_Payment->setText(system_locale.toString(m_gas_record.Month_Year_Payment,c_format_Date_Month_Year_Payment));

        ui->Value->setText(system_locale.toString(m_gas_record.Value));
        ui->Sum->setText(system_locale.toString(m_gas_record.Sum,'f',3));
        if (m_gas_record.Date_Payment.isValid())
        {
            //Вывод когда была произведена оплата
            ui->checkBox_HavePaid->setText("ОПЛАЧЕНО "+system_locale.toString(m_gas_record.Date_Payment,c_format_Date_checkBox_HavePaid));
            ui->checkBox_HavePaid->setChecked(1);
            ui->checkBox_HavePaid->setEnabled(0);//Подавление, чтобы нельзя бы изменить состояние
            ui->pushButton_InputNewValue->setEnabled(1);
            if (QDateTime::currentDateTime().secsTo(m_gas_record.Date_Payment)<C_TIME_FROM_PAYMENT)
            {
                //Если оплата была произведена недавно добавить ее в список для вычисления Конроль
                sum_payment=m_gas_record.Sum;
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

Gas::~Gas()
{
    delete ui;
    delete m_GasDB;
}

void Gas::on_pushButton_InputNewValue_clicked()
{
    std::list<QString> name_counters;
    name_counters.push_back(QString("Значение счетчика:"));
    Dialog_Input_New_Value m_dialog_input_new_value(name_counters);
    int retCode = m_dialog_input_new_value.exec();

    if (retCode==QDialog::Accepted)
    {
        Gas_record m_gas_record;
        m_gas_record.Value=m_dialog_input_new_value.get_Value()[0];
        m_gas_record.Month_Year_Payment=m_dialog_input_new_value.get_Date();
        m_GasDB->insert_new_record(&m_gas_record);

        show_last_record();
    }
}

void Gas::on_pushButton_OK_clicked()
{
    if (!m_gas_record.Date_Payment.isValid())
    {
        //Только в случае первого ввода данных
        if (ui->checkBox_HavePaid->isChecked())
        {
            //Update делается только если подтвержден платеж
            m_GasDB->update_new_record(&m_gas_record);
        };
    };
    close();
}
