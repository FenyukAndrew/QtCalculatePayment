#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Common_parameters.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    //void on_pushButton_clicked();

    void on_pushButtonElectricity_clicked();

    void on_pushButtonWater_clicked();

    void on_pushButtonGas_clicked();

    void on_pushButtonRubbish_clicked();

    void on_pushButtonControl_clicked();

    void on_pushButtonTariff_clicked();

private:
    Ui::MainWindow *ui;

    double sum_payments[c_types_of_payments];
};

#endif // MAINWINDOW_H
