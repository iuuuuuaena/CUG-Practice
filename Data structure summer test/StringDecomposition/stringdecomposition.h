#ifndef STRINGDECOMPOSITION_H
#define STRINGDECOMPOSITION_H

#include <string>
#include <QDebug>

class StringDecomposition
{
public:
    StringDecomposition(char in[]);
    ~StringDecomposition();
    void calculate();
    int *get();
    int getlength();



private:
    int *out;
    char *in;
    int length;
    int length_out;
};

#endif // STRINGDECOMPOSITION_H
