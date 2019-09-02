// practice1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <process.h>
#include <time.h>
using namespace std;

#define N 10
#define producer_size 3
#define consumer_size 2
HANDLE producer_thread[producer_size];
HANDLE consumer_thread[consumer_size];
//线程ID
UINT producer_ID[producer_size];
UINT consumer_ID[consumer_size];
HANDLE Mymutex, Myfull, Myempty;

int buffer[N];
int in = 0, out = 0, item = 0;

bool run = true;

void insert_item(int item) {
	buffer[in] = item;
	cout << "produce " << item << " in buffer " << in << endl;
	in = (in + 1) % N;
}
void remove_item() {
	cout << "consume " << buffer[out] << " in buffer " << out << endl;
	out = (out + 1) % N;
}
int produce_item() {
	return rand() % 100;
}



unsigned __stdcall producer(HANDLE) {
	//int item;
	while (run)
	{
		//item = produce_item();
		item = item + 1;
		WaitForSingleObject(Myempty, INFINITE);
		WaitForSingleObject(Mymutex, INFINITE);
		insert_item(item);
		Sleep(500);
		ReleaseMutex(Mymutex);
		ReleaseSemaphore(Myfull, 1, NULL);
	}
	return 0;
}

unsigned __stdcall consumer(HANDLE) {
	while (run)
	{
		WaitForSingleObject(Myfull, INFINITE);
		WaitForSingleObject(Mymutex, INFINITE);
		remove_item();
		Sleep(500);
		ReleaseMutex(Mymutex);
		ReleaseSemaphore(Myempty, 1, NULL);
	}
	return 0;
}



int main()
{
	Mymutex = CreateMutex(NULL, false, NULL);//bInitialOwner BOOL，如创建进程希望立即拥有互斥体，则设为TRUE。一个互斥体同时只能由一个线程拥有
	Myfull = CreateSemaphore(NULL, 0, N, NULL);
	Myempty = CreateSemaphore(NULL, N, N, NULL);
	for (int i = 0; i < producer_size; i++) {
		producer_thread[i]=(HANDLE)_beginthreadex(NULL, 0, producer, NULL, 0, &producer_ID[i]);
		cout << "create producer " << i << endl;
	}
	for (int  i = 0; i < consumer_size; i++)
	{
		consumer_thread[i]=(HANDLE)_beginthreadex(NULL, 0, consumer, NULL, 0, &consumer_ID[i]);
		cout  << "create consumer " << i << endl;
	}
	/*主线程等待子线程结束*/
	//for (int i = 0; i < producer_size; i++) {
	//	WaitForSingleObject(producer_thread[i], INFINITE);
	//	CloseHandle(producer_thread[i]);
	//}
	//for (int i = 0; i < consumer_size; i++)
	//{
	//	WaitForSingleObject(consumer_thread[i], INFINITE);
	//	CloseHandle(consumer_thread[i]);
	//}
	if (getchar()) {
		run = false;
	}
	return 0;
}