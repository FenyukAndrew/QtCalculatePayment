#ifndef CHANGE_TARIFFS_H
#define CHANGE_TARIFFS_H

#include <QDialog>

namespace Ui {
class Change_Tariffs;
}

class Change_Tariffs : public QDialog
{
    Q_OBJECT

public:
    explicit Change_Tariffs(QWidget *parent = 0);
    ~Change_Tariffs();

private:
    Ui::Change_Tariffs *ui;
};

#endif // CHANGE_TARIFFS_H
