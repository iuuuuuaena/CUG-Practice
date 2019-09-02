#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
int main()
{
int i,k,m,n,p[10];
	cin>>k;
	for(i=0;i<10;i++)
	{p[i]=i+1;}
	i=0;
	n=0;
	m=9;//共淘汰9个人
	while(m)
	{
	if(p[i]!=0)
		n++;
	if(n==k)
		{
		cout<<"淘汰："<<p[i]<<'\t'<<"剩余情况：";
		p[i]=0;
		n=0;
		for(int j=0;j<10;j++)
		{cout<<" "<<p[j];}
		cout<<endl;
		m--;
		}
	i++;
	if(i==10)	{i=0;}
	}
for(int a=0;a<10;a++)
{
	if(p[a]==0){continue;}
	else	cout<<"最后剩的人的编号是："<<p[a]<<endl;
}
	
	::system("pause");
	return 0;
}