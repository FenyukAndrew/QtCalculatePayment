#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Forms/water.h"
#include "Forms/electricity.h"
#include "Forms/gas.h"
#include "Forms/rubbish.h"
#include "control_payments.h"
#include "change_tariffs.h"
#include "Common_parameters.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ANDROID_MAKE_WINDOW_FULL_SCREEN;

    for(short i=0;i<c_types_of_payments;i++)
    {//Чтобы не было левых значений
        sum_payments[i]=0;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

enum e_types_payments { e_Water, e_Electricity, e_Gas, e_Rubbish};

void MainWindow::on_pushButtonWater_clicked()
{
    water m_water;
    //m_water->show();
    m_water.exec();
    sum_payments[e_Water]=m_water.get_sum_payment();
}

void MainWindow::on_pushButtonElectricity_clicked()
{
    Electricity m_Electricity;
    m_Electricity.exec();
    sum_payments[e_Electricity]=m_Electricity.get_sum_payment();
}


void MainWindow::on_pushButtonGas_clicked()
{
    Gas m_Gas;
    m_Gas.exec();
    sum_payments[e_Gas]=m_Gas.get_sum_payment();
}

void MainWindow::on_pushButtonRubbish_clicked()
{
    Rubbish m_Rubbish;
    m_Rubbish.exec();
    sum_payments[e_Rubbish]=m_Rubbish.get_sum_payment();
}

void MainWindow::on_pushButtonControl_clicked()
{
    Control_Payments m_Control_Payments(sum_payments);
    m_Control_Payments.exec();
}

void MainWindow::on_pushButtonTariff_clicked()
{
    Change_Tariffs m_Change_Tariffs;
    m_Change_Tariffs.exec();
}
