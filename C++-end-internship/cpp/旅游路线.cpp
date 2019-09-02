// 旅游路线.cpp : 定义控制台应用程序的入口点。
/*设在n-1个城市的情况下已经有了结果……bca，再加入一个城市……bcax，则有：经过城市a的不可以经过城市x；没经过城市a的可以经过城市x，也可以不经过城市x；以及之前所有程序都没经过，只玩了程序x的。
经过城市x的有 f(n-1) - f(n-2) 个
没经过城市x的有 f(n-2) 个
所以 f(n) = [f(n-1) - f(n-2)] + [2 * f(n-2)] + 1 = f(n-1) + f(n-2) + 1*/

#include "stdafx.h"
#include<iostream>
using namespace std;

int f(int n)
{
	if(n==0)return 0;
	else if(n==1)return 1;
	else return f(n-1)+f(n-2)+1;
}

int main()
{
	cout<<"请输入城市数量"<<endl;
	int n;
	cin>>n;
	if(n>=0){int m=f(n);
	cout<<"路线选择有："<<m<<"种"<<endl;}
	else cout<<"输入有误"<<endl;
	::system("pause");
	return 0;
}

