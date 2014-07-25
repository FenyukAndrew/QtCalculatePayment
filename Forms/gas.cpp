#include "gas.h"
#include "ui_gas.h"

Gas::Gas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Gas)
{
    ui->setupUi(this);
}

Gas::~Gas()
{
    delete ui;
}
