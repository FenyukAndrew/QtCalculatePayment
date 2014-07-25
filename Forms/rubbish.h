#ifndef RUBBISH_H
#define RUBBISH_H

#include <QDialog>

namespace Ui {
class Rubbish;
}

class Rubbish : public QDialog
{
    Q_OBJECT

public:
    explicit Rubbish(QWidget *parent = 0);
    ~Rubbish();

private:
    Ui::Rubbish *ui;
};

#endif // RUBBISH_H
