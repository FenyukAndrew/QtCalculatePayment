#include "dialog_input_new_value.h"
#include "ui_dialog_input_new_value.h"
#include <QLineEdit>

#include <limits>

Dialog_Input_New_Value::Dialog_Input_New_Value(std::list<QString> name_counters, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Input_New_Value)
{
    ui->setupUi(this);

    ui->dateEdit->setDate(QDate::currentDate());

    //Лучше счетчики добавлять динамически
    //auto
    for(std::list<QString>::iterator it = name_counters.begin(); it != name_counters.end(); ++it)
    {
        QLineEdit* cur_edit=new QLineEdit;
        cur_edit->setText("0");
        cur_edit->setValidator( new QIntValidator(0, std::numeric_limits<int>::max(), this) );//или LONG_MAX

        ui->formLayout_Counters->addRow(*it,(QWidget*)cur_edit);
        m_QLineEdits.push_back(cur_edit);
    }

        //Можно ограничить число символов, т.к. разрядность счетчика ограничена
        //ui->lineEditValue->setInputMask("00009");
        //ui->lineEditValue->setMaxLength(5);

        //myLineEdit->setValidator( new QDoubleValidator(0, 100, this) )
}

Dialog_Input_New_Value::~Dialog_Input_New_Value()
{
    delete ui;
}

void Dialog_Input_New_Value::on_pushButton_OK_clicked()
{
    for(std::vector<QLineEdit*>::iterator it = m_QLineEdits.begin(); it != m_QLineEdits.end(); ++it)
    {
        values.push_back((*it)->text().toDouble());
    }
    date_input=ui->dateEdit->date();

    QDialog::accept();
}

void Dialog_Input_New_Value::on_pushButton_Cancel_clicked()
{
    //this->close();
    QDialog::reject();
}
