#include "pch.h"
#include "MemoryManage.h"
#include <Windows.h>

MemoryManage::MemoryManage(int size, int osSize) {
	init(size, osSize);
}
MemoryManage::~MemoryManage(){
	Node *p;
	if (head==NULL)
	{
		return;
	}
	while (head)
	{
		p = head->next;
		delete head;
		head = p;
	}
}
void MemoryManage::init(int size, int osSize) {
	this->head = new Node(0, osSize, "os");
	head->next = new Node(osSize, size - osSize, "hole");
	this->size = size;
}

bool MemoryManage::request(string process, int size, int mode) {
	switch (mode) {
	case 0:
		return this->firstFit(process, size);
	case 1:
		return this->nextFit(process, size);
	case 2:
		return this->bestFit(process, size);
	case 3:
		return this->worstFit(process, size);
	default:return false;
	}
}

void MemoryManage::assignMemory(Node *node, string process, int size) {
	if (node->size==size)
	{
		node->process = process;
		this->print();
		return;
	}
	if (node->begin+size!=this->size)
	{
		current = new Node(node->begin + size, node->size - size, "hole",node->next);
		node->next = current;
	}
	node->process = process;
	node->size = size;
	
	this->print();
}

bool MemoryManage::firstFit(string process, int size) {
	Node* tmp = head;
	while (tmp != NULL) {
		if (tmp->process == "hole"&&tmp->size >= size) {
			this->assignMemory(tmp, process, size);
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

bool MemoryManage::nextFit(string process, int size) {
	Node* tmp = current;
	while (tmp != NULL) {
		if (tmp->process == "hole"&&tmp->size >= size) {
			this->assignMemory(tmp, process, size);
			return true;
		}
		tmp = tmp->next;
	}
	tmp = head;
	while (head != current) {
		if (tmp->process == "hole"&&tmp->size >= size) {
			this->assignMemory(tmp, process, size);
			return true;
		}
		tmp = tmp->next;
	}
	return false;
}

bool MemoryManage::bestFit(string process, int size) {
	Node *best = NULL;
	Node *tmp = head;
	while (tmp != NULL) {
		if (tmp->process == "hole"&&tmp->size >= size) {
			if (best == NULL) {
				best = tmp;
			}
			else if (tmp->size < best->size) {
				best = tmp;
			}
		}
		tmp = tmp->next;
	}
	if (best != NULL) {
		this->assignMemory(best, process, size);
		return true;
	}
	return false;
}

bool MemoryManage::worstFit(string process, int size) {
	Node *worst = NULL;
	Node *tmp = head;
	while (tmp != NULL) {
		if (tmp->process == "hole"&&tmp->size >= size) {
			if (worst == NULL) {
				worst = tmp;
			}
			else if (tmp->size > worst->size) {
				worst = tmp;
			}
		}
		tmp = tmp->next;
	}
	if (worst != NULL) {
		this->assignMemory(worst, process, size);
		return true;
	}
	return false;
}

void MemoryManage::print() {
	Node *tmp = head;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	cout << "-------------------------------------\n块号\t进程\t大小\t地址" << endl;
	int i = 0;
	while (tmp != NULL) {
		if (tmp->process=="os")
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		}
		else if(tmp->process=="hole")
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
		}
		cout << i << '\t' << tmp->process << '\t' << tmp->size << "k\t" << tmp->begin << "k-" << tmp->begin + tmp->size - 1 << "k" << endl;
		++i; tmp = tmp->next;
	}
	cout << "-------------------------------------" << endl;
}

void MemoryManage::scanf() {
	char c=1;string str; int size;
	while (c!='q')
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		cout << "-------------------------------------\n0->申请内存\n1->释放内存\nq->退出\n-------------------------------------\n";
		cin >> c;
		if (c=='0')
		{
			cout << "输入进程名称(string)和申请的内存大小(int)" << endl;
			cin >> str >> size;
			int mode;
			cout << "输入分配方法(0->最先匹配法,1->下次匹配法,2->最佳匹配法,3->最坏匹配法)" << endl;
			cin >> mode;
			if (!this->request(str, size, mode)) {
				cout << "分配失败" << endl;
				cout << "执行内存紧缩" << endl;
				this->tighteningMemory();
				if (!this->request(str, size, mode)) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << "仍然失败,请释放程序内存" << endl;
				}
			}
		}
		if (c == '1') {
			cout << "输入要释放内存的进程" << endl;
			cin >> str;
			if (!this->memoryRecycling(str))
			{
				cout<<"释放失败"<<endl;
			}
		}
		if (c=='q')
		{
			break;
		}
	}
}

bool MemoryManage::memoryRecycling(string process){
	Node *tmp = head->next;
	Node *p = head;
	while (head!=NULL)
	{
		if (tmp->process==process)
		{
			tmp->process = "hole";
			if (p->process=="hole")
			{
				p->size = p->size + tmp->size;
				p->next = tmp->next;
			}
			if (tmp->next!=NULL&&tmp->next->process=="hole")
			{
				p->size = p->size + tmp->next->size;
				p->next = tmp->next->next;
			}
			cout << "释放成功" << endl;
			this->print();
			return true;
		}
		p = p->next;
		tmp = tmp->next;
	}
	return false;
}

bool MemoryManage::tighteningMemory()
{
	Node *tmp = head->next;
	Node *p;
	Node *q=head;
	while (tmp!=NULL)
	{
		p = tmp->next;
		if (tmp->process=="hole")
		{
			//q->next = p;
			delete tmp;
			tmp = p;
		}
		else
		{
			tmp->begin = q->begin + q->size;
			q->next = tmp;
			q = tmp;
			tmp = p;
		}
	}
	q->next = new Node(q->begin + q->size, size - q->begin - q->size, "hole");
	this->print();
	return true;
}
