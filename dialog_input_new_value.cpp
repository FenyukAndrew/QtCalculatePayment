#include "dialog_input_new_value.h"
#include "ui_dialog_input_new_value.h"
#include <QLineEdit>
#include <limits>
#include "Common_parameters.h"

#include <QDebug>

Dialog_Input_New_Value::Dialog_Input_New_Value(const QDate& last_Month_Year_Payment,std::list<QString> name_counters, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Input_New_Value)
{
    ui->setupUi(this);

    ANDROID_MAKE_WINDOW_FULL_SCREEN;

    if (last_Month_Year_Payment.isValid())
    {
        ui->dateEdit->setDate(last_Month_Year_Payment.addMonths(1));//Следующий месяц
    }
    else
    {
        QDate cur_date=QDate::currentDate();
        ui->dateEdit->setDate(QDate(cur_date.year(),cur_date.month(),1));//Всегда должно быть начало месяца - так красивее
    }

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

Dialog_Input_New_Value::Dialog_Input_New_Value(const QDate& last_Month_Year_Payment,std::list<Counter_Type>& counters, e_input_or_edit m_input_or_edit, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Input_New_Value)
{
    ui->setupUi(this);

    ANDROID_MAKE_WINDOW_FULL_SCREEN;

    if (last_Month_Year_Payment.isValid())
    {
        int add_month=(m_input_or_edit==e_dlg_new_input) ? 1 : 0;//Следующий месяц, если ввод нового месяца
        ui->dateEdit->setDate(last_Month_Year_Payment.addMonths(add_month));
    }
    else
    {
        QDate cur_date=QDate::currentDate();
        ui->dateEdit->setDate(QDate(cur_date.year(),cur_date.month(),1));//Всегда должно быть начало месяца - так красивее
    }

    //Лучше счетчики добавлять динамически
    //auto
    for(std::list<Counter_Type>::iterator it = counters.begin(); it != counters.end(); ++it)
    {
        QLineEdit* cur_edit=new QLineEdit;

        if (m_input_or_edit==e_dlg_new_input)
        {
            cur_edit->setText("0");
            cur_edit->setValidator( new QIntValidator((*it).value, std::numeric_limits<int>::max(), this) );//или LONG_MAX
        }
        else
        {//В случае редактирования можно ввести любое значение, т.к. по ошибке может быть введенно значение старше на 1 разряд
            cur_edit->setText(system_locale.toString((*it).value,'f',0));
            cur_edit->setValidator( new QIntValidator(0, std::numeric_limits<int>::max(), this) );//или LONG_MAX
        }

        ui->formLayout_Counters->addRow((*it).name,(QWidget*)cur_edit);
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
        //Сделать проверку еще раз - если не верно значение - сделать красным фон
        //В противном случае убрать фон
        const QValidator* m_validator=(*it)->validator();
        int pos = 0;
        QString t1=(*it)->text();
        QValidator::State m_state=m_validator->validate(t1,pos);
        //qDebug() << "STATE VALIDATOR:" << t1 << "=" << m_state;
        if (m_state!=QValidator::Acceptable)
        {//QValidator пропускает значения, которые почти попадают под проверку (например не прверяется диапазон значений)
            //В этом случае строка подсвечивается красным
            //QValidator::Invalid	0	The string is clearly invalid.
            //QValidator::Intermediate	1	The string is a plausible intermediate value.
            //QValidator::Acceptable	2	The string is acceptable as a final result; i.e. it is valid.*/
            QPalette *palette = new QPalette();
            palette->setColor(QPalette::Base,Qt::red);//QPalette::Text
            //QPalette::Window - цвет рамки окна вокруг
            //QPalette::Base - Цвет фона элемента Used mostly as the background color for text entry widgets, but can also be used for other painting - such as the background of combobox drop down lists and toolbar handles. It is usually white or another light color.
            (*it)->setPalette(*palette);
            (*it)->setFocus();
            return;
        }
        else
        {
            QPalette *palette = new QPalette();
            palette->setColor(QPalette::Base,Qt::white);
            (*it)->setPalette(*palette);
        }
        //values.push_back((*it)->text().toDouble());В этом случае неправильно парсяться данные
        bool ok;//Не используется - т.к. есть валидатор
        values.push_back(system_locale.toDouble((*it)->text(),&ok));
    }
    date_input=ui->dateEdit->date();

    QDialog::accept();
}

void Dialog_Input_New_Value::on_pushButton_Cancel_clicked()
{
    //this->close();
    QDialog::reject();
}
