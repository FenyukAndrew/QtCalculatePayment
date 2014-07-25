#include "rubbish.h"
#include "ui_rubbish.h"

Rubbish::Rubbish(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Rubbish)
{
    ui->setupUi(this);
}

Rubbish::~Rubbish()
{
    delete ui;
}
