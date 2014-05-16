#ifndef DIALOG_INPUT_NEW_VALUE_H
#define DIALOG_INPUT_NEW_VALUE_H

#include <QDialog>

namespace Ui {
class Dialog_Input_New_Value;
}

class Dialog_Input_New_Value : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_Input_New_Value(QWidget *parent = 0);
    ~Dialog_Input_New_Value();
    
private:
    Ui::Dialog_Input_New_Value *ui;
};

#endif // DIALOG_INPUT_NEW_VALUE_H
