#ifndef RECURSIVEOUTPUT_H
#define RECURSIVEOUTPUT_H
#include<QString>

class RecursiveOutput
{
public:
    RecursiveOutput(int n,int k);
    void calculate();
    QString getrecord();

private:
    QString record;
    int n;
    int k;
    int m;

};

#endif // RECURSIVEOUTPUT_H
