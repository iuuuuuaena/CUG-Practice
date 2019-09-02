#include "cal.h"

cal::cal(QString expIn)
{
    this->exp=expIn;
}

double cal::calOp(double num1, char op, double num2)
{
    if(op=='+'){return num1+num2;}
    else if(op=='-'){return num1-num2;}
    else if(op=='*'){return num1*num2;}
    else if(op=='/'){
        if(num2==0){
            QMessageBox::critical(NULL,"error","The divisor can not be 0.","OK");
        }
        return num1/num2;}
    else if(op=='%'){return (int)num1%(int)num2;}
    else if(op=='^'){return qPow(num1,num2);}
    else return 0;
}
double cal::calFun(char fun, double num)
{
    if(fun=='~')return -num;
    else if(fun=='s')return qSin(num);
    else if(fun=='c')return qCos(num);
    else if(fun=='t')return qTan(num);
    else if(fun=='S')return qSqrt(num);
    else if(fun=='l')return qLn(num);
    else if(fun=='L') return (qLn(num)/qLn(10));
    else return 0;
}

bool cal::isOp(char op){
    if(op=='+'||(op=='-')||op=='*'||op=='/'||op=='%'||op=='^'){
        return true;
    }
    else {
        return false;
    }
}
bool cal::isFun(char fun){
    if(fun=='s'||fun=='c'||fun=='t'||fun=='L'||fun=='S'||fun=='l'||fun=='~'){
        return true;
    }
    else {
        return false;
    }
}
int cal::compare(char op1, char op2)
{
    int i_op1;
    int i_op2;
    if(op1=='('){i_op1=0;}
    if(op2=='('){i_op2=0;}
    if(op1=='+'||op1=='-'){i_op1=1;}
    if(op2=='+'||op2=='-'){i_op2=1;}
    if(op1=='*'||op1=='/'||op1=='%'){i_op1=2;}
    if(op2=='*'||op2=='/'||op2=='%'){i_op2=2;}
    if(op1=='^'){i_op1=4;}
    if(op2=='^'){i_op2=4;}
    if(op1=='s'||op1=='c'||op1=='t'||op1=='S'||op1=='l'||op1=='L'){i_op1=3;}
    if(op2=='s'||op2=='c'||op2=='t'||op2=='S'||op2=='l'||op2=='L'){i_op2=3;}
    if(op1=='~'){i_op1=5;}
    if(op2=='~'){i_op2=5;}
    //qDebug()<<i_op1<<'\t'<<i_op2;
    if(i_op1==i_op2){return 0;}
    else if(i_op1<i_op2){return -1;}
    else if(i_op1>i_op2){return 1;}
}
bool cal::calculate(double &res)
{
    QByteArray exp_Qb=exp.toLocal8Bit();
    int i=0;
    while(i<exp_Qb.length()){
        //qDebug()<<"";
        if(isdigit(exp_Qb[i])||exp_Qb[i]=='.')
        {
            //qDebug()<<"if--------1";
            QByteArray num_temp;
            num_temp.push_back(exp_Qb[i]);
            i++;
            while (isdigit(exp_Qb[i])||exp_Qb[i]=='.') {
               num_temp.push_back(exp_Qb[i]);
                i++;
            }
            QString num_str=QString::fromLocal8Bit(num_temp);
            num_Stack.Push(num_str.toDouble());
        }
        else if(op_Stack.IsEmpty())
        {
            //qDebug()<<"if--------2";
            if(exp_Qb[i]=='+'||(exp_Qb[i]=='-'&&(!num_Stack.IsEmpty()))||exp_Qb[i]=='*'||exp_Qb[i]=='/'||exp_Qb[i]=='%'||exp_Qb[i]=='^'||exp_Qb[i]=='(')
            {
                op_Stack.Push(exp_Qb[i]);
                i=i+1;
            }
            else if(exp_Qb[i]=='-'&&(num_Stack.IsEmpty())){
                op_Stack.Push('~');
                i++;
            }
            else if(exp_Qb[i]=='s'||exp_Qb[i]=='c'||exp_Qb[i]=='t'||exp_Qb[i]=='L'){
                op_Stack.Push(exp_Qb[i]);
                i=i+3;
            }
            else if(exp_Qb[i]=='S'){
                op_Stack.Push('S');
                i=i+4;
            }
            else if(exp_Qb[i]=='l'){
                op_Stack.Push('l');
                i=i+2;
            }
            else i++;
        }
        else if(exp_Qb[i]=='(')
        {
            //qDebug()<<"if--------3";
            op_Stack.Push('(');
            i=i+1;
        }
        else if(exp_Qb[i]==')')
        {
            //qDebug()<<"if--------9";
            while (op_Stack.Top()!='(') {
                char op=op_Stack.Top();op_Stack.Pop();
                if(isOp(op)){
                    double a=num_Stack.Top();num_Stack.Pop();
                    double b=num_Stack.Top();num_Stack.Pop();
                    num_Stack.Push(calOp(b,op,a));
                }
                if(isFun(op)){
                    double a=num_Stack.Top();num_Stack.Pop();
                    num_Stack.Push(calFun(op,a));
                }
            }
            if(op_Stack.Top()=='('){
                op_Stack.Pop();
                i++;
            }
        }
        else if(exp_Qb[i]=='+'||(exp_Qb[i]=='-'&&isdigit(exp_Qb[i-1]))||exp_Qb[i]=='*'||exp_Qb[i]=='/'||exp_Qb[i]=='%'||exp_Qb[i]=='^')
        {
            //qDebug()<<"if--------------------------------------4";
            int com=compare(op_Stack.Top(),exp_Qb[i]);
            if(com==1||com==0){
                char op=op_Stack.Top();op_Stack.Pop();
                if(isOp(op)){
                    double a=num_Stack.Top();num_Stack.Pop();
                    double b=num_Stack.Top();num_Stack.Pop();
                    num_Stack.Push(calOp(b,op,a));
                }
                if(isFun(op)){
                    double a=num_Stack.Top();num_Stack.Pop();
                    num_Stack.Push(calFun(op,a));
                }
                op_Stack.Push(exp_Qb[i]);
                i++;
            }
            if(com==-1){
                op_Stack.Push(exp_Qb[i]);
                i++;
            }
        }
        else if (exp_Qb[i]=='-'&&(!isdigit(exp_Qb[i-1])))
        {
            //qDebug()<<"if--------5";
            op_Stack.Push('~');
            i++;
        }
        else if (exp_Qb[i]=='s'||exp_Qb[i]=='c'||exp_Qb[i]=='t'||exp_Qb[i]=='L')
        {
            //qDebug()<<"if--------6";
            int com=compare(op_Stack.Top(),exp_Qb[i]);
            if(com==1||com==0){
                char op=op_Stack.Top();op_Stack.Pop();
                if(isOp(op)){
                    double a=num_Stack.Top();num_Stack.Pop();
                    double b=num_Stack.Top();num_Stack.Pop();
                    num_Stack.Push(calOp(b,op,a));
                }
                if(isFun(op)){
                    double a=num_Stack.Top();num_Stack.Pop();
                    num_Stack.Push(calFun(op,a));
                }
                op_Stack.Push(exp_Qb[i]);
                i=i+3;
            }
            if(com==-1){
                op_Stack.Push(exp_Qb[i]);
                i=i+3;
            }
        }
        else if (exp_Qb[i]=='S')
        {
            //qDebug()<<"if--------7";
            int com=compare(op_Stack.Top(),exp_Qb[i]);
            if(com==1||com==0){
                char op=op_Stack.Top();op_Stack.Pop();
                if(isOp(op)){
                    double a=num_Stack.Top();num_Stack.Pop();
                    double b=num_Stack.Top();num_Stack.Pop();
                    num_Stack.Push(calOp(b,op,a));
                }
                if(isFun(op)){
                    double a=num_Stack.Top();num_Stack.Pop();
                    num_Stack.Push(calFun(op,a));
                }
                op_Stack.Push(exp_Qb[i]);
                i=i+4;
            }
            if(com==-1){
                op_Stack.Push(exp_Qb[i]);
                i=i+4;
            }
        }
        else if (exp_Qb[i]=='l')
        {
            //qDebug()<<"if--------8";
            int com=compare(op_Stack.Top(),exp_Qb[i]);
            if(com==1||com==0){
                char op=op_Stack.Top();op_Stack.Pop();
                if(isOp(op)){
                    double a=num_Stack.Top();num_Stack.Pop();
                    double b=num_Stack.Top();num_Stack.Pop();
                    num_Stack.Push(calOp(b,op,a));
                }
                if(isFun(op)){
                    double a=num_Stack.Top();num_Stack.Pop();
                    num_Stack.Push(calFun(op,a));
                }
                op_Stack.Push(exp_Qb[i]);
                i=i+2;
            }
            if(com==-1){
                op_Stack.Push(exp_Qb[i]);
                i=i+2;
            }
        }
        else
        {
            //QMessageBox::critical(NULL,"error","input error!","OK");
            return false;
        }
    }
    while (!op_Stack.IsEmpty()) {
        char op=op_Stack.Top();op_Stack.Pop();
        if(isOp(op)){
            double a=num_Stack.Top();num_Stack.Pop();
            double b=num_Stack.Top();num_Stack.Pop();
            num_Stack.Push(calOp(b,op,a));
        }
        if(isFun(op)){
            double a=num_Stack.Top();num_Stack.Pop();
            num_Stack.Push(calFun(op,a));
        }
    }
    res=num_Stack.Top();
    return true;
}
