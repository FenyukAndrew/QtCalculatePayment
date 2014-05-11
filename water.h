#ifndef WATER_H
#define WATER_H

#include <QDialog>

namespace Ui {
class water;
}

class water : public QDialog
{
    Q_OBJECT
    
public:
    explicit water(QWidget *parent = 0);
    ~water();
    
private:
    Ui::water *ui;
};

#endif // WATER_H
