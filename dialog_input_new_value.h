#ifndef DIALOG_INPUT_NEW_VALUE_H
#define DIALOG_INPUT_NEW_VALUE_H

#include <QDialog>
#include <QDate>

namespace Ui
{
class Dialog_Input_New_Value;
}

class QLineEdit;

class Dialog_Input_New_Value : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Input_New_Value(const QDate& last_Month_Year_Payment,std::list<QString> name_counters, QWidget *parent = 0);
    ~Dialog_Input_New_Value();

    std::vector<double>& get_Value()
    {
        return values;
    };
    QDate get_Date()
    {
        return date_input;
    };

private slots:
    void on_pushButton_OK_clicked();

    void on_pushButton_Cancel_clicked();

private:
    Ui::Dialog_Input_New_Value *ui;

    std::vector<double> values;
    std::vector<QLineEdit*> m_QLineEdits;
    QDate date_input;
};

#endif // DIALOG_INPUT_NEW_VALUE_H
