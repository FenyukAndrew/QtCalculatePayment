#include "water.h"
#include "ui_water.h"

water::water(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::water)
{
    ui->setupUi(this);

}

water::~water()
{
    delete ui;
}
