#ifndef CHANGEPROBLEM_H
#define CHANGEPROBLEM_H
#include<QDebug>

class ChangeProblem
{
public:
    ChangeProblem(int n,int *t,int *coins,int m);
    ~ChangeProblem();
    void calculate();
    int getcount();
    int mini(int a, int b);
private:
    int n;//n种不同硬币
    int *t;//硬币面值
    int *coins;//各种硬币个数
    int m;//要找的钱
    int count;//最小个数
};

#endif // CHANGEPROBLEM_H
