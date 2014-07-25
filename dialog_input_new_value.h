#ifndef DIALOG_INPUT_NEW_VALUE_H
#define DIALOG_INPUT_NEW_VALUE_H

#include <QDialog>
#include <QDate>

namespace Ui {
class Dialog_Input_New_Value;
}

class Dialog_Input_New_Value : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog_Input_New_Value(QWidget *parent = 0);
    ~Dialog_Input_New_Value();

    double get_Value() {return value;};
    QDate get_Date() {return date_input;};

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::Dialog_Input_New_Value *ui;

    double value;
    QDate date_input;
};

#endif // DIALOG_INPUT_NEW_VALUE_H
