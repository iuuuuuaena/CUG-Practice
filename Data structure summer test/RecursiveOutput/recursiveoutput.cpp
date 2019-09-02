#include "recursiveoutput.h"

RecursiveOutput::RecursiveOutput(int n,int k)
{
    this->n=n;
    this->k=k;
    record="";
    m=1;
}

void RecursiveOutput::calculate(){
    if (k == 0) {
        if (n == 1) {
            record=record+QString::number(n)+'\n';
        }
        else
        {
            for (int i = 0; i < n; i++) {
                record=record+QString::number(n)+'\t';
            }
            record+='\n';
            n--;
            return calculate();
        }
    }
    if (k == 1) {
        if (m == n) {
            for (int i = 0; i < n; i++) {
                record=record+QString::number(n)+'\t';
            }
            record+='\n';
        }
        else
        {
            for (int i = 0; i < m; i++) {
                record=record+QString::number(m)+'\t';
            }
            record=record+'\n';
            m++;
            return calculate();
        }

    }
}

QString RecursiveOutput::getrecord(){
    return record;
}
