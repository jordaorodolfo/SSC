#ifndef CSVWRITER_H
#include <QList>
#include <QFile>
#define CSVWRITER_H

/*!
 * \brief The CsvWriter class for simple csv output.
 *
 * A basic class for writing the output as a csv file whenever
 * the user wishes to export recorded data by the software.
 */
class CsvWriter
{
public:
    //! baisc constructor
    CsvWriter(QString target);

    /*!
     * \brief takes a Qlist of double and writes it into a file
     * in ready to read csv format.
     */
    void writeNumberVector(QList<double>);

private:
    QString file;
};

#endif // CSVWRITER_H
