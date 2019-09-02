#ifndef LIST_H
#define LIST_H
#include <iostream>
using namespace std;

struct LinkNode
{
	int a;//·Ö×Ó
	int b;//·ÖÄ¸
	LinkNode *link;
	LinkNode(LinkNode *ptr = NULL) { link = ptr; }
	LinkNode(const int &x, const int &y, LinkNode *ptr = NULL) {
		a = x; b = y; link = ptr;
	}
};

class list
{
protected:
	LinkNode *first;
	

public:
	list() { first = new LinkNode; };
	list(const int &x, const int &y) { first = new LinkNode(x, y); }
	~list() { this->makeEmpty(); };
	void makeEmpty();
	int Length()const;
	LinkNode *Locate(int i)const;
	bool Insert(int i, int &x, int &y);
	void Output()const;
	void Farey(int n);
};


#endif // !LIST_H