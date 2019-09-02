// 人员类.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <string>
using namespace std;

class Date //日期子类 
{
	private: 
		int year; 
		int month; 
		int day; 
	public: Date(){} //默认构造 
			Date(int y,int m,int d) //带参构造 
			{ year=y; month=m; day=d; } 
			void set() //设置数据函数 
			{ cin>>year>>month>>day; } 
			void display() //显示函数 
			{ cout<<year<<"年"<<month<<"月"<<day<<"日"; } }; 
			
class Person //人员类 
{ 
private: 
	int num; 
	char sex; 
	Date birthday; 
	char ID[18]; 
public: Person(){} //默认构造 
		Person(int n,char id[18],char s='m') 
		{ num=n; sex=s; strcpy(ID,id); } //有默认值的带参构造 
		Person(Person& p) //拷贝构造 
		{ num=p.num; sex=p.sex; birthday=p.birthday; strcpy(ID,p.ID); } 
		void input() //输入函数 
		{ cout<<"录入数据："<<endl; 
			cout<<"编号："; 
			cin>>num; 
			cout<<"性别(m/w)："; 
			cin>>sex; cout<<"生日："; 
			birthday.set(); 
			cout<<"身份证号："; 
			cin>>ID; ID[18]='\0'; 
			cout<<endl; } 
		void output() //输出函数 
			{ cout<<"编号："<<num<<endl; 
			cout<<"性别：";
			if(sex='m')
			{cout<<"男"<<endl;} 
			else if(sex='w')
			{cout<<"女";}
			else {cout<<"输入错误！";}
			cout<<"生日："; birthday.display(); 
			cout<<endl; cout<<"身份证号："<<ID<<endl; } 
		~Person() //析构函数 
		{ cout<<" "<<num<<"号人员已经录入"<<endl; } }; 
		
int main() 
{ 
	Person p1; 
	p1.input(); 
	p1.output(); 
	::system("pause");
	return 0; 

}

