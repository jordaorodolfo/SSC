#include "csvwriter.h"
#include <QFile>
#include <QList>
#include <QTextStream>
#include <QString>

CsvWriter::CsvWriter(QString target)
{
    if(target.contains("."))
        file = target;
    else
        file = target+".csv";
}

void CsvWriter::writeNumberVector(QList<double> vector)
{
    QFile archive(file);
    archive.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream archive_stream(&archive);
    for(int i=0;i<vector.length()-1;i++)
    {
        archive_stream << vector[i] << '\n';
    }
    archive_stream << vector.last();
}
