#ifndef MYBINTREE_H
#define MYBINTREE_H
#include"binary.h"

template<class T>
class MyBinTree:public BinaryTree<T>
{
public:
    MyBinTree():BinaryTree() {}
    MyBinTree(T value):BinaryTree(value){}
    MyBinTree(MyBinTree<T> &s){this->root=this->Copy(s.root);}
    void CreatebyPre(T *seq, int n){i=0;CreatebyPre(seq,n,root);}
    void CreatebyLevel(T *seq);
    void SwapTree(){this->SwapTree(root);}
    void PreOrder();
    BinTreeNode<T>* Find(T &item, QString &str);
    void Refactoring(T *VLR, T *LVR, int n);
protected:
    void SwapTree(BinTreeNode<T> *&subTree);
    void CreatebyPre(T *seq, int n, BinTreeNode<T> * &subTree);
    int i;
};

template<class T>
void MyBinTree<T>::CreatebyPre(T *seq, int n, BinTreeNode<T> *&subTree){
    T item;
    if(i<n){
        item=seq[i];i++;
        if(item!=RefValue){
            subTree=new BinTreeNode<T>(item);
            CreatebyPre(seq,n,subTree->leftChild);
            CreatebyPre(seq,n,subTree->rightChild);
        }
    }
}

template <class T>
void MyBinTree<T>::SwapTree(BinTreeNode<T> *&subTree){//交换子树
    if(subTree==NULL)return;
    if(subTree->leftChild==NULL&&subTree->rightChild==NULL){
        return;
    }
    else {
        BinTreeNode<T> *temp;
        temp=subTree->leftChild;
        subTree->leftChild=subTree->rightChild;
        subTree->rightChild=temp;
    }
    SwapTree(subTree->leftChild);
    SwapTree(subTree->rightChild);
}
template<class T>
void MyBinTree<T>::PreOrder() {//前序遍历算法
    stack<BinTreeNode<T>*> S;
    BinTreeNode<T> *p = root;
    S.push(NULL);
    qDebug()<<"前序输出:";
    while (p!=NULL)
    {
        qDebug()<<p->data;
        if (p->rightChild != NULL)S.push(p->rightChild);
        if (p->leftChild != NULL)p=p->leftChild;
        else
        {
            p=S.top();
            S.pop();
        }
    }
}
template<class T>
void MyBinTree<T>::CreatebyLevel(T *seq){
    //qDebug()<<"creatByLevel";
    queue<BinTreeNode<T>*> Q;
    BinTreeNode<T> *p;i=0;
    if(seq[i]!=RefValue){p=new BinTreeNode<T>(seq[i]);i++;}
    else {qDebug()<<"return";return;}
    root=p;
    Q.push(p);
    while (!Q.empty()) {
        p=Q.front();Q.pop();
        if(seq[i]!=RefValue){p->leftChild=new BinTreeNode<T>(seq[i]);Q.push(p->leftChild);i++;}
        else{i++;}
        if(seq[i]!=RefValue){p->rightChild=new BinTreeNode<T>(seq[i]);Q.push(p->rightChild);i++;}
        else{i++;}
    }
}

template<class T>
BinTreeNode<T> *MyBinTree<T>::Find(T &item,QString &str){
    stack<stkNode<T>> S; stkNode<T> w;
    BinTreeNode<T> *p = root;
    do
    {
        while (p!=NULL)
        {
            w.ptr = p; w.tag = stkNode<T>::L; S.push(w);
            p = p->leftChild;
        }
        int continue1 = 1;
        while (continue1&&!S.empty())
        {
            w = S.top(); S.pop(); p = w.ptr;
            switch (w.tag)
            {
            case stkNode<T>::L: w.tag = stkNode<T>::R; S.push(w);
                continue1 = 0;
                p = p->rightChild;
                break;
            case stkNode<T>::R:if(p->data==item){
                    //qDebug()<<"祖先节点:";
                    while (!S.empty()) {
                        //qDebug()<<S.top().ptr->data;
                        str+=QString(S.top().ptr->data);
                        str+=";";
                        S.pop();
                    }
                    return p;
                }; break;
            }
        }
    } while (!S.empty());
    //qDebug()<<"can't find";
    return NULL;
}

template<class T>
void MyBinTree<T>::Refactoring(T *VLR, T *LVR, int n){
    this->root=this->CreateBinTree(VLR,LVR,n);
}
#endif // MYBINTREE_H
