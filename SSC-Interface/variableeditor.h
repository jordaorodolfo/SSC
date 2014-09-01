#ifndef VARIABLEEDITOR_H
#define VARIABLEEDITOR_H

#include <QWidget>

namespace Ui {
class VariableEditor;
}

class VariableEditor : public QWidget
{
    Q_OBJECT

public:
    explicit VariableEditor(QWidget *parent = 0, int TARA = 0);
    ~VariableEditor();

private slots:
    void on_pushButtonSave_clicked();

private:
    Ui::VariableEditor *ui;

signals:

    void setTARA(QString);
};

#endif // VARIABLEEDITOR_H
