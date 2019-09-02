#pragma once
#include <string>
#include <iostream>
#include <queue>
using namespace std;
struct Node {
	int begin;//起始地址
	int size;//长度
	Node* next;
	string process;//状态(os->操作系统,hole->空闲区,process->进程)
	Node(int b, int s, string p, Node* n = NULL) {
		begin = b;
		size = s;
		process = p;
		next = n;
	}
};
class MemoryManage {
public:
	MemoryManage(int size=256, int osSize=8);
	~MemoryManage();
	void init(int size, int osSize);
	//mode:0->最先匹配法,1->下次匹配法,2->最佳匹配法,3->最坏匹配法
	bool request(string process, int size, int mode);
	void assignMemory(Node* node, string process, int size);
	bool firstFit(string process, int size);
	bool bestFit(string process, int size);
	bool nextFit(string process, int size);
	bool worstFit(string process, int size);
	void print();
	void scanf();
	bool memoryRecycling(string process);
	bool tighteningMemory();
private:
	Node* head;//头指针
	Node* current;//纪录当前位置
	int size;
};
