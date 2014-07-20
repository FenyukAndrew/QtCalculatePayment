#ifndef WATER_H
#define WATER_H

#include <QDialog>

namespace Ui {
class water;
}

class WaterDB;
class water_record;

class water : public QDialog
{
    Q_OBJECT
    
public:
    explicit water(QWidget *parent = 0);
    ~water();
    
private slots:
    void on_checkBox_HavePaid_stateChanged(int arg1);

    void on_checkBox_HavePaid_clicked();

    void on_pushButton_InputNewValue_clicked();

    void on_pushButton_OK_clicked();

private:

    void show_last_record();

    Ui::water *ui;

    WaterDB* m_WaterDB;

    water_record* m_water_record;
};

#endif // WATER_H
