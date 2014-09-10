#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "progressdialog.h"
#include "variableeditor.h"
#include <QtSerialPort/QtSerialPort>
#include <QTimer>
#include <QVector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sampling_size = 50;
    min_height = 0;
    max_height = 100;
    int_vars.append(sampling_size);
    double_vars.append(min_height);
    double_vars.append(max_height);
    serial = new QSerialPort(this);
    QObject::connect(this,SIGNAL(sendArduino(QString)),this,SLOT(sendArduinoData(QString)));
    QObject::connect(this,SIGNAL(sendArduino()),this,SLOT(sendArduinoData()));
    QObject::connect(this,SIGNAL(statusMessage(QString,int)),ui->statusBar,SLOT(showMessage(QString,int)));
    QObject::connect(this,SIGNAL(statusMessage(QString)),ui->statusBar,SLOT(showMessage(QString)));
    QObject::connect(this,SIGNAL(motorEnable(bool)),ui->motorEnable,SLOT(setChecked(bool)));
    QObject::connect(this,SIGNAL(arduinoConnection(bool)),ui->arduinoConnected,SLOT(setChecked(bool)));
    QObject::connect(this,SIGNAL(motorReferenceCW(bool)),ui->referenceRpmCW,SLOT(setChecked(bool)));
    QObject::connect(this,SIGNAL(motorReferenceCW(bool)),ui->refCWReciproFreqcheckBox,SLOT(setChecked(bool)));
    QObject::connect(this,SIGNAL(motorOutputCW(bool)),ui->outputRpmCW,SLOT(setChecked(bool)));
    QObject::connect(this,SIGNAL(motorOutputCW(bool)),ui->outputCWReciproFreqcheckBox,SLOT(setChecked(bool)));
    QObject::connect(this,SIGNAL(motorStalling(bool)),ui->motorStallingCheckBox,SLOT(setChecked(bool)));
    QObject::connect(this,SIGNAL(motorOutputRPM(QString)),ui->outputRpm,SLOT(setText(QString)));
    QObject::connect(this,SIGNAL(motorReferenceReciproFreq(QString)),ui->refReciproFreqlineEdit,SLOT(setText(QString)));
    QObject::connect(this,SIGNAL(motorReferenceRPM(QString)),ui->referenceRpm,SLOT(setText(QString)));
    QObject::connect(this,SIGNAL(motorOutputReciproFreq(QString)),ui->outputReciproFreqlineEdit,SLOT(setText(QString)));
    QObject::connect(this,SIGNAL(systemHeight(QString)),this,SLOT(processHeight(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendArduinoData()
{
    emit sendArduino("");
}

void MainWindow::sendArduinoData(QString data)
{
    arduino_output_buffer = data.toUtf8();
    switch(serial->isOpen())
    {
    case true:
        switch(serial->isWritable())
        {
        case true:
            serial->write(arduino_output_buffer);
            serial->flush();
            emit statusMessage("Data sent: "+arduino_output_buffer);
            break;
        case false:
            emit statusMessage("Arduino busy.");
        }
        break;
    case false:
        emit statusMessage("Arduino is disconnected.");
        break;
    }
}

void MainWindow::on_inputRpm_returnPressed()
{
    on_inputRpmButton_clicked();
}

void MainWindow::connectArduino()
{
    emit statusMessage("Trying to connect...");
    switch(serial->isOpen())
    {
    case false:
        // assuming there is only one arduino find it
        foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
        {
            serial->setPort(info);
            if (serial->open(QIODevice::ReadWrite))
            {
                emit statusMessage("Arduino connected!");
                emit arduinoConnection(true);
                serial->setBaudRate(QSerialPort::Baud9600);
                serial->setDataBits(QSerialPort::Data8);
                serial->setParity(QSerialPort::NoParity);
                serial->setStopBits(QSerialPort::OneStop);
                serial->setFlowControl(QSerialPort::NoFlowControl);
                QObject::connect(serial,SIGNAL(readyRead()),this,SLOT(serialRecieved()));
                return;
                break;
            }
            else
            {
                serial->close();
            }
        }
        emit statusMessage("Didn't find an arduino.");
        break;
    default:
        emit statusMessage("Arduino already connected.");
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
                    //motor stalling?
                    if(arduino_input_list[1][0] == '1')
                    {
                        emit motorStalling(true);
                    }
                    else
                    {
                        emit motorStalling(false);
                    }
                    //what the reference RPM?
                    if(arduino_input_list[2][0] == '-')
                    {
                        emit motorReferenceCW(true);
                        emit motorReferenceRPM(arduino_input_list[2].remove(0,1));
                        emit motorReferenceReciproFreq(QString::number(arduino_input_list[2].remove(0,1).toDouble()/60));
                    }
                    else
                    {
                        emit motorReferenceCW(false);
                        emit motorReferenceRPM(arduino_input_list[2]);
                        emit motorReferenceReciproFreq(QString::number(arduino_input_list[2].toDouble()/60));
                    }
                    //what is the output RPM?
                    if(arduino_input_list[3][0] == '-')
                    {
                        emit motorOutputCW(true);
                        emit motorOutputRPM(arduino_input_list[3].remove(0,1));
                        emit motorOutputReciproFreq(QString::number(arduino_input_list[3].remove(0,1).toDouble()/60));
                    }
                    else
                    {
                        emit motorOutputCW(false);
                        emit motorOutputRPM(arduino_input_list[3]);
                        emit motorOutputReciproFreq(QString::number(arduino_input_list[3].toDouble()/60));
                    }
                    //what is the current?
                    emit motorOutputCurrent(arduino_input_list[4]);
                    //what is the error?
                    emit motorRPMError(qAbs(arduino_input_list[3].toDouble()-arduino_input_list[2].toDouble()));
                    //what is the height?
                    emit systemHeight(arduino_input_list[5]);
                    break;
                case '0':
                    emit motorEnable(false);
                    emit motorOutputRPM("");
                    emit motorReferenceRPM("");
                    emit motorOutputCurrent("");
                    emit motorOutputReciproFreq("");
                    emit motorReferenceReciproFreq("");
                    emit motorOutputCW(false);
                    emit motorReferenceCW(false);
                    emit motorStalling(false);
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

void MainWindow::on_inputRpmButton_clicked()
{
    emit sendArduino(ui->inputRpm->text());
    ui->inputRpm->setText("");
}

void MainWindow::on_motorEnableButton_clicked()
{
    emit sendArduino("E");
}

void MainWindow::on_connectArduinoButton_clicked()
{
    connectArduino();
}

void MainWindow::on_motorDisableButton_clicked()
{
    emit sendArduino("D");
}

void MainWindow::on_actionError_triggered()
{
    progressDialog * errorRecord = new progressDialog(this,sampling_size,"Error record");
    QObject::connect(this,SIGNAL(motorRPMError(double)),errorRecord,SLOT(recordValue(double)));
    errorRecord->show();
}

void MainWindow::on_actionOutput_Rpm_triggered()
{
    progressDialog * rpmRecord = new progressDialog(this,sampling_size,"Rpm record");
    QObject::connect(this,SIGNAL(motorOutputRPM(QString)),rpmRecord,SLOT(recordValue(QString)));
    rpmRecord->show();
}

void MainWindow::on_actionOutput_Current_triggered()
{
    progressDialog * currentRecord = new progressDialog(this,sampling_size,"Current record");
    QObject::connect(this,SIGNAL(motorOutputCurrent(QString)),currentRecord,SLOT(recordValue(QString)));
    currentRecord->show();
}

void MainWindow::on_inputReciproFreqpushButton_clicked()
{
    emit sendArduino(QString::number(int(ui->inputReciproFreqlineEdit->text().toDouble()*60)));
    ui->inputReciproFreqlineEdit->setText("");
}

void MainWindow::on_inputReciproFreqlineEdit_returnPressed()
{
    on_inputReciproFreqpushButton_clicked();
}

void MainWindow::on_actionOutput_Frequency_triggered()
{
    progressDialog * freqRecord = new progressDialog(this,sampling_size,"Frequency record");
    QObject::connect(this,SIGNAL(motorOutputReciproFreq(QString)),freqRecord,SLOT(recordValue(QString)));
    freqRecord->show();
}

void MainWindow::on_actionEditVariables_triggered()
{
    VariableEditor * var_edit = new VariableEditor(this,int_vars,double_vars);
    QObject::connect(var_edit,SIGNAL(s_setVars(QList<int>,QList<double>)),this,SLOT(setVars(QList<int>,QList<double>)));
    var_edit->show();
}

void MainWindow::setVars(QList<int> int_vars_, QList<double> double_vars_)
{
    sampling_size = int_vars[0];
    min_height = double_vars[0];
    max_height = double_vars[1];
    int_vars = int_vars_;
    double_vars = double_vars_;
}

void MainWindow::processHeight(QString value)
{
    ui->lineEditHeight->setText(QString::number((max_height - min_height)*value.toDouble()/100 + min_height));
}

void MainWindow::on_actionDefault_Values_triggered()
{
    sampling_size = 50;
    min_height = 0;
    max_height = 100;
    int_vars[0] = sampling_size;
    double_vars[0] = min_height;
    double_vars[1] = max_height;
}
