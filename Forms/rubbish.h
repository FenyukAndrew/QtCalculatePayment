#ifndef RUBBISH_H
#define RUBBISH_H

#include <QDialog>
#include "Common_Struct_data.h"

class RubbishDB;

namespace Ui {
class Rubbish;
}

class Rubbish : public QDialog
{
    Q_OBJECT

public:
    explicit Rubbish(QWidget *parent = 0);
    ~Rubbish();

    double get_sum_payment() {return sum_payment;}//m_rubbish_record.Sum;}

private slots:
    void on_pushButton_InputNewValue_clicked();

    void on_pushButton_OK_clicked();

private:
    Ui::Rubbish *ui;

    void show_last_record();

    RubbishDB* m_RubbishDB;

    Rubbish_record m_rubbish_record;

    double sum_payment;//Значение совершенного платежа
};

#endif // RUBBISH_H
