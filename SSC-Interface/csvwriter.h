#ifndef CSVWRITER_H
#include <QList>
#include <QFile>
#define CSVWRITER_H

class CsvWriter
{
public:
    CsvWriter(QString target);
    void writeNumberVector(QList<double>);

private:
    QString file;
};

#endif // CSVWRITER_H
