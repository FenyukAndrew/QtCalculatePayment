#ifndef CHANGE_TARIFFS_H
#define CHANGE_TARIFFS_H

#include <QDialog>
#include "Database/tariffsdb.h"

namespace Ui
{
class Change_Tariffs;
}

class QLineEdit;

struct Tariff_data
{
    Tariff_data(QString& n_name,double n_tariff)
    {
        name=n_name;
        tariff=n_tariff;
    }

    QString name;
    double tariff;
private:
    Tariff_data();
};

class Change_Tariffs : public QDialog
{
    Q_OBJECT

public:
    explicit Change_Tariffs(QWidget *parent = 0);
    ~Change_Tariffs();

    void Init();

private slots:
    void on_pushButton_OK_clicked();
    void on_pushButton_Cancel_clicked();
    void on_LineEdit_text_Changed();

private:
    Ui::Change_Tariffs *ui;

    TariffsDB m_TariffsDB;

    //std::list<QLineEdit*> listQLineEdit;
    std::map<QLineEdit*,Tariff_data*> mapQLineEdit;
};

#endif // CHANGE_TARIFFS_H
