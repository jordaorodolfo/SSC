#include "variableeditor.h"
#include "ui_variableeditor.h"

VariableEditor::VariableEditor(QWidget *parent, int TARA) :
    QWidget(parent),
    ui(new Ui::VariableEditor)
{
    ui->setupUi(this);
    //default values
//    QWidgetItem * temp = new QWidgetItem(ui->tableWidget->item(1,1));
//    temp->setText(QString::number(TARA));
//    ui->tableWidget->setItem(1,1,temp);
    //connections
    QObject::connect(ui->pushButtonCancel,SIGNAL(clicked()),this,SLOT(deleteLater()));
}

VariableEditor::~VariableEditor()
{
    delete ui;
}

void VariableEditor::on_pushButtonSave_clicked()
{
    emit setTARA(ui->tableWidget->itemAt(1,1)->text());
    emit deleteLater();
}
