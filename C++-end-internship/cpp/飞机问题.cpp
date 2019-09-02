// 飞机问题.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<algorithm>
using namespace std;
int t[400000];
int d[400000];
int main()
{
	int n,s,i,j,len,temp;
	while(cin>>n>>s)
	{
		for(i=0;i<n;i++)
		{cin>>t[i];}
		sort(t,t+n);//排序
		for(i=0,j=1;i<n;i++)//除去重复元素
		{	if(i==0)
			{
				d[j]=t[i];
				j++;}
			else
			{
				if(t[i]!=t[i-1])
				{d[j]=t[i];j++;}
			}
		}
		len=j;
		t[1]=s+d[1]*d[1];
		for(i=2;i<len;i++)//t[i]表示机场i到中心机场的最小费用，则有递推式：t[i]=min{s+d[i]^2,s+(d[j]-d[i])^2+t[j]}(1<=j<i)
		{
			t[i]=s+d[i]*d[i];
			for(j=1;j<i;j++)
				{
					temp=s+(d[i]-d[j])*(d[i]-d[j])+t[j];
					if(temp<t[i])
					t[i]=temp;
				}
		}
	cout<<t[len-1]<<endl;
	}
	return 0;
}