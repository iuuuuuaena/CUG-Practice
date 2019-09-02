// 计算三角形面积.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;


int main()
{
	double a[100], b[100], c[100];
	double s, n;
	float  area;
	cout << "请输入要测试的数据的组数" << endl;
	cin >> n;//共n组数据
	cout << "请输入三角形三条边长：" << endl;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i] >> b[i] >> c[i];
	}
	for (int i = 1; i <= n; i++)
	{
		s = (a[i] + b[i] + c[i]) / 2;
		(float)area = sqrt(double(s*(s - a[i])*(s - b[i])*(s - c[i])));
		if (a[i] + b[i]>c[i] && a[i] + c[i]>b[i] && b[i] + c[i]>a[i])
		{
			cout << setprecision(2) << fixed << "该三角形面积为：" << area<<endl;
		}
		else
		{
			cout << "Input error!" << endl;
		}
	}
	::system("pause");
	return 0;
}
