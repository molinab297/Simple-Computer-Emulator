#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
        ui->setupUi(this);

        pc                = 0;
        ac                = 0;
        accumulatorValue  = 0;
        inputIncrementer  = 1;
        outputIncrementer = 1;
        input             = 1;
        count             = 0;
        opCode            = " ";


       // Sets each line edit widget to only allow a 3 digit integer (-999 to 999) as input
        int i = 0;
        while(i < 100)
        {
            if(i < 10)
            {
                ui->centralwidget->findChild<QLineEdit *>("inputbox"
                + QString::number(i+1))->setValidator(new QIntValidator(-999, 999, this));
                ui->centralwidget->findChild<QLineEdit *>("outputbox"
                + QString::number(i+1))->setValidator(new QIntValidator(-999, 999, this));
            }
            ui->centralwidget->findChild<QLineEdit *>("cell"
            +QString::number(i))->setValidator(new QIntValidator(-999, 999, this));
            i++;
        }

        // Disables unecessary arrows on QSpinBoxes
        ui->acInput->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ui->pcInput->setButtonSymbols(QAbstractSpinBox::NoButtons);
        ui->irInput->setButtonSymbols(QAbstractSpinBox::NoButtons);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_stepButton2_clicked()
{

        if(opCode != NULL && count == 0)
        {
            MainWindow::on_stepButton_clicked();
            count ++;
        }
        else if(opCode != NULL && opCode.at(0) != '9' && input != 0)
        {
           MainWindow::on_stepButton_clicked();
        }
        else
        {
            if(opCode == NULL && input == 0)
            {
                QMessageBox msgBox;
                msgBox.setText("Execution Halted: Input card is empty.");
                msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
                msgBox.setIcon(QMessageBox::Information);
                msgBox.exec();
                input = 1; // fixes problem where both input = 0 and opcode is 900
            }
            else if(opCode == NULL)
            {
                QMessageBox msgBox;
                msgBox.setText("Execution Halted: Memory location being fetched is empty.");
                msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
                msgBox.setIcon(QMessageBox::Information);
                msgBox.exec();
            }
            else if(input == 0)
            {
                QMessageBox msgBox;
                msgBox.setText("Execution Halted: Input card is empty.");
                msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
                msgBox.setIcon(QMessageBox::Information);
                msgBox.exec();
                input = 1; // fixes problem where both input = 0 and opcode is 900
            }
            else
            {
                // Resets program counter to proper memory location i.e. 900, 920, ect.
                pc = opCode.mid(1,3).toInt();
                ui->pcInput->setValue(pc);
                // Resets all variables (Except outputIncrementer)
                ResetVariables();
                // "Program has terminated normally" message
                QMessageBox msgBox;
                msgBox.setText("Program has terminated normally.");
                msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
                msgBox.setIcon(QMessageBox::Information);
                msgBox.exec();

                qDebug() << "\nProgram has executed normally.";
                qDebug() << "Program will start at cell: " << pc;
            }
        }
}

void MainWindow::on_runButton_clicked()
{
        // LCV : OpCode must contain a value and cannot be a 900 code
        if(opCode != NULL && opCode.at(0) != '9')
        {
            MainWindow::on_stepButton_clicked();
        }

        while(opCode != NULL && input != 0 && opCode.at(0) != '9')
        {
            MainWindow::on_stepButton_clicked();
        }

        if(opCode == NULL && input == 0)
        {
            QMessageBox msgBox;
            msgBox.setText("Execution Halted: Input card is empty.");
            msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
            input = 1; // fixes problem where both input = 0 and opcode is 900
        }
        else if(opCode == NULL)
        {
            QMessageBox msgBox;
            msgBox.setText("Execution Halted: Memory location being fetched is empty.");
            msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
        }
        else if(input == 0)
        {
            QMessageBox msgBox;
            msgBox.setText("Execution Halted: Input card is empty.");
            msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
            input = 1; // fixes problem where both input = 0 and opcode is 900
        }
        else
        {
            // Resets program counter to proper memory location i.e. 900, 920, ect.
            pc = opCode.mid(1,3).toInt();
            ui->pcInput->setValue(pc);
            // Resets all variables (Except outputIncrementer)
            ResetVariables();
            // "Program has terminated normally" message
            QMessageBox msgBox;
            msgBox.setText("Program has terminated normally.");
            msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();

            qDebug() << "\nProgram has executed normally.";
            qDebug() << "Program will start at cell: " << pc;
        }
}

void MainWindow::on_stepButton_clicked()
{
    // Sets and then reads value from PC box (Tells program which cell to start execution)
    pc = ui->pcInput->value();
    qDebug() << "current Program Position:" << pc;

    // Reads OpCode Command from specified cell
    opCode      = ui->centralwidget->findChild<QLineEdit *>("cell"+QString::number(pc))->text();

    if(opCode != NULL)
    {

    qDebug() << "*** Executing task : " << opCode << "***";

        /*******************
         *** OP CODE - 0 ***
         *******************/
        if(opCode.at(0) == '0')
        {
            inputTmp = tr("%1").arg(inputIncrementer);

            // Serves as a check to make sure you can't read in past 10 inputs
            if(inputIncrementer < 11)
            {
                // Reads from input card and stores value
                input = ui->centralwidget->findChild<QLineEdit *>("inputbox"+ inputTmp)->text().toInt();

                if(input != 0)
                {
                    QString result;

                    // Seperates the '0' and '__' part of the OpCode to see where to store input card
                    memoryLocation = opCode.mid(1,3).toInt();
                    qDebug() << "storing value " << input << " at cell: " << memoryLocation;

                    // Corrects output to display leading zeros i.e. 3 ----> 003
                    result = ConstructOutput(input);
                    if(memoryLocation != 0)
                    {
                        ui->centralwidget->findChild<QLineEdit*>("cell"+ QString::number(memoryLocation))->setText(result+QString::number(input));
                    }
                    inputIncrementer++; // updates input cards
                }
                else
                {
                    input = 0;
                }
            }
            else
            {
                input = 0;
            }
        }

        /*******************
         *** OP CODE - 1 ***
         *******************/
        if(opCode.at(0) == '1')
        {
            if(outputIncrementer < 11)
            {
                value = ui->centralwidget->findChild<QLineEdit*>("cell"+ opCode.mid(1,3))->text();  // grabs value
                ui->centralwidget->findChild<QLineEdit*>("outputbox" + QString::number(outputIncrementer))->setText(value); // outputs value
                outputIncrementer++;
                qDebug() << "Outputting: " << value;
            }
            else
            {
                QMessageBox msgBox;
                msgBox.setText("You are limited to only 10 outputs.");
                msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
                msgBox.setIcon(QMessageBox::Information);
                msgBox.exec();
            }
        }

        /*******************
         *** OP CODE - 2 ***
         *******************/
        if(opCode.at(0) == '2')
        {
           int num;
           num= opCode.mid(1,3).toInt();
           value = ui->centralwidget->findChild<QLineEdit*>("cell"+ QString::number(num))->text();
           accumulatorValue = accumulatorValue+value.toInt(); // adds value to accumulator
        }
        /*******************
         *** OP CODE - 3 ***
         *******************/
        if(opCode.at(0) == '3')
        {
            int num;
            num= opCode.mid(1,3).toInt();
            value = ui->centralwidget->findChild<QLineEdit*>("cell"+ QString::number(num))->text();
            accumulatorValue = accumulatorValue-value.toInt(); // subtracts value from accumulator
        }
        /*******************
         *** OP CODE - 4 ***
         *******************/
        if(opCode.at(0) == '4')
        {
            int num;
            accumulatorValue = 0;
            // Converts string to integer before parsing to "cell" i.e.
            num = opCode.mid(1,3).toInt();
            // Copy contents of cell # into the accumulator
            accumulatorValue = ui->centralwidget->findChild<QLineEdit*>("cell"+QString::number(num))->text().toInt();
            qDebug() << "Accumulator value: " << accumulatorValue;

        }
        /*******************
         *** OP CODE - 5 ***
         *******************/
        if(opCode.at(0) == '5')
        {
            int num;
            QString result;
            // Copy value of the accumulator into cell number __
            num = opCode.mid(1,3).toInt();
            // Corrects output to display leading zeros i.e. 3 ----> 003
            result = ConstructOutput(accumulatorValue);
            ui->centralwidget->findChild<QLineEdit*>("cell"+QString::number(num))->setText(result+QString::number(accumulatorValue));
        }

        /*******************
         *** OP CODE - 8 ***
         *******************/
        if(opCode.at(0) == '8')
        {
            QString strNum;
            int num;

            // x
            strNum = opCode.at(1);
            num    = strNum.toInt();

            if(opCode.at(1) != '0' && opCode.at(2) != '0')
            {
                if(num == 1)
                   accumulatorValue = accumulatorValue * 10;
                else if(num == 2)
                    accumulatorValue = accumulatorValue * 100;
                else if(num == 3)
                    accumulatorValue = accumulatorValue * 1000;
                else if(num > 3)
                    accumulatorValue = 0;
            }
            else
            {
                if(num == 1)
                   accumulatorValue = (accumulatorValue * 10) % 1000;
                else if(num == 2)
                    accumulatorValue = (accumulatorValue * 100) % 1000;
                else if(num == 3)
                    accumulatorValue = (accumulatorValue * 1000) % 1000;
                else if(num > 3)
                    accumulatorValue = 0;
            }

            // y
            strNum = opCode.at(2);
            num    = strNum.toInt();

            if(num == 1)
               accumulatorValue = accumulatorValue / 10;
            else if(num == 2)
                accumulatorValue = accumulatorValue / 100;
            else if(num == 3)
                accumulatorValue = accumulatorValue / 1000;
            else if(num > 3)
                accumulatorValue = 0;
        }


        /*******************
        ***     LCV     ***
        *******************/
        if(opCode.at(0) == '9') // might be useless...
        {
            qDebug() << "Exit Loop";
        }
        else
        {
            if(opCode.at(0) == '6' || opCode.at(0) == '7') // case: 6__
            {
                if(opCode.at(0) == '6') // *** OP CODE - 6 ***
                {
                    ui->cell99->setText(QString::number(pc+1));
                    qDebug() << "Cell 99: " << pc;
                    // Place jump address in PC register
                    pc = opCode.mid(1,3).toInt();
                    // Update GUI to display new jump address
                    ui->pcInput->setValue(pc);

                    qDebug() << "Unconditional JUMP to " << pc;
                }
                if(opCode.at(0) == '7') // *** OP CODE - 7 ***************************************
                {
                    // If accumulator has a negative value, jump to new specified location
                    if(accumulatorValue < 0)
                    {
                        pc = opCode.mid(1,3).toInt();
                        ui->pcInput->setValue(pc);
                        qDebug() << "JUMP to " << pc;
                    }
                    // otherwise ignore, and proceed normally
                    else
                    {
                        pc++;
                        ui->pcInput->setValue(pc);
                    }
                 }

               }
            else
            {
                pc++;
                ui->pcInput->setValue(pc);
            }

            // Grab next opcode
            opCode  = ui->centralwidget->findChild<QLineEdit *>("cell"+QString::number(pc))->text();

            qDebug() << "Proceeding...";
        } // end else


        // update Instruction Register and AC Register
        ui->acInput->setValue(accumulatorValue);
        ir = opCode;
        ui->irInput->setValue(ir.toInt());

        qDebug() << "Current OpCode: " << opCode << " at cell: " << pc;
        qDebug() << "\n";

    } //end if opCode != NULL

}

QString MainWindow :: ConstructOutput(int num) const
{
    QString result;

    if(num< 10 && num >= 0)
       result = "00";
    else if(num < 100 && num > 9)
       result = "0";
    else
       result = "";
    return result;
}

void MainWindow::on_memoryClearButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Clear all memory cells?"));
    QAbstractButton* pButtonYes = msgBox.addButton(tr("Yes"), QMessageBox::YesRole);
    msgBox.addButton(tr("No"), QMessageBox::NoRole);
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.exec();

    int count = 1;
    QString tmp = NULL;

    if (msgBox.clickedButton()==pButtonYes)
    {
        // set all memory cells to 0
        while(count < 100)
        {
            ui->centralwidget->findChild<QLineEdit *>("cell"+QString::number(count))->setText("");
            count++;
        }
    }
    else
    {
        msgBox.close();
    }

}
void MainWindow::on_clearCPUButton_clicked()
{
    pc = 0;
    ir = "000";
    ac = 0;
    ui->pcInput->setValue(pc);
    ui->acInput->setValue(ac);
    ui->irInput->setValue(ir.toInt());
}

void MainWindow::on_clearInputCardsButton_clicked()
{
    int count = 1;
    while(count < 11)
    {
        ui->centralwidget->findChild<QLineEdit*>("inputbox"+QString::number(count))->setText("");
        count++;
    }
}

void MainWindow::on_clearOutputCardsButton_clicked()
{
    int count = 1;
    while(count < 11)
    {
        ui->centralwidget->findChild<QLineEdit*>("outputbox"+QString::number(count))->setText("");
        count++;
    }
}

void MainWindow::on_clearAllButton_clicked()
{
    MainWindow::on_clearCPUButton_clicked();
    MainWindow::on_clearInputCardsButton_clicked();
    MainWindow::on_clearOutputCardsButton_clicked();
    MainWindow::on_memoryClearButton_clicked();
}

void MainWindow::on_opCodesButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText("OP Code Commands:\n"
                   "\n0 _ _	 Input - Copy the current input card into cell number _ _ and advance to the next card. Halt execution if the input card is empty."
                   "\n\n1 _ _	 Output - Copy the contents of cell number _ _ to the current output card and advance to the next card."
                   "\n\n2 _ _	 Add - Add the contents of cell number _ _ to the value of the accumulator. Sets Carry Bit on overflow."
                   "\n\n3 _ _	 Subtract - Subtract the contents of cell number _ _ from the current value of the accumulator. Sets Carry Bit on overflow."
                   "\n\n4 _ _	 Load Accumulator - Clear the accumulator and carry flag, then copy the contents of cell number _ _ into the accumulator."
                   "\n\n5 _ _	 Store Accumulator - Copy the tree digits of the accumulator into cell number _ _."
                   "\n\n6 _ _	 Jump - Place the current value of the program counter into cell 99. Next, change the value of the program counter to _ _."
                   "\n\n7 _ _	 Test Accumulator - If the value of the accumulator is negative, change the value of the program counter to _ _."
                   "\n\n8 x y	 Shift - Shift the accumulator left x digits, then shift the result right y digits. Shift digits through the Carry Bit and enter zeros from the left and right appropriately."
                   "\n\n9 _ _	 Halt - Replace the value of the program counter with cell number _ _ and then halt execution.");
    msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

void MainWindow::on_helpButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setText(" -------- How to Use --------\n"
                   "\n Enter istructions you wish to write in the 'Memory' portion of the screen. "
                   "(Click OpCodes button for simple computer instruction set.) Inputs will be read in sequentially as well as outputs outputted sequentially. "
                   "(From the input/output card slots)."
                   "\n\n- Pressing the 'Save' Button will save your current progress."
                   "\n- Pressing the 'Load' Button will load your most recent saved file."
                   "\n\n* Before running your program do not forget to set the Program Counter(PC) to the desired memory cell you wish to start at.");
    msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

// writes to output file
void MainWindow::on_saveButton_clicked()
{
    int num = 0;
    QString tmp;

    QFile file("/Users/koolkirbykid/Desktop/QT Build files/build-
    SCemulator-Desktop_Qt_5_5_0_clang_64bit-Debug/file.txt");
    QTextStream stream(&file);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // saves memory cell values
        for(int i = 0; i < 100; i++)
        {
           stream << ui->centralwidget->findChild<QLineEdit*>("cell"+QString::number(i))->text() << endl;
        }

        // saves input values
        for(int i = 1; i < 11; i++)
        {
            stream << ui->centralwidget->findChild<QLineEdit*>("inputbox"+QString::number(i))->text() << endl;
        }
        // saves output values
        for(int i = 1; i < 11; i++)
        {
            stream << ui->centralwidget->findChild<QLineEdit*>("outputbox"+QString::number(i))->text() << endl;
        }

        // Saves PC, AC, and IR values
        num = ui->centralwidget->findChild<QSpinBox *>("irInput")->value();
        stream << num << endl;
        num = ui->centralwidget->findChild<QSpinBox *>("acInput")->value();
        stream << num << endl;
        num = ui->centralwidget->findChild<QSpinBox *>("pcInput")->value();
        stream << num << endl;

        stream.flush();
        file.close();
        qDebug() << "File Written";

        QMessageBox msgBox;
        msgBox.setText("File Saved!");
        msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("An error with the input file has occured.");
        msgBox.addButton(tr("Okay"), QMessageBox::YesRole);
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.exec();
    }
}

// reads from output file
void MainWindow::on_loadButton_clicked()
{
    QFile file("/Users/koolkirbykid/Desktop/QT Build files/build-SCemulator-
    Desktop_Qt_5_5_0_clang_64bit-Debug/file.txt");
    QTextStream stream(&file);
    QString line;
    int i = 0;

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // loads memory cell values
        do
        {
            line = stream.readLine();
            ui->centralwidget->findChild<QLineEdit*>("cell"+QString::number(i))->setText(line);
            i++;

        }while(i < 100);

        // loads input values
        i = 1;
        do
        {
            line = stream.readLine();
            ui->centralwidget->findChild<QLineEdit*>("inputbox"+QString::number(i))->setText(line);
            i++;

        }while(i < 11);

        // loads output values
        i = 1;
        do
        {
            line = stream.readLine();
            ui->centralwidget->findChild<QLineEdit*>("outputbox"+QString::number(i))->setText(line);
            i++;

        }while(i < 11);

        ui->centralwidget->findChild<QSpinBox *>("irInput")->setValue(stream.readLine().toInt());
        ui->centralwidget->findChild<QSpinBox *>("acInput")->setValue(stream.readLine().toInt());
        ui->centralwidget->findChild<QSpinBox *>("pcInput")->setValue(stream.readLine().toInt());

        file.close();
        qDebug() << "File Loaded";
    }
}
