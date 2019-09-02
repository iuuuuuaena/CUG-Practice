#include "pch.h"
#include "list.h"



void list::makeEmpty()
{
	LinkNode *q;
	while (first->link != NULL)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
}

int list::Length() const
{
	LinkNode *p = first->link;
	int count = 0;
	while (p != NULL)
	{
		p = p->link;
		count++;
	}
	return count;
}

LinkNode * list::Locate(int i) const
{
	if (i < 0)return NULL;
	LinkNode *current = first; int k = 0;
	while (current != NULL && k < i)
	{
		current = current->link; k++;
	}
	return current;
}

bool list::Insert(int i, int & x, int & y)
{
	if (i < 0) return false;
	LinkNode *current = Locate(i);
	if (current == NULL)return false;
	else
	{
		LinkNode *newNode = new LinkNode(x,y);
		if (newNode == NULL) { cerr << "´æ´¢·ÖÅä´íÎó£¡" << endl; }
		newNode->link = current->link;
		current->link = newNode;
		return true;
	}
}

void list::Output() const
{
	LinkNode *current = first->link;
	while (current != NULL)
	{
		cout << current->a <<"/"<<current->b<< " ";
		current = current->link;
	}
}


void list::Farey(int n)
{
/*for (int i = 2; i <= n; i++) {
		LinkNode *p = first->link;
		while (Locate(Length()-1)) {
			if (p->b + p->link->b <= i) {
				LinkNode *temp = new LinkNode(p->a + p->link->a, p->b + p->link->b);
				temp->link = p->link;
				p->link = temp;
				p = temp->link;
			}
			else p = p->link;
		}
	}*/
	first->link = new LinkNode(0, 1);
	int x = 1;
	LinkNode *lastNode = new LinkNode(1, 1);
	first->link->link = lastNode;
		int j, k;
		LinkNode *current = first->link;
		while(current!=lastNode)
		{
			j = current->a + current->link->a;
			k = current->b + current->link->b;
			if (k <= n) { 
				LinkNode *newNode = new LinkNode(j, k); 
				newNode->link = current->link;
				current->link = newNode;
				continue;
			}
			current = current->link;
		}
}


