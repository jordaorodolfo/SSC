#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>
#include <QList>

namespace Ui {
class progressDialog;
}

/*!
 * \brief The progressDialog class is a simple progress bar for value recording.
 *
 * This class manages both the gui representing the value recording and
 * the recording itself, by storing the samples internally. The sample size
 * is given in the class construction.
 *
 * The recording itself happens via slots from the mainwindow to one instance
 * of this class.
 */
class progressDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief progressDialog constructor.
     *
     * The constructor must recieve the sample size which it will record so
     * that the sample size can be tracked and managed internally. The name of
     * the title should also be given for aesthetics.
     *
     * \param parent generally the main window.
     * \param dim_ the samplign size that the object will manage.
     * \param tracked the actual title of the GUI.
     */
    explicit progressDialog(QWidget *parent = 0, int dim_ = 50, QString tracked = "");
    ~progressDialog();

private slots:

    void on_progressDialog_finished(int result);

public slots:

    /*!
     * \brief tkae a double value and add it to the stack.
     *
     * take the double given in the signal and add it to the
     * internal sampel stack, managing the GUI and internal variables
     * automatically. When the stack reaches the desired sample size,
     * a finished signal is emited and a prompt for save is given.
     */
    void recordValue(double);

    /*!
     * \brief recordValue placeholder.
     *
     * This signal is a placeholder for the recordValue signal, which
     * tries to convert the string to double format and the calls the
     * correct recordValue(double).
     */
    void recordValue(QString);
    void saveValues();

private:
    Ui::progressDialog *ui;
    int dim;
    QList<double> value_memory;

signals:

    /*!
     * \brief simple GUI fucntion.
     *
     * This takes an int and represent it accordingly into the progress
     * bar, making it show another percentage.
     */
    void setProgress(int);

};

#endif // PROGRESSDIALOG_H
