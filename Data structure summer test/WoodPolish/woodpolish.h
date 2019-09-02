#ifndef WOODPOLISH_H
#define WOODPOLISH_H
#include<QString>
#include <QtAlgorithms>

struct wood
{
    int wei;
    int l;
};


class WoodPolish
{
public:
    WoodPolish(int n,wood w[]);
    void calculate();
    QString getrecord();
    static bool cmp(wood a,wood b);
private:
    int n;
    wood *w;
    QString record;
    int time;
};

#endif // WOODPOLISH_H
