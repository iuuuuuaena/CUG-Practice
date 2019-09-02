#include "pch.h"
#include "List.h"



List::List(List & L)
{
	int value;
	LinkNode *srcptr = L.getHead();
	LinkNode *destptr = first = new LinkNode;
	while (srcptr->link) {
		value = srcptr->link->data;
		destptr->link = new LinkNode(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;
}

void List::makeEmpty()
{
	LinkNode *q;
	while (first->link!=NULL)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
}

int List::Length() const
{
	LinkNode *p = first->link;
	int count = 0;
	while (p!=NULL)
	{
		p = p->link;
		count++;
	}
	return count;
}

LinkNode * List::Search(int x)
{
	LinkNode *current = first->link;
	while (current!=NULL)
	{
		if (current->data == x) {
			break;
		}
		else
		{
			current = current->link;
		}
	}
	return current;
}

LinkNode * List::Locate(int i) const
{
	if (i < 0)return NULL;
	LinkNode *current = first; int k = 0;
	while (current!=NULL&&k<i)
	{
		current = current->link; k++;
	}
	return current;
}

bool List::getData(int i, int & x) const
{
	if (i <= 0)return false;
	LinkNode *current = Locate(i);
	if (current == NULL)return false;
	else
	{
		x = current->data; return true;
	}

	return false;
}

void List::setData(int i, int & x)
{
	if (i <= 0) return;
	LinkNode *current = Locate(i);
	if (current == NULL)return;
	else
	{
		current->data = x;
	}
}

bool List::Insert(int i, int & x)
{
	if (i < 0) return false;
	LinkNode *current = Locate(i);
	if (current == NULL)return false;
	else
	{
		LinkNode *newNode = new LinkNode(x);
		if (newNode == NULL) { cerr << "´æ´¢·ÖÅä´íÎó£¡" << endl; }
		newNode->link = current->link;
		current->link = newNode;
		return true;
	}
}

bool List::Remove(int i, int & x)
{
	LinkNode *current = Locate(i-1);
	if (current == NULL&&current->link==NULL)return false;
	LinkNode *del = current->link;
	current->link = del->link;
	x = del->data;
	delete del;
	return true;
}

void List::Sort()
{
}

void List::Input()
{
}

void List::Output()
{
	LinkNode *current = first->link;
	cout << current->data;
	current = current->link;
	while (current!=NULL)
	{
		cout <<setw(3)<<setfill('0')<< current->data;
		current = current->link;
	}
}

List & List::operator=(List & L)
{
	int value;
	LinkNode *srcptr = L.getHead();
	LinkNode *destptr = first = new LinkNode;
	makeEmpty();
	while (srcptr->link) {
		value = srcptr->link->data;
		destptr->link = new LinkNode(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;
	return *this;
}

void List::factorial(int n)
{
	int i = 1;
	this->Insert(0, i);
	while (i <= n) {
		LinkNode *current = first->link;
		int k = 0;
		while (current)
		{
			int pro = (current->data)*i + k;
			current->data = pro % 1000;
			k = pro / 1000;
			if (k > 0 && !(current->link)) {
				current->link = new LinkNode(0);
			}
			current = current->link;
		}
		i++;
	}
}

void List::Inversion()
{
	LinkNode *f=first->link;
	if (f == NULL)return;
	LinkNode *p = f->link, *pr = NULL;
	while (p!=NULL)
	{
		f->link = pr;
		pr = f;
		f = p;
		p = p->link;
	}
	f->link = pr;
	first->link = f;
}
