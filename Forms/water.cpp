#include "water.h"
#include "ui_water.h"
#include "Database/waterdb.h"
#include "dialog_input_new_value.h"
#include "Common_parameters.h"

water::water(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::water)
{
    ui->setupUi(this);

    ANDROID_MAKE_WINDOW_FULL_SCREEN;

    m_WaterDB=new WaterDB();
    show_last_record();
}

void water::show_last_record()
{
    sum_payment=0;//По умолчанию считается, что платеж не совершен

    if (m_WaterDB->get_last_record(&m_water_record))
    {
        //QLocale::LongFormat - пятница, 3 января 2014 г. 1:00:00 MSK
        //QLocale::ShortFormat - 01.01.01 00:00
        //QLocale::NarrowFormat - 03.01.14 1:00
        ui->Date_Input_Value->setText(system_locale.toString(m_water_record.Date_Input_Value,c_format_Date_Input_Value));
        ui->Month_Year_Payment->setText(system_locale.toString(m_water_record.Month_Year_Payment,c_format_Date_Month_Year_Payment));

        //3 знака после запятой, т.к. округление может работать неверно
        ui->Value->setText(system_locale.toString(m_water_record.Value));
        //ui->Value->setText(system_locale.toString(m_water_record.Value,'f',3));
        ui->Sum->setText(system_locale.toString(m_water_record.Sum,'f',3));
        ui->Commission->setText(system_locale.toString(m_water_record.Sum/100,'f',3));
        ui->Sum_Commission->setText(system_locale.toString(m_water_record.Sum_Commission,'f',3));//g выводит в формате 1e+3
        //if (!m_water_record->Date_Payment.isNull())
        if (m_water_record.Date_Payment.isValid())
        {
            //Вывод когда была произведена оплата
            ui->checkBox_HavePaid->setText("ОПЛАЧЕНО "+system_locale.toString(m_water_record.Date_Payment,c_format_Date_checkBox_HavePaid));
            ui->checkBox_HavePaid->setChecked(1);
            ui->checkBox_HavePaid->setEnabled(0);//Подавление, чтобы нельзя бы изменить состояние
            ui->pushButton_InputNewValue->setEnabled(1);
            //qDebug() << "VALID";
        }
        else
        {
            ui->checkBox_HavePaid->setText("ОПЛАТИТЬ");
            ui->checkBox_HavePaid->setChecked(0);
            ui->checkBox_HavePaid->setEnabled(1);
            ui->pushButton_InputNewValue->setEnabled(0);//Подавление, чтобы нельзя бы перейти к вводу нового значения
            //qDebug() << "not valid";
        }
    }
}

water::~water()
{
    //if (m_water_record) delete m_water_record;
    delete ui;
    delete m_WaterDB;
}

void water::on_checkBox_HavePaid_stateChanged(int arg1)
{
    //Можно использовать для сохранения значения при оплате
    /*qDebug() << arg1;
    if (arg1!=0)
    {
        //qDebug() << "ON";
    }
    else
    {
        //qDebug() << "OFF";
    }*/
}

void water::on_checkBox_HavePaid_clicked()
{
    //qDebug() << "Click by user!";

}

void water::on_pushButton_InputNewValue_clicked()
{
    std::list<QString> name_counters;
    name_counters.push_back(QString("Значение счетчика:"));
    Dialog_Input_New_Value m_dialog_input_new_value(m_water_record.Month_Year_Payment,name_counters);
    int retCode = m_dialog_input_new_value.exec();

    if (retCode==QDialog::Accepted)
    {
        Water_record m_water_new_record;
        m_water_new_record.Value=m_dialog_input_new_value.get_Value()[0];
        m_water_new_record.Month_Year_Payment=m_dialog_input_new_value.get_Date();
        m_WaterDB->insert_new_record(&m_water_new_record);

        show_last_record();
    }
}

void water::on_pushButton_EditValue_clicked()
{

}

void water::on_pushButton_OK_clicked()
{
    //if (ui->checkBox_HavePaid->isEnabled())
    if (!m_water_record.Date_Payment.isValid())
    {
        //Только в случае первого ввода данных
        if (ui->checkBox_HavePaid->isChecked())
        {
            //Update делается только если подтвержден платеж
            m_WaterDB->update_new_record(&m_water_record);
        };
        sum_payment=m_water_record.Sum_Commission;//Только что произведена оплата, добавление в общую сумму
    }
    else
    {
        //В случае просмотра только что совершенных платежей
        if (QDateTime::currentDateTime().secsTo(m_water_record.Date_Payment)<C_TIME_FROM_PAYMENT)
        {
            //Если оплата была произведена недавно добавить ее в список для вычисления Конроль
            sum_payment=m_water_record.Sum_Commission;
        }
    };
    close();
}
