#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QtSerialPort/QtSerialPort>
#include <QByteArray>
#include <QTimer>
#include <QVector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void connectArduino();

public slots:
    void serialRecieved();

private slots:
    void sendArduinoData(QString);

    void sendArduinoData();

    void on_inputRpm_returnPressed();

    void on_inputRpmButton_clicked();

    void on_motorEnableButton_clicked();

    void on_connectArduinoButton_clicked();

    void on_motorDisableButton_clicked();

    void on_actionError_triggered();

    void on_actionOutput_Rpm_triggered();

    void on_actionOutput_Current_triggered();

    void on_inputReciproFreqpushButton_clicked();

    void on_inputReciproFreqlineEdit_returnPressed();

    void on_actionOutput_Frequency_triggered();

    void on_actionEditVariables_triggered();

    void setVars(QList<int> int_vars_, QList<double> double_vars_);

    void processHeight(QString);

    void on_actionDefault_Values_triggered();

signals:
    void sendArduino(QString);

    void sendArduino();

    void serialRecievedProcessed();

    void serialSent();

    void arduinoConnection(bool);

    void motorEnable(bool);

    void motorOutputCW(bool);

    void motorReferenceCW(bool);

    void motorStalling(bool);

    void motorOutputRPM(QString);

    void motorReferenceRPM(QString);

    void motorReferenceReciproFreq(QString);

    void motorOutputReciproFreq(QString);

    void motorOutputCurrent(QString);

    void systemHeight(QString);

    void motorRPMError(double);

    void statusMessage(QString,int);

    void statusMessage(QString);

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;

    //--------------------------------------
    // recieving and sending to arduino
    //--------------------------------------
    QByteArray arduino_input_buffer;
    QByteArray arduino_output_buffer;
    QList<QByteArray> arduino_input_list;
    //--------------------------------------

    //--------------------------------------
    // for the recording of values
    //--------------------------------------
    int sampling_size;
    //--------------------------------------

    //--------------------------------------
    // for the height control
    //--------------------------------------
    int min_height;
    int max_height;
    //--------------------------------------

    //--------------------------------------
    // self tuning of arduino
    //--------------------------------------
    //bool self_tuning_mode;
    //QVector<int> self_tuning_args;
    //--------------------------------------

    //--------------------------------------
    // internal control
    //--------------------------------------
    QList<int> int_vars;
    QList<double> double_vars;
    //--------------------------------------
};

#endif // MAINWINDOW_H
