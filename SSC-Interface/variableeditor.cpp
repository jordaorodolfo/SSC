#include "variableeditor.h"
#include "ui_variableeditor.h"

VariableEditor::VariableEditor(QWidget *parent, QList<int> int_vars_, QList <double> double_vars_) :
    QDialog(parent),
    ui(new Ui::VariableEditor)
{
    ui->setupUi(this);
    int_vars = int_vars_;
    double_vars = double_vars_;
    ui->tableWidget->setRowCount(int_vars.length()+double_vars.length());
    for(int i=0; i<int_vars.length();i++)
    {
        QTableWidgetItem * item = new QTableWidgetItem(QString::number(int_vars[i]),0);
        ui->tableWidget->setItem(i,0,item);
    }
    for(int i=0; i<double_vars.length();i++)
    {
        QTableWidgetItem * item = new QTableWidgetItem(QString::number(double_vars[i]),0);
        ui->tableWidget->setItem(i+int_vars.length(),0,item);
    }
    ui->tableWidget->setVerticalHeaderItem(0,new QTableWidgetItem("Sampling size"));
    ui->tableWidget->setVerticalHeaderItem(1,new QTableWidgetItem("Min height"));
    ui->tableWidget->setVerticalHeaderItem(2,new QTableWidgetItem("Max height"));
    QObject::connect(ui->pushButtonCancel,SIGNAL(clicked()),this,SLOT(deleteLater()));
}

VariableEditor::~VariableEditor()
{
    delete ui;
}

void VariableEditor::on_pushButtonSave_clicked()
{
    for(int i=0;i<int_vars.length();i++)
        int_vars[i] = ui->tableWidget->item(i,0)->text().toInt();
    for(int i=0;i<double_vars.length();i++)
        double_vars[i] = ui->tableWidget->item(i+int_vars.length(),0)->text().toDouble();
    emit s_setVars(int_vars,double_vars);
    emit deleteLater();
}
