#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qdebug.h>
#include <QSpinBox>
#include <QMessageBox>
#include <QEventLoop>
#include <QFile>

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
    void on_runButton_clicked();
    void on_memoryClearButton_clicked();
    void on_clearCPUButton_clicked();
    void on_clearInputCardsButton_clicked();
    void on_clearOutputCardsButton_clicked();
    void on_clearAllButton_clicked();
    void on_opCodesButton_clicked();
    void on_helpButton_clicked();
    void on_stepButton_clicked();
    void on_saveButton_clicked();
    void on_loadButton_clicked();
    void on_stepButton2_clicked();

    void ResetVariables()
    {
        opCode            = " ";
        ac                = 0;
        inputIncrementer  = 1;
        input             = 1;
        count             = 0;
    }


    QString ConstructOutput(int num) const;

private:
    Ui::MainWindow *ui;
    QString ir;
    QString tmp;
    QString tmp7;
    QString inputTmp;            // String representation of inputIncrementer
    QString outputTmp;           // String representation of outputIncrementer
    QString opCode;
    QString value;
    int memoryLocation;      // Contains memory location of where the input card is to be stored
    int pc;
    int ac;
    int accumulatorValue;
    int inputIncrementer;
    int outputIncrementer;
    int input;
    int count;

};


#endif // MAINWINDOW_H
