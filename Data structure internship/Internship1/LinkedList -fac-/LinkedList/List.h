#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

struct  LinkNode	//链表类节点
{
	int data;	//数据域
	LinkNode *link;	//指针域
	LinkNode(LinkNode *ptr = NULL) { link = ptr; }//仅初始化指针
	LinkNode(const int &item, LinkNode *ptr = NULL) {//初始化数据和指针的构造
		data = item; link = ptr;
	}
};

class List	//int单链表类
{
public:
	List() { first = new LinkNode; };//构造函数
	List(const int &x) { first = new LinkNode(x); }//构造函数
	List(List &L);//复制构造函数
	~List() { makeEmpty(); };//析构函数
	void makeEmpty();//置空
	int Length()const;//获取长度
	LinkNode *getHead()const { return first; }//获取头节点
	LinkNode *Search(int x);//查找元素x
	LinkNode *Locate(int i)const;//定位元素
	bool getData(int i, int &x)const;//取出元素的值
	void setData(int i, int &x);//修改元素值
	bool Insert(int i, int &x);//插入元素
	bool Remove(int i, int &x);//移除元素
	bool isEmpty()const//判空
	{
		return this->first->link == NULL ? true : false;
	}
	bool isFull()const { return false; }//判满
	void Sort();
	void Input();
	void Output();//输出
	List & operator=(List &L);
	void factorial(int n);
	void Inversion();

protected:
	LinkNode *first;
};

