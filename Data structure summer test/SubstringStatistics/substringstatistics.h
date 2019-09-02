#ifndef SUBSTRINGSTATISTICS_H
#define SUBSTRINGSTATISTICS_H
#include<QString>

class SubstringStatistics
{
public:
    SubstringStatistics(QString str1,QString str2);
    void calculate();
    int getcount();
    ~SubstringStatistics();

private:
    QString str1;
    QString str2;
    int count;
    int len1;
    int len2;
};

#endif // SUBSTRINGSTATISTICS_H
