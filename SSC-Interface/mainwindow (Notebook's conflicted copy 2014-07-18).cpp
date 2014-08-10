#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QtSerialPort>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    QObject::connect(this,SIGNAL(motorEnable(bool)),ui->motorEnable,SLOT(setChecked(bool)));
    QObject::connect(this,SIGNAL(arduinoConnection(bool)),ui->arduinoConnected,SLOT(setChecked(bool)));
    QObject::connect(this,SIGNAL(motorReferenceCW(bool)),ui->referenceRpmCW,SLOT(setChecked(bool)));
    QObject::connect(this,SIGNAL(motorOutputCW(bool)),ui->outputRpmCW,SLOT(setChecked(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendArduinoData()
{
    sendArduinoData("");
}

void MainWindow::sendArduinoData(QString data)
{
    arduino_output_buffer = ui->inputRpm->text().toUtf8();
    arduino_output_buffer += data;
    switch(serial->isOpen())
    {
    case true:
        switch(serial->isWritable())
        {
        case true:
            serial->write(arduino_output_buffer);
            serial->flush();
            displayMessage("Data sent: "+arduino_output_buffer);
            break;
        case false:
            displayMessage("Arduino busy.");
        }
        break;
    case false:
        displayMessage("Arduino is disconnected.");
        break;
    }
    ui->inputRpm->setText("");
}

void MainWindow::on_inputRpm_returnPressed()
{
    sendArduinoData();
}

void MainWindow::connectArduino()
{
    displayMessage("Trying to connect...");
    switch(serial->isOpen())
    {
    case false:
        // assuming there is only one arduino find it
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            serial->setPort(info);
            if (serial->open(QIODevice::ReadWrite))
            {
                displayMessage("Arduino connected!");
                emit arduinoConnection(true);
                serial->setBaudRate(QSerialPort::Baud9600);
                serial->setDataBits(QSerialPort::Data8);
                serial->setParity(QSerialPort::NoParity);
                serial->setStopBits(QSerialPort::OneStop);
                serial->setFlowControl(QSerialPort::NoFlowControl);
                QObject::connect(serial,SIGNAL(readyRead()),this,SLOT(serialRecieved()));
                break;
            }
            else
            {
                serial->close();
            }
        }
        break;
    default:
        displayMessage("Arduino already connected.");
        break;
    }
}

void MainWindow::serialRecieved()
{
    switch(serial->isOpen())
    {
    case true:
        switch(serial->isReadable())
        {
        case true:
            //---------------------
            // keep buffering until linefeed
            //---------------------
            arduino_input_buffer += serial->readAll();
            switch(arduino_input_buffer.endsWith('\n'))
            {
            case true:
                //---------------------
                // parse arduino output
                //---------------------
                switch(arduino_input_buffer[0])
                {
                case '1':
                    //make list of data
                    arduino_input_list = arduino_input_buffer.split(';');
                    //motor enabled?
                    emit motorEnable(true);
                    //reference rpm
                    if(arduino_input_list[1][0] == '-')
                    {
                        emit motorOutputCW(true);
                        ui->outputRpm->setText(arduino_input_list[2].remove(0,1));
                    }
                    else
                    {
                        emit motorOutputCW(false);
                        ui->outputRpm->setText(arduino_input_list[2]);
                    }
                    //what is the output RPM?
                    if(arduino_input_list[2][0] == '-')
                    {
                        emit motorOutputCW(true);
                        ui->outputRpm->setText(arduino_input_list[2].remove(0,1));
                    }
                    else
                    {
                        emit motorOutputCW(false);
                        ui->outputRpm->setText(arduino_input_list[2]);
                    }
                    break;
                case '0':
                    emit motorEnable(false);
                    ui->referenceRpm->setText("");
                    ui->outputRpm->setText("");
                    break;
                }
                //---------------------
                arduino_input_buffer.clear();
                serial->flush();
                emit serialRecievedProcessed();
                break;
            case false:
                break;
            }
            break;
            //---------------------
        }
        break;
    }
}

void MainWindow::on_actionConnect_triggered()
{
    connectArduino();
}

void MainWindow::on_inputRpmButton_clicked()
{
    sendArduinoData();
}

void MainWindow::on_motorEnableButton_clicked()
{
    sendArduinoData("E");
}

void MainWindow::on_connectArduinoButton_clicked()
{
    connectArduino();
}

void MainWindow::displayMessage(QString message, int time)
{
    ui->statusBar->showMessage(message,time);
}

void MainWindow::displayMessage(QString message)
{
    ui->statusBar->showMessage(message,1000);
}

void MainWindow::on_motorDisableButton_clicked()
{
    sendArduinoData("D");
}
