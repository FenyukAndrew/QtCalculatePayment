#include "water.h"
#include "Database/waterdb.h"
#include "ui_water.h"
#include <QLocale>
#include "dialog_input_new_value.h"

water::water(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::water)
{
    ui->setupUi(this);

    m_WaterDB=new WaterDB();
    show_last_record();
}

void water::show_last_record()
{
    m_WaterDB->get_last_record(&m_water_record);

    QLocale russain_locale(QLocale::Russian);

    //QLocale::LongFormat - пятница, 3 января 2014 г. 1:00:00 MSK
    //QLocale::ShortFormat - 01.01.01 00:00
    //QLocale::NarrowFormat - 03.01.14 1:00
    ui->Date_Input_Value->setText(russain_locale.toString(m_water_record.Date_Input_Value,"dd.MM.yyyy hh:mm:ss"));
    ui->Month_Year_Payment->setText(russain_locale.toString(m_water_record.Month_Year_Payment,"MM\\yyyy"));

    //3 знака после запятой, т.к. округление может работать неверно
    ui->Value->setText(russain_locale.toString(m_water_record.Value));
    //ui->Value->setText(russain_locale.toString(m_water_record.Value,'f',3));
    ui->Sum->setText(russain_locale.toString(m_water_record.Sum,'f',3));
    ui->Commission->setText(russain_locale.toString(m_water_record.Sum/100,'f',3));
    ui->Sum_Commission->setText(russain_locale.toString(m_water_record.Sum_Commission,'f',3));//g выводит в формате 1e+3
    //if (!m_water_record->Date_Payment.isNull())
    if (m_water_record.Date_Payment.isValid())
    {
        //Вывод когда была произведена оплата
        ui->checkBox_HavePaid->setText("ОПЛАЧЕНО "+russain_locale.toString(m_water_record.Date_Payment,"dd.MM.yyyy hh:mm:ss"));
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

water::~water()
{
    //if (m_water_record) delete m_water_record;
    delete ui;
    delete m_WaterDB;
}

void water::on_checkBox_HavePaid_stateChanged(int arg1)
{
    /*qDebug() << arg1;
    if (arg1!=0)
    {
        qDebug() << "ON";
    }
    else
    {
        qDebug() << "OFF";
    }*/
}

void water::on_checkBox_HavePaid_clicked()
{
    //qDebug() << "Click by user!";

}

void water::on_pushButton_InputNewValue_clicked()
{
    Dialog_Input_New_Value m_dialog_input_new_value;
    int retCode = m_dialog_input_new_value.exec();

    if (retCode==QDialog::Accepted)
    {
        Water_record m_water_record;
        m_water_record.Value=m_dialog_input_new_value.get_Value();
        m_water_record.Month_Year_Payment=m_dialog_input_new_value.get_Date();
        m_WaterDB->insert_new_record(&m_water_record);

        show_last_record();
    }
}

void water::on_pushButton_OK_clicked()
{
    //if (ui->checkBox_HavePaid->isEnabled())
    if (!m_water_record.Date_Payment.isValid())
    {//Только в случае первого ввода данных
        if (ui->checkBox_HavePaid->isChecked())
        {//Update делается только если подтвержден платеж
            m_WaterDB->update_new_record(&m_water_record);
        };
    };
    close();
}
