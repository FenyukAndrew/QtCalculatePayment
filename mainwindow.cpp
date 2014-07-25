#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Forms/water.h"
#include "Forms/electricity.h"
#include "Forms/gas.h"
#include "Forms/rubbish.h"
#include "control_payments.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonWater_clicked()
{
    water m_water;
    //m_water->show();
    m_water.exec();
}

void MainWindow::on_pushButtonElectricity_clicked()
{
    Electricity m_Electricity;
    m_Electricity.exec();
}


void MainWindow::on_pushButtonGas_clicked()
{
    Gas m_Gas;
    m_Gas.exec();
}

void MainWindow::on_pushButtonRubbish_clicked()
{
    Rubbish m_Rubbish;
    m_Rubbish.exec();
}

void MainWindow::on_pushButtonControl_clicked()
{
    Control_Payments m_Control_Payments;
    m_Control_Payments.exec();
}

void MainWindow::on_pushButtonTariff_clicked()
{

}
