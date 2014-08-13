#include "change_tariffs.h"
#include "ui_change_tariffs.h"

Change_Tariffs::Change_Tariffs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Change_Tariffs)
{
    ui->setupUi(this);
}

Change_Tariffs::~Change_Tariffs()
{
    delete ui;
}
