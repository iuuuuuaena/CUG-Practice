#ifndef CAL_H
#define CAL_H
#include "Linkedstack.h"
#include <QString>
#include <QtMath>
#include <QMessageBox>
#include <QByteArray>
#include <QDebug>

class cal
{
private:
    QString exp;
    LinkedStack<double> num_Stack;
    LinkedStack<char> op_Stack;

public:
    cal(QString expIn);
    double calOp(double num1,char op,double num2);
    double calFun(char fun,double num);
    bool calculate(double &res);
    int compare(char op1,char op2);
    bool isOp(char op);
    bool isFun(char fun);
};


#endif // CAL_H
