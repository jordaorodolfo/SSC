#include "progressdialog.h"
#include "ui_progressdialog.h"
#include "csvwriter.h"
#include <QFileDialog>
#include <QMessageBox>

progressDialog::progressDialog(QWidget *parent, int dim_, QString tracked) :
    QDialog(parent),
    ui(new Ui::progressDialog)
{
    ui->setupUi(this);
    dim = dim_;
    setWindowTitle(tracked+" Progress");
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(dim);
    ui->progressBar->setValue(0);
    ui->sample_size_label->setText("sample size: "+QString::number(dim));
    QObject::connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(deleteLater()));
    QObject::connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(saveValues()));
    QObject::connect(this,SIGNAL(setProgress(int)),ui->progressBar,SLOT(setValue(int)));
}

progressDialog::~progressDialog()
{
    delete ui;
}

void progressDialog::recordValue(double value)
{
    if(value_memory.length() < dim)
        value_memory.append(value);
    else
        emit finished(1);
    emit setProgress(value_memory.length());
}

void progressDialog::recordValue(QString value)
{
    recordValue(value.toDouble());
}

void progressDialog::saveValues()
{
    emit finished(1);
}

void progressDialog::on_progressDialog_finished(int result)
{
    switch(result)
    {
    case 1:
        QString fileName = QFileDialog::getSaveFileName(this,
             tr("Set File"), QDir::currentPath(), tr("Data Files (*.csv *.txt)"));
        CsvWriter * writer = new CsvWriter(fileName);
        writer->writeNumberVector(value_memory);
        emit deleteLater();
        break;
    }
}
