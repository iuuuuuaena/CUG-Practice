#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H
#include <iostream>
#include <cassert>
using namespace std;

template<class T>
struct StackNode
{
    T data;
    StackNode<T> *link;
    StackNode(T d = 0,StackNode<T> *next=NULL):link(next),data(d){}
};
template <class T>
class LinkedStack
{
public:
    LinkedStack() :top(NULL) {}//无头节点
    ~LinkedStack() { makeEmpty(); }
    void Push(const T &x);
    bool Pop(T &x);
    bool Pop();
    bool Top(T &x)const;
    T Top();
    int Size()const;
    bool IsEmpty()const {
        return top == NULL;
    }
    bool IsFull()const{
        return false;
    }
    void makeEmpty();
//    friend ostream& operator << (ostream &os, LinkedStack <T> &s) {
//        os << "Stack Size:" << s.Size() << endl;
//        StackNode<T> *p = s.top;
//        int i = 0;
//        while (p)
//        {
//            os << ++i << ":" << p->data << endl;
//            p = p->link;
//        }
//        return os;
//    }

protected:
    StackNode<T> *top;
};

template<class T>
void LinkedStack<T>::Push(const T & x)
{
    top = new StackNode<T>(x, top);
    assert(top);//创建新节点失败退出
}

template<class T>
bool LinkedStack<T>::Pop(T & x)
{
    if (IsEmpty()) {
        return false;
    }
    StackNode <T> *p = top;
    top = top->link;
    x = p->data;
    delete p;
    return true;
}

template<class T>
bool LinkedStack<T>::Pop()
{
    if(IsEmpty()){
        return false;
    }
    StackNode<T> *p=top;
    top=top->link;
    delete p;
    return true;
}

template<class T>
bool LinkedStack<T>::Top(T & x) const
{
    if (IsEmpty()) {
        return false;
    }
    x = top->data;
    return true;
}

template<class T>
T LinkedStack<T>::Top()
{
    if(IsEmpty()){
        return 0;
    }
    return top->data;
}

template<class T>
int LinkedStack<T>::Size() const
{
    StackNode<T> *p = top;
    int k = 0;
    while (p)
    {
        p = p->link;
        k++;
    }
    return k;
}

template<class T>
void LinkedStack<T>::makeEmpty()
{
    StackNode<T> *p;
    while (top)
    {
        p = top;
        top = top->link;
        delete p;
    }
}
#endif // LINKEDSTACK_H
