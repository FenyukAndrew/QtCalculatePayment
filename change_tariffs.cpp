#include "change_tariffs.h"
#include "ui_change_tariffs.h"
#include <QLineEdit>
#include <algorithm>
#include "Common_parameters.h"

Change_Tariffs::Change_Tariffs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Change_Tariffs)
{
    ui->setupUi(this);

    ANDROID_MAKE_WINDOW_FULL_SCREEN;

    Init();
}

/*void deleteObject(QLineEdit* mQLineEdit)
{
    delete mQLineEdit;
}*/

Change_Tariffs::~Change_Tariffs()
{
    delete ui;

    //Возможно удаление не требуется - об удалении должен позаботиться хозяин объекта
    //for_each(listQLineEdit.begin(), listQLineEdit.end(),deleteObject);
    std::for_each(mapQLineEdit.begin(),mapQLineEdit.end(),
                  [](std::pair<QLineEdit* const, Tariff_data*>& m_pair)
    {
        delete m_pair.first;
        delete m_pair.second;
    });
}

void Change_Tariffs::Init()
{
    if (!m_TariffsDB.create_cursor()) return;

    QString name="";
    double tariff=0;
    while(m_TariffsDB.get_next_record(name,tariff))
    {
        QLineEdit* mLineEdit=new QLineEdit();

        mLineEdit->setText(system_locale.toString(tariff,'f',2));
        mLineEdit->setAlignment(Qt::AlignRight);
        mLineEdit->setValidator(new QDoubleValidator(0, std::numeric_limits<double>::max(), 2, this));//2 знака после запятой

        connect(mLineEdit, SIGNAL(editingFinished()), this, SLOT(on_LineEdit_text_Changed()));
        //Неработает - Возникает ошибка No such signal QLineEdit::textChanged()
        //connect(mLineEdit, SIGNAL(textChanged(const QString & text)), this, SLOT(on_LineEdit_text_Changed(const QString & text)));

        //listQLineEdit.push_back(mLineEdit);
        mapQLineEdit[mLineEdit]=new Tariff_data(name,tariff);

        ui->formLayoutTariffs->addRow (name, mLineEdit);
    }

}

void Change_Tariffs::on_LineEdit_text_Changed()
{
    QObject* m_Object=sender();//Объект, пославший сигнал
    QLineEdit* mLineEdit=dynamic_cast<QLineEdit*>(m_Object);

    //Измененные строки подсвечивать
    if (mLineEdit)
    {
        QPalette *palette = new QPalette();
        palette->setColor(QPalette::Text,Qt::red);
        mLineEdit->setPalette(*palette);
    }
}

void Change_Tariffs::on_pushButton_OK_clicked()
{
    //Запись в базу изменений

    //Возможен проход по всем элементам управления через QLayoutItem * QFormLayout::itemAt ( int row, ItemRole role ) const
    //ui->formLayoutTariffs->rowCount();

    /*for(auto t=mapQLineEdit.begin();t!=mapQLineEdit.end();t++)
    {

    }*/

    std::for_each(mapQLineEdit.begin(),mapQLineEdit.end(),
                  [&](std::pair<QLineEdit* const, Tariff_data*>& m_pair) //[&] - все переменные захватываются по ссылке
    {
        //Чтобы не возникало проблем с языковыми настойками использовать
        bool ok;
        double new_tariff=system_locale.toDouble(m_pair.first->text(),&ok);
        if (ok)
        {//Чтобы избежать случайного обнуления всех записей из-за ошибки национальных настроек
            Tariff_data* m_Tariff_data=m_pair.second;
            if (new_tariff!=m_Tariff_data->tariff)
            {//Запись нового значения
                m_TariffsDB.update_new_record(m_Tariff_data->name,new_tariff);
            }
        }
    });
    QDialog::accept();
}

void Change_Tariffs::on_pushButton_Cancel_clicked()
{
    this->close();
    QDialog::reject();
}
