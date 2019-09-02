#pragma once
#ifndef BANK_H
#define BANK_H
#include<iostream>
using namespace std;
class Bank
{
public:
	Bank();
	~Bank();
	void init();
	void print();//打印当前系统信息
	void printWork();//打印执行过程
	bool request();//发起资源请求
	void reduction();//还原
	bool checkSecurity();//安全性检测
	bool checkOneProcess(int i);//检测一个进程
private:
	int process;//进程数
	int resource;//资源数
	int *available;//可利用资源数
	int **allocation;//分配矩阵
	int **max;//最大需求矩阵
	int **need;//需求矩阵
	int *work;//工作向量
	bool *finish;//纪录进程是否能够完成

	int **allocation_copy;//allocation的拷贝，便于还原
	int **workRecord;//纪录每次的work
	int *sequence;//一个安全序列纪录

	int rProcess;//当前请求的进程
	int *rResource;//当前进程请求的资源
};

Bank::Bank()
{
	this->init();
	this->print();
	cout << "没有进程请求资源时:" << endl;
	this->checkSecurity();
	this->printWork();
}
Bank::~Bank()
{
	for (size_t i = 0; i < process; i++)
	{
		delete allocation[i], max[i], need[i], allocation_copy[i], workRecord[i];
	}
	delete allocation, max, need, available, work, rResource, allocation_copy, finish, workRecord;
}
void Bank::init()
{
	cout << "输入进程数" << endl;
	cin >> process;
	cout << "输入资源数" << endl;
	cin >> resource;

	finish = new bool[process];
	workRecord = new int*[process];
	sequence = new int[process];
	for (size_t i = 0; i < process; i++)
	{
		workRecord[i] = new int[resource];
	}

	//初始化分配矩阵与拷贝
	allocation = new int*[process];
	allocation_copy = new int*[process];
	for (size_t i = 0; i < process; i++)
	{
		allocation[i] = new int[resource];
		allocation_copy[i] = new int[resource];
		cout << "数入进程" << i << "分配的资源数(共有" << this->resource << "种资源)" << endl;
		for (size_t j = 0; j < resource; j++)
		{
			cin >> allocation[i][j]; allocation_copy[i][j] = allocation[i][j];
		}
	}
	//初始化最大需求矩阵
	max = new int*[process];
	for (size_t i = 0; i < process; i++)
	{
		max[i] = new int[resource];
		cout << "数入进程" << i << "最大需求资源数(共有" << this->resource << "种资源)" << endl;
		for (size_t j = 0; j < resource; j++)
		{
			cin >> max[i][j];
		}
	}
	//初始化可利用资源数
	available = new int[resource];
	cout << "输入可利用资源数(共有" << resource << "种资源)" << endl;
	for (size_t i = 0; i < resource; i++)
	{
		cin >> available[i];
	}
	//初始化需求矩阵
	need = new int*[process];
	for (size_t i = 0; i < process; i++)
	{
		need[i] = new int[resource];
		for (size_t j = 0; j < resource; j++)
		{
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
	work = new int[resource];
	for (size_t i = 0; i < resource; i++)
	{
		work[i] = available[i];
	}
	rResource = new int[resource];
}
void Bank::print()
{
	cout << "---------------------------------------当前资源分配----------------------------------------" << endl;
	cout << "Process\t|\tAllocation\t|\tMax\t\t|\tNeed\t\t|Available\t" << endl;
	cout << "Resource";
	for (size_t i = 0; i < 4; i++)
	{
		char tmp = 'A';
		cout << "|";
		for (size_t i = 0; i < resource; i++)
		{
			cout << tmp << '\t'; tmp++;
		}
	}
	cout << endl;
	for (size_t i = 0; i < process; i++)
	{
		cout << "P[" << i << "]\t|";
		for (size_t j = 0; j < resource; j++)
		{
			cout << allocation[i][j] << '\t';
		}cout << "|";
		for (size_t j = 0; j < resource; j++)
		{
			cout << max[i][j] << '\t';
		}cout << "|";
		for (size_t j = 0; j < resource; j++)
		{
			cout << need[i][j] << '\t';
		}
		if (i==0)
		{
			cout << "|";
			for (size_t j = 0; j < resource; j++)
			{
				cout << available[j] << '\t';
			}
		}
		cout << endl;
	}
}
bool Bank::request()
{
	cout << "输入要请求资源的进程(0-" << process-1 << ")" << endl;
	int tmp;
	cin >> tmp;
	if (tmp>=process)
	{
		cout << "输入的进程超出了进程总数" << endl;
		return false;
	}
	rProcess = tmp;
	cout << "请输入请求的资源数(共有" << resource << "个资源)" << endl;
	for (size_t i = 0; i < resource; i++)
	{
		cin >> tmp;
		if (tmp>max[rProcess][i]-allocation[rProcess][i])
		{
			cout << "输入的请求资源超过了最大请求数" << endl;
			return false;
		}
		rResource[i] = tmp;
	}
	//用请求更新信息
	for (size_t i = 0; i < resource; i++)
	{
		need[rProcess][i] = need[rProcess][i] - rResource[i];
		allocation[rProcess][i] = allocation[rProcess][i] + rResource[i];
		work[i] = work[i] - rResource[i];
	}
	//进行安全性检测
	if (!checkSecurity())
	{
		cout << "找不到安全序列,系统处于不安全状态。" << endl;
		this->reduction();
		return false;
	}
	cout << "存在安全序列，系统处于安全状态，可为其分配资源。其中一种序列:" << endl;
	//输出序列执行过程
	this->printWork();
	return true;
}
bool Bank::checkSecurity()
{
	bool deadlock = false;
	int index = 0;
	memset(finish, false, process);
	while (!deadlock&&index<process)
	{
		deadlock = true;
		for (size_t i = 0; i < process; i++)
		{
			if (!finish[i]&&checkOneProcess(i))
			{
				deadlock = false;
				sequence[index++] = i;
				finish[i] = true;
				for (size_t j = 0; j < resource; j++)
				{
					workRecord[i][j] = work[j];
					work[j] += allocation[i][j];
				}
			}
		}
		if (deadlock)//发生死锁
		{
			return false;
		}
	}
	return true;
}
bool Bank::checkOneProcess(int i)
{
	for (size_t j = 0; j < resource; j++)
	{
		if (work[j]<need[i][j])
		{
			return false;
		}
	}
	return true;
}
void Bank::printWork()
{
	cout << "---------------------------------------请求资源后执行过程----------------------------------------" << endl;
	cout << "Process\t|\tAllocation\t|\tNeed\t\t|\tWork\t\t" << endl;
	cout << "Resource";
	for (size_t i = 0; i < 3; i++)
	{
		char tmp = 'A';
		cout << "|";
		for (size_t i = 0; i < resource; i++)
		{
			cout << tmp << '\t'; tmp++;
		}
	}
	cout << endl;
	for (size_t i = 0; i < process; i++)
	{
		cout << "P[" << sequence[i] << "]\t|";
		for (size_t j = 0; j < resource; j++)
		{
			cout << allocation[sequence[i]][j] << '\t';
		}cout << "|";
		for (size_t j = 0; j < resource; j++)
		{
			cout << need[sequence[i]][j] << '\t';
		}cout << "|";
		for (size_t j = 0; j < resource; j++)
		{
			cout << workRecord[sequence[i]][j] << '\t';
		}
		cout << endl;
	}
}
void Bank::reduction()
{
	for (size_t i = 0; i < process; i++)
	{
		for (size_t j = 0; j < resource; j++)
		{
			allocation[i][j] = allocation_copy[i][j];
			need[i][j] = max[i][j] - allocation[i][j];
		}
	}
	for (size_t i = 0; i < resource; i++)
	{
		work[i] = available[i];
	}
}

#endif // !BANK_H
