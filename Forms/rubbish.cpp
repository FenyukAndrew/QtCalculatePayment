#include "rubbish.h"
#include "ui_rubbish.h"
#include "Database/rubbishdb.h"
#include <QLocale>
#include "dialog_input_new_value.h"

Rubbish::Rubbish(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rubbish)
{
    ui->setupUi(this);

    m_RubbishDB=new RubbishDB();
    show_last_record();
}

void Rubbish::show_last_record()
{
if(m_RubbishDB->get_last_record(&m_rubbish_record))
{

QLocale russain_locale(QLocale::Russian);

ui->Date_Input_Value->setText(russain_locale.toString(m_rubbish_record.Date_Input_Value,"dd.MM.yyyy hh:mm:ss"));
ui->Month_Year_Payment->setText(russain_locale.toString(m_rubbish_record.Month_Year_Payment,"MM\\yyyy"));

ui->Sum->setText(russain_locale.toString(m_rubbish_record.Sum,'f',3));
if (m_rubbish_record.Date_Payment.isValid())
{
    //Вывод когда была произведена оплата
    ui->checkBox_HavePaid->setText("ОПЛАЧЕНО "+russain_locale.toString(m_rubbish_record.Date_Payment,"dd.MM.yyyy hh:mm:ss"));
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

Rubbish::~Rubbish()
{
    delete ui;
    delete m_RubbishDB;
}

void Rubbish::on_pushButton_InputNewValue_clicked()
{
    std::list<QString> name_counters;
    Dialog_Input_New_Value m_dialog_input_new_value(name_counters);
    int retCode = m_dialog_input_new_value.exec();

    if (retCode==QDialog::Accepted)
    {
        Rubbish_record m_rubbish_record;
        m_rubbish_record.Month_Year_Payment=m_dialog_input_new_value.get_Date();
        m_RubbishDB->insert_new_record(&m_rubbish_record);

        show_last_record();
    }
}

void Rubbish::on_pushButton_OK_clicked()
{
if (!m_rubbish_record.Date_Payment.isValid())
{//Только в случае первого ввода данных
    if (ui->checkBox_HavePaid->isChecked())
    {//Update делается только если подтвержден платеж
        m_RubbishDB->update_new_record(&m_rubbish_record);
    };
};
close();
}
