#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include "minheap.h"
#include<iostream>
#include<string>
#include<QDebug>
//#pragma warning(disable : 4703)
using namespace std;

//Huffman树结点的类定义
template <typename E>
struct HuffmanNode {
    E data;
    HuffmanNode<E> *leftChild, *rightChild, *parent;
    HuffmanNode() :leftChild(NULL), rightChild(NULL), parent(NULL) {}//构造函数
    HuffmanNode(E elem, HuffmanNode<E> * pr, HuffmanNode<E> *left, HuffmanNode<E>*right)
        :data(elem), parent(pr), leftChild(left), rightChild(right) {}
    //重载操作符：
    bool operator > (HuffmanNode<E> right) {
        return data > right.data;
    }
    bool operator >= (HuffmanNode<E> right) {
        return (data > right.data) || (data == right.data);
    }
    bool operator < (HuffmanNode<E> right) {
        return data < right.data;
    }
    bool operator <= (HuffmanNode<E> right) {
        return (data < right.data) || (data == right.data);
    }
    bool operator == (HuffmanNode<E> right) {
        return data == right.data;
    }
};

//Huffman树类定义
template <typename E>class HuffmanTree {
public:
    HuffmanTree(E w[], int n);
    ~HuffmanTree() {
        deleteTree(root);
    }
    HuffmanNode<E>* getRoot() {
        return root;
    }
    //void output(HuffmanNode<E> * t, string str, ostream &out);
protected:
    HuffmanNode<E> *root;
    void deleteTree(HuffmanNode<E> * t);
    void mergeTree(HuffmanNode<E> *ht1, HuffmanNode<E> *ht2, HuffmanNode<E> *& parent);
};


//--------------------------------------------------------------------------------------------------
template <typename E>
void HuffmanTree<E>::deleteTree(HuffmanNode<E> * t) {//清除子二叉树，添加
    if (t != NULL) {
        deleteTree(t->leftChild);
        deleteTree(t->rightChild);
        delete t;
    }
}

template <typename E>
HuffmanTree<E>::HuffmanTree(E w[], int n) {
    //给出n个权值w[1]～w[n], 构造Huffman树
    //qDebug()<<"tree1";
    MinHeap<HuffmanNode<E> > hp;/*qDebug()<<"tree2";*/	//使用最小堆存放森林的结点
    HuffmanNode<E> *parent, *first, *second, temp;
    HuffmanNode<E> *NodeList/* = new HuffmanNode<E>[n]*/; //不宜一次性建立森林，否则析构函数一个一个删结点时操作系统断言出错
    int i;//qDebug()<<"tree3";
    for (i = 0; i < n; i++) {//按棵逐步建立森林中的树木，并作为Huffman树的叶结点。数据放入森林
        NodeList = new HuffmanNode<E>;
        NodeList->data = w[i];
        NodeList->leftChild = NULL;
        NodeList->rightChild = NULL;/*qDebug()<<i;*/
        NodeList->parent = NodeList;//父指针指向自己，信息入堆后，出堆时可以找到对应结点
        hp.Insert(*NodeList);	//森林信息插入最小堆中
    }/*qDebug()<<"tree4";*/
    for (i = 0; i < n - 1; i++) {	//n-1趟, 建Huffman树
        hp.RemoveMin(temp); 		//根权值最小的树
        first = temp.parent;			//first指向对应的最小结点
        hp.RemoveMin(temp);	        //根权值次小的树
        second = temp.parent;			//second指向对应的次小结点
        mergeTree(first, second, parent);	//合并
        hp.Insert(*parent);		//新结点插入堆中
    }
    root = parent;		//建立根结点
    //qDebug()<<"treeend";
    //cout<<"root = "<<root->data<<endl;
    //output(root,string(),cout);
}

template <typename E>
void HuffmanTree<E>::mergeTree(HuffmanNode<E> *bt1,
    HuffmanNode<E> *bt2, HuffmanNode<E> *& parent) {//pasent必须为引用，它作为返回量
    parent = new HuffmanNode<E>;
    parent->leftChild = bt1;
    parent->rightChild = bt2;
    parent->parent = parent;//归并后的根结点的父指针指向新子树，在信息入堆后，出堆时可以找到对应子树
    parent->data = bt1->data + bt2->data;		//数据为左右子树数据之和
    bt1->parent = bt2->parent = parent;		//处理两子树根结点的父指针
    //cout<<bt1->data<<" and "<<bt2->data<<" union to:"<<parent->data<<endl;
}

//template <typename E>
//void HuffmanTree<E>::output(HuffmanNode<E> * t, string str, ostream &out){//按目录结构方式输出二叉树，添加
//    if (!t){
//        return;
//    }
//    out << str << t->data;
//    if (t->leftChild){
//        out << "─┐" << endl;
//        if (t->rightChild){
//            output(t->leftChild, str+"│　", out);
//        }
//        else{
//            output(t->leftChild, str+"　　", out);
//        }
//    }
//    if (t->rightChild){
//        out << endl << str << "└─┐" << endl;
//        output(t->rightChild, str+"　　", out);
//    }
//}
#endif // HUFFMANTREE_H
