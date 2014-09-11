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

/*!
 * \brief The MainWindow class.
 * Actually is the heart of the interface. All the methods which deal with the arduino itself
 * are coded in the source code of this class.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! default cosntructor
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /*!
     * \brief the funtion wich tries to connect to and arduino.
     *
     * This function tries to be as cross-platform possible, by iterating in the
     * lsit given by the QtSerial library and attempting connection with the first
     * possibility it finds. There is a draw back to this approach: The assumption that
     * only on arduino is connected to the machine.
     *
     * By calling the function the internal variable serial is manipulated in this respect.
     */
    void connectArduino();

public slots:
    /*!
     * \brief fucntion that is executed everytime a serial message is recieved.
     *
     * This function processes all the serial data recieved by the Arduino. Since it does
     * not behave like the arduino processing does, being faster in this respect; a internal
     * buffer is necessary to gather all the data until a linefeed is issued. If this happens,
     * the buffer is taken and processed according to the minimal standard adopted in the arduino:
     *
     * Enabled; Stalling; reference RPM; output RPM; output Height;
     */
    void serialRecieved();

    /*!
     * \brief send data to arduino via serial bus.
     *
     * Takes the string given in the slot and sends it in the
     * correct form to the arduino via serial bus. The string can
     * be any command that the arduino recognizes (invalid commands
     * and chars are ignored by the arduino internal parser).
     *
     * If the serial is still being processes; the string is appended
     * to the end of the outgoing stream.
     */
    void sendArduinoData(QString);

    /*!
     * \brief similar to sendArduinoData(QString), but sends a null string
     * and act the stream.
     */
    void sendArduinoData();

private slots:

    void on_inputRpm_returnPressed();

    void on_inputRpmButton_clicked();

    void on_motorEnableButton_clicked();

    void on_connectArduinoButton_clicked();

    void on_motorDisableButton_clicked();

    void on_actionOutput_Rpm_triggered();

    void on_inputReciproFreqpushButton_clicked();

    void on_inputReciproFreqlineEdit_returnPressed();

    void on_actionOutput_Frequency_triggered();

    void on_actionEditVariables_triggered();

    void setVars(QList<int> int_vars_, QList<double> double_vars_);

    void processHeight(QString);

    void on_actionDefault_Values_triggered();

signals:
    /*!
     * \brief send Arduino string.
     *
     * The signal to send Arduino any commands and numbers
     * within the string. If the arduino is not connect, however,
     * a message is printed into the status bar telling that the
     * arduino is not connected and no action takes place.
     */
    void sendArduino(QString);

    /*!
     * \brief equivalent to the string counterpart.
     *
     * @see sendArduino(QString);
     */
    void sendArduino();

    //! signal that indicates that the incoming serial stream has been processed.
    void serialRecievedProcessed();

    //! signal that indicates that the outgoung serial stream has been processed.
    void serialSent();

    //! signals that the arduino is connected or not. mainly for GUI purposes.
    void arduinoConnection(bool);

    //! signals that motor is enabled or not.
    void motorEnable(bool);

    //! signals that the motor is turning CW or CCW. mainly for GUI purposes.
    void motorOutputCW(bool);

    //! same idea as motorOutputCW. @see motorOutputCW(bool)
    void motorReferenceCW(bool);

    //! signals if the motor is in intermittent operation. mainly for GUI purposes.
    void motorStalling(bool);

    //! used to show a GUI representation of the arduino output RPM.
    void motorOutputRPM(QString);

    //! used to show a GUI representation of the arduino reference RPM.
    void motorReferenceRPM(QString);

    //! simple conversions to frequency. mainly for GUI purposes. @see motorReferenceRPM(Qstring)
    void motorReferenceReciproFreq(QString);

    //! same idea as motorReferenceReciproFreq(QString). @see motorOutputRPM(QString)
    void motorOutputReciproFreq(QString);

    //! signals the system height given by the arduino serial stream.
    void systemHeight(QString);

    //! signal used to show a message into the main windows status bar, with a timer.
    void statusMessage(QString,int);

    //! same as statusMessage(QString,int), without timer.
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
