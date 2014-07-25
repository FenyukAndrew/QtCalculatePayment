#ifndef GAS_H
#define GAS_H

#include <QDialog>

namespace Ui {
class Gas;
}

class Gas : public QDialog
{
    Q_OBJECT

public:
    explicit Gas(QWidget *parent = 0);
    ~Gas();

private:
    Ui::Gas *ui;
};

#endif // GAS_H
