#include "gas.h"
#include "ui_gas.h"
#include "Database/gasdb.h"
#include <QLocale>
#include "dialog_input_new_value.h"

Gas::Gas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gas)
{
    ui->setupUi(this);

    m_GasDB=new GasDB();
    show_last_record();
}

void Gas::show_last_record()
{
    if (m_GasDB->get_last_record(&m_gas_record))
    {

    QLocale russain_locale(QLocale::Russian);

    ui->Date_Input_Value->setText(russain_locale.toString(m_gas_record.Date_Input_Value,"dd.MM.yyyy hh:mm:ss"));
    ui->Month_Year_Payment->setText(russain_locale.toString(m_gas_record.Month_Year_Payment,"MM\\yyyy"));

    ui->Value->setText(russain_locale.toString(m_gas_record.Value));
    ui->Sum->setText(russain_locale.toString(m_gas_record.Sum,'f',3));
    if (m_gas_record.Date_Payment.isValid())
    {
        //Вывод когда была произведена оплата
        ui->checkBox_HavePaid->setText("ОПЛАЧЕНО "+russain_locale.toString(m_gas_record.Date_Payment,"dd.MM.yyyy hh:mm:ss"));
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
    {//Только в случае первого ввода данных
        if (ui->checkBox_HavePaid->isChecked())
        {//Update делается только если подтвержден платеж
            m_GasDB->update_new_record(&m_gas_record);
        };
    };
    close();
}
