#ifndef VARIABLEEDITOR_H
#define VARIABLEEDITOR_H

#include <QDialog>
#include <QList>

namespace Ui {
class VariableEditor;
}

class VariableEditor : public QDialog
{
    Q_OBJECT

public:
    explicit VariableEditor(QWidget *parent = 0, QList<int> int_vars_ = QList<int>(), QList<double> double_vars_ = QList<double>());
    ~VariableEditor();

private slots:
    void on_pushButtonSave_clicked();

private:
    Ui::VariableEditor *ui;
    QList<int> int_vars;
    QList<double> double_vars;

signals:

    void s_setVars(QList<int>,QList<double>);

};

#endif // VARIABLEEDITOR_H
