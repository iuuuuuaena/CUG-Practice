// 点到折线的距离.cpp : Defines the entry point for the console application.
/*计算点到折线的距离。
点到折线的距离定义为点到折线中每一条线段的距离中的最短距离，而点到线段的距离可
能是点到线段某个端点的距离（当垂足不在线段内部），也可能是点到垂足的距离（当垂足在线段
内部）。要求定义点类CPoint 和折线类CLine，并在折线类上实现距离计算成员函数。*/

#include "stdafx.h"
#include<iostream>
#include<cmath>
using namespace std;

class cpoint//点类
{
private:
	double x,y;
public:
	cpoint(double xx=0,double yy=0)
	{x=xx;y=yy;}
	double get_x(){return x;}
	double get_y(){return y;}
	void set()
	{
		cout<<"请输入点坐标"<<endl;
		cin>>x>>y;
	}
};
class cline//折线类
{
private:
	cpoint poi;//定义点类
	double a,b,c;//折线：ax+by+c=0
	double x0,y0;
	double d;
public:
	cline(){}//默认构造
	cline(double _a,double _b,double _c)
	{a=_a;b=_b;c=_c;}
	void input()//输入函数
	{
		poi.set();
		cout<<"输入折线系数"<<endl;
		cin>>a>>b>>c;}
	void fun()//值传递
		{x0=poi.get_x();
		y0=poi.get_y();}
	double fun1()
	{
	double s=fabs(a*x0+b*x0+c);
		double m=sqrt(a*a+b*b);
		d=s/m;
		return d;
	}
	void output() //输出函数
	{cout<<"点到直线距离为："<<d<<endl;}
	~cline(){}//析构函数
};


int main()
{
	cline c1;
	c1.input();
	c1.fun();
	c1.fun1();
	c1.output();
	::system("pause");
	return 0;
}