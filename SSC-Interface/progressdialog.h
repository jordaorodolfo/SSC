#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>
#include <QList>

namespace Ui {
class progressDialog;
}

class progressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit progressDialog(QWidget *parent = 0, int dim_ = 50, QString tracked = "");
    ~progressDialog();

private slots:

    void on_progressDialog_finished(int result);

public slots:
    void recordValue(double);
    void recordValue(QString);

private:
    Ui::progressDialog *ui;
    int dim;
    QList<double> value_memory;

signals:
    void setProgress(int);

};

#endif // PROGRESSDIALOG_H
