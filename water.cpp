#include "water.h"
#include "waterdb.h"
#include "ui_water.h"
#include <QLocale>
#include "dialog_input_new_value.h"

water::water(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::water)
{
    ui->setupUi(this);

    QLocale russain_locale(QLocale::Russian);

    m_WaterDB=new WaterDB();

    water_record* m_water_record=m_WaterDB->get_last_data();

    //QLocale::LongFormat - пятница, 3 января 2014 г. 1:00:00 MSK
    //QLocale::ShortFormat - 01.01.01 00:00
    //QLocale::NarrowFormat - 03.01.14 1:00
    ui->Date_Input_Value->setText(russain_locale.toString(m_water_record->Date_Input_Value,"dd.MM.yyyy hh:mm:ss"));
    //3 знака после запятой, т.к. округление может работать неверно
    ui->Value->setText(russain_locale.toString(m_water_record->Value,'f',3));
    ui->Sum->setText(russain_locale.toString(m_water_record->Sum,'f',3));
    ui->Commission->setText(russain_locale.toString(m_water_record->Sum/100,'f',3));
    ui->Sum_Commission->setText(russain_locale.toString(m_water_record->Sum_Commission,'g',3));
    //if (!m_water_record->Date_Payment.isNull())
    if (m_water_record->Date_Payment.isValid())
    {
        //Вывод когда была произведена оплата
        ui->checkBox_HavePaid->setText(ui->checkBox_HavePaid->text()+" "+russain_locale.toString(m_water_record->Date_Payment,"dd.MM.yyyy hh:mm:ss"));
        ui->checkBox_HavePaid->setChecked(1);
        ui->checkBox_HavePaid->setEnabled(0);//Подавление, чтобы нельзя бы изменить состояние
        //qDebug() << "VALID";
    }
    else
    {
        ui->checkBox_HavePaid->setChecked(0);
        //qDebug() << "not valid";
    }
}

water::~water()
{
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
    Dialog_Input_New_Value* m_dialog_input_new_value=new Dialog_Input_New_Value();
    m_dialog_input_new_value->show();

}
