#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_pushButton_clicked();

    void on_pushButtonElectricity_clicked();

    void on_pushButtonWater_clicked();

    void on_pushButtonGas_clicked();

    void on_pushButtonRubbish_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
