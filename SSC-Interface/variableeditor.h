#ifndef VARIABLEEDITOR_H
#define VARIABLEEDITOR_H

#include <QDialog>
#include <QList>

namespace Ui {
class VariableEditor;
}

/*!
 * \brief The VariableEditor class is a simple global internal variable editor.
 *
 * The goal is that the object created changes the global variables determined into
 * the mainwindow such as sample size and height extrema.
 */
class VariableEditor : public QDialog
{
    Q_OBJECT

public:
    /*!
     * \brief VariableEditor contructor, needs a couple of parameters.
     *
     * To make the variables appear in the correct way, they are passed as lists
     * by the mainwindow object and then processed internally by this class.
     *
     * Although the numbering and rows managning is automatic, the row labels are not.
     * If more global variables are defined and need to be managed, the source code must
     * be modified accordingly, in this class and in the MainWindow class.
     *
     * \param parent The usual GUI parent. Genrally the mainwindow.
     * \param int_vars_ the input list of integer variables.
     * \param double_vars_ the input list of double/float variables.
     */
    explicit VariableEditor(QWidget *parent = 0, QList<int> int_vars_ = QList<int>(), QList<double> double_vars_ = QList<double>());
    ~VariableEditor();

private slots:
    void on_pushButtonSave_clicked();

private:
    Ui::VariableEditor *ui;
    QList<int> int_vars;
    QList<double> double_vars;

signals:

    /*!
     * \brief s_setVars signals the new variables to be set in the main window.
     *
     * The variable chaging is not entirelly general in the mainwindow class and if
     * a new global variable is created and needs to be managed, as stated in VariableEditor()
     * description;the correspondent source code of the MainWindow class also needs to be changed.
     * Although it is a straighforward change.
     */
    void s_setVars(QList<int>,QList<double>);

};

#endif // VARIABLEEDITOR_H
