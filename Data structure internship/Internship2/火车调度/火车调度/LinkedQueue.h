#pragma once
#include <iostream>
using namespace std;
template<class T>
struct LinkNode
{
	T date;
	LinkNode<T> *link;
	LinkNode(LinkNode<T> *ptr = NULL) { link = ptr; }
	LinkNode(const T &item, LinkNode<T> *ptr = NULL) {
		date = item; link = ptr;
	}
};
template<class T>
class LinkedQueue
{
public:
	LinkedQueue() :rear(NULL), front(NULL) {};
	~LinkedQueue() { makeEmpty(); };
	void makeEmpty();
	bool EnQueue(const T& x);
	bool Dequeue(T& x);
	T Dequeue();
	bool getFront(T& x)const;
	T getFront();
	T getRear();
	bool isEmpty()const { return front == NULL ? true : false; }
	int getSize()const;
	friend ostream& operator<<(ostream& os, LinkedQueue<T>& Q);

protected:
	LinkNode<T> *front, *rear;
};

template<class T>
void LinkedQueue<T>::makeEmpty()
{
	LinkNode<T> *p;
	while (front != NULL)
	{
		p = front; front = front->link; delete p;
	}
}

template<class T>
bool LinkedQueue<T>::EnQueue(const T & x)
{
	if (front == NULL) {
		front = rear = new LinkNode<T>(x);
		if (front == NULL) {
			return false;
		}
	}
	else
	{
		rear->link = new LinkNode<T>(x);
		if (rear->link == NULL) {
			return false;
		}
		rear = rear->link;
	}
	return true;
}

template<class T>
bool LinkedQueue<T>::Dequeue(T & x)
{
	if (isEmpty()) { return false; }
	LinkNode<T> *p = front;
	x = front->date;
	front = front->link;
	delete p;
	return true;
}

template<class T>
T LinkedQueue<T>::Dequeue()
{
	if (isEmpty()) { return false; }
	LinkNode<T> *p = front;
	T x = front->date;
	front = front->link;
	delete p;
	return x;
}

template<class T>
bool LinkedQueue<T>::getFront(T & x) const
{
	if (isEmpty()) { return false; }
	x = front->date;
	return true;
}

template<class T>
 T LinkedQueue<T>::getFront()
{
	 if(isEmpty()){
		 cout << "队列为空" << endl;
		 return 9;
	 }
	return front->date;
}

 template<class T>
 inline T LinkedQueue<T>::getRear()
 {
	 if (isEmpty()) {
		 cout << "队列为空" << endl;
		 return 0;
	 }
	 return rear->date;
 }

template<class T>
int LinkedQueue<T>::getSize() const
{
	LinkNode<T> *p = front;
	int k = 0;
	while (p != NULL)
	{
		p = p->link; k++;
	}
	return k;
}

template<class T>
ostream& operator<<(ostream& os, LinkedQueue<T>& Q)
{
	os << "队列中元素个数有" << Q.getSize() << endl;
	LinkNode<T> *p = Q.front; int i = 0;
	while (p != NULL)
	{
		os << ++i << ":" << p->date << endl;
	}
	return os;
}