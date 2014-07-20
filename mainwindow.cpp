#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "water.h"
#include "electricity.h"

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
    water* m_water=new water();
    m_water->show();

}

void MainWindow::on_pushButtonElectricity_clicked()
{
    Electricity* m_Electricity=new Electricity();
    m_Electricity->show();
}


void MainWindow::on_pushButtonGas_clicked()
{

}

void MainWindow::on_pushButtonRubbish_clicked()
{

}

void MainWindow::on_pushButtonControl_clicked()
{

}
