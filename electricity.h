#ifndef ELECTRICITY_H
#define ELECTRICITY_H

#include <QDialog>

namespace Ui {
class Electricity;
}

class Electricity : public QDialog
{
    Q_OBJECT
    
public:
    explicit Electricity(QWidget *parent = 0);
    ~Electricity();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Electricity *ui;
};

#endif // ELECTRICITY_H
