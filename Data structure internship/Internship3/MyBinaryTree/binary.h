#ifndef BINARY_H
#define BINARY_H
#include<iostream>
#include<fstream>
#include<stack>
#include<queue>
#include<QDebug>

using namespace std;

template<class T>
struct BinTreeNode
{
    T data;
    BinTreeNode<T> *leftChild, *rightChild;
    BinTreeNode():leftChild(NULL),rightChild(NULL){}
    BinTreeNode(T x,BinTreeNode<T> *l=NULL,BinTreeNode<T> *r=NULL):data(x),leftChild(l),rightChild(r){}
};

template<class T>
class BinaryTree {
public:
    BinaryTree():root(NULL){}
    BinaryTree(T value):RefValue(value),root(NULL){}
    BinaryTree(BinaryTree<T> & s);		//复制构造
    ~BinaryTree() { destroy(root); }		//析构
    bool IsEmpty() { return (root == NULL) ? true : false; }	//判空
    /********************************************************************/
    BinTreeNode<T>* Parent(BinTreeNode<T> *current) {//返回父节点
        return(root == NULL || root == current) ?
            NULL : Parent(root, current);
    }
    /********************************************************************/
    BinTreeNode<T>* LeftChild(BinTreeNode<T> *current) {//返回左子女
        return (current != NULL) ? current->leftChild : NULL;
    }
    BinTreeNode<T>* RightChild(BinTreeNode<T>* current) {//返回右子女
        return (current != NULL) ? current->rightChild : NULL;
    }
    int Height() { return Height(root); }//树高度
    int Size() { return Size(root); }//节点数
    BinTreeNode<T>* getRoot()const { return root; }//取根
    void preOrder(void(*visit)(BinTreeNode<T>*p)) {//前序遍历
        preOrder(root, visit);
    }
    void inOrder(void(*visit)(BinTreeNode<T>*p)) {//中序遍历
        inOrder(root, visit);
    }
    void postOrder(void(*visit)(BinTreeNode<T>*p)) {//后序遍历
        postOrder(root, visit);
    }
    void levelOrder(void(*visit)(BinTreeNode<T>*p));//层次序遍历
    int Insert(const T&item);//插入新元素
    //BinTreeNode<T> *Find(T&item)const;//搜索

    void PrintBTree(BinTreeNode<T> *BT);
    /********************非递归遍历*************************/
    void PreOrder(void(*visit)(BinTreeNode<T>*p));//前序
    void PreOrder2(void(*visit)(BinTreeNode<T>*p));//另一种前序
    void InOrder(void(*visit)(BinTreeNode<T>*p));//中序
    void PostOrder(void(*visit)(BinTreeNode<T>*p));//后序
    /********************非递归遍历************************/

protected:
    BinTreeNode<T> *root;
    T RefValue;
    void CreateBinTree(istream& in, BinTreeNode<T> *&subTree);//从文件中读入建树(广义表)
    void CreateBinTree(ifstream& in, BinTreeNode<T> *&subTree);//前序遍历建立二叉树
    BinTreeNode<T>* CreateBinTree(T *VLR, T*LVR, int n);//利用前序序列和中序序列创建二叉树

    bool Insert(BinTreeNode<T> *&subTree, const T& x);//插入
    void destroy(BinTreeNode<T> *&subTree);//删除
    //bool Find(BinTreeNode<T> *subTree, const T &x);//查找
    BinTreeNode<T> *Copy(BinTreeNode<T> *orignode);//复制
    int Height(BinTreeNode<T> *subTree);//返回树高度
    int Size(BinTreeNode<T> *subTree);//返回节点数
    BinTreeNode<T> *Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *current);//返回父节点
    BinTreeNode<T> *Find(BinTreeNode<T> *subTree, const T &x)const;//搜寻x
    void Traverse(BinTreeNode<T> *subTree, ostream &out);//前序遍历输出
    void preOrder(BinTreeNode<T> *subTree, void(*visit)(BinTreeNode<T> *p));//前序遍历
    void inOrder(BinTreeNode<T> *subTree, void(*visit)(BinTreeNode<T> *p));//中序遍历
    void postOrder(BinTreeNode<T> *subTree, void(*visit)(BinTreeNode<T> *p));//后序遍历
    friend istream& operator>>(istream &in, BinaryTree<T> &Tree);//重载输入操作
    friend ostream& operator<<(ostream &out, BinaryTree<T> &Tree);//重载输出操作
    friend bool operator==(const BinaryTree<T> &s, const BinaryTree<T> &t);//重载==

};

template<class T>
void BinaryTree<T>::destroy(BinTreeNode<T> *& subTree) {
    //若指针subTree不为空，则删除根为subTree的子树
    if (subTree != NULL) {
        destroy(subTree->leftChild);
        destroy(subTree->rightChild);
        delete subTree;
    }
}

template<class T>
BinTreeNode<T>* BinaryTree<T>::Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *current) {
    //私有函数：从节点subTree开始，搜索节点current的父节点。若找到，则返回父节点的地址，否则返回NULL
    if (subTree == NULL)return NULL;
    if (subTree->leftChild == current || subTree->rightChild == current)return subTree;
    BinTreeNode<T> *p;
    if ((p = Parent(subTree->leftChild, current)) != NULL)return p;
    else
    {
        return Parent(subTree->rightChild, current);
    }
}

template<class T>
void BinaryTree<T>::Traverse(BinTreeNode<T> *subTree, ostream &out) {//搜索并输出根为subTree的二叉树
    if (subTree != NULL) {
        out << subTree->data << ' ';
        Traverse(subTree->leftChild, out);
        Traverse(subTree->rightChild, out);
    }
}

template<class T>
istream& operator>>(istream &in, BinaryTree<T>& Tree) {
    CreateTree(in, Tree.root);
    return in;
}

template<class T>
ostream& operator<<(ostream &out, BinaryTree<T>& Tree) {
    out << "二叉树的前序遍历\n";
    Tree.Traverse(Tree.root, out);
    return out;
}

template<class T>
void BinaryTree<T>::CreateBinTree(istream &in, BinTreeNode<T> *&subTree) {//广义表建立
    stack<BinTreeNode<T> *> s;
    subTree = NULL;
    BinTreeNode<T> *p, *t; int k;
    T ch;
    in >> ch;
    while (ch!=RefValue)
    {
        switch (ch)
        {
        case'(':s.push(p); k = 1; break;
        case')':s.pop(); break;
        case',':k = 2; break;
        default:p = new BinTreeNode<T>(ch);
            if (subTree == NULL)subTree = p;
            else if (k == 1) {
                t = s.top(); t->leftChild = p;
            }
            else
            {
                t = s.top(); t->rightChild = p;
            }
        }
        in >> ch;
    }
}
//中序遍历算法
template<class T>
void BinaryTree<T>::inOrder(BinTreeNode<T> *subTree, void(*visit)(BinTreeNode<T> *p)) {
    if (subTree != NULL) {
        inOrder(subTree->leftChild, visit);
        visit(subTree);
        inOrder(subTree->rightChild, visit);
    }
}
//前序遍历算法
template<class T>
void BinaryTree<T>::preOrder(BinTreeNode<T> *subTree, void(*visit)(BinTreeNode<T> *p) ){
    if (subTree != NULL) {
        visit(subTree);
        preOrder(subTree->leftChild, visit);
        preOrder(subTree->rightChild, visit);
    }
}
//后序遍历算法
template<class T>
void BinaryTree<T>::postOrder(BinTreeNode<T> *subTree, void(*visit)(BinTreeNode<T>*p)) {
    if (subTree != NULL) {
        postOrder(subTree->leftChild, visit);
        postOrder(subTree->rightChild, visit);
        visit(subTree);
    }
}

template<class T>
int BinaryTree<T>::Size(BinTreeNode<T> *subTree) {
    if (subTree == NULL)return 0;
    else
    {
        return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
    }
}
template<class T>
int BinaryTree<T>::Height(BinTreeNode<T> *subTree) {
    if (subTree == NULL)return NULL;
    else
    {
        int i = Height(subTree->leftChild);
        int j = Height(subTree->rightChild);
        return (i < j) ? j + 1 : i + 1;
    }
}
template<class T>
BinaryTree<T>::BinaryTree(BinaryTree<T> &s) {
    root = Copy(s.root);
}
template<class T>
BinTreeNode<T> *BinaryTree<T>::Copy(BinTreeNode<T> *orignode) {
    if (orignode == NULL)return NULL;
    BinTreeNode<T> *temp = new BinTreeNode<T>;
    temp->data= orignode->data;
    temp->leftChild = Copy(orignode->leftChild);
    temp->rightChild = Copy(orignode->rightChild);
    return temp;
}

template<class T>
bool operator==(const BinaryTree<T> &s, const BinaryTree<T> &t) {
    return(equal(s.root, t.root)) ? true : false;
}

template<class T>
bool equal(BinTreeNode<T> *a, BinTreeNode<T> *b) {
    //如果a和b的子树不等同，返回false，否则返回true
    if (a == NULL && b == NULL)return true;
    if (a != NULL && b != NULL && a->data == b->data&&equal(a->leftChild, b->leftChild) && equal(a->rightChild, b->rightChild))return true;
    else
    {
        return false;
    }
}
template<class T>
void BinaryTree<T>::CreateBinTree(ifstream &in, BinTreeNode<T> *&subTree) {//前序遍历建立二叉树
    T item;
    if (!in.eof()) {
        in >> item;
        if (item != RefValue) {
            subTree = new BinTreeNode<T>(item);
            if (subTree == NULL) {
                cerr << "存储分配出错" << endl; exit(1);
            }
            CreateBinTree(in, subTree->leftChild);
            CreateBinTree(in, subTree->rightChild);
        }
        else
        {
            subTree == NULL;
        }
    }
}
template<class T>
void BinaryTree<T>::PrintBTree(BinTreeNode<T> *BT) {
    if (BT != NULL) {
        cout << BT->data;
        if (BT->leftChild != NULL || BT->rightChild != NULL) {
            cout << '(';
            PrintBTree(BT->leftChild);
            cout << ',';
            if (BT->rightChild != NULL)
                PrintBTree(BT->rightChild);
            cout << ')';
        }
    }
}
/*****************************二叉树遍历的非递归算法*******************************/
template<class T>
void BinaryTree<T>::PreOrder(void(*visit)(BinTreeNode<T> *p)) {//前序遍历算法
    stack<BinTreeNode<T>*> S;
    BinTreeNode<T> *p = root;
    S.push(NULL);
    while (p!=NULL)
    {
        visit(p);
        if (p->rightChild != NULL)S.push(p->rightChild);
        if (p->leftChild != NULL)S.push(p->leftChild);
        else
        {
            S.pop();
        }
    }
}
template<class T>
void BinaryTree<T>::PreOrder2(void(*visit)(BinTreeNode<T> *p)) {//另一种非递归的前序遍历
    stack<BinTreeNode<T>*> S;
    BinTreeNode<T> *p;
    S.push(root);
    while (!S.empty())
    {
        p = S.top(); S.pop(); visit(p);
        if (p->rightChild != NULL)S.push(p->rightChild);
        if (p->leftChild != NULL)S.push(p->leftChild);
    }
}
template<class T>
void BinaryTree<T>::levelOrder(void(*visit)(BinTreeNode<T> *p)) {//层次序遍历
    queue<BinTreeNode<T>*> Q;
    BinTreeNode<T> *p = root;
    Q.push(p);
    while (!Q.empty())
    {
        p = Q.front(); Q.pop(); visit(p);
        if (p->leftChild != NULL)Q.push(p->leftChild);
        if (p->rightChild != NULL)Q.push(p->rightChild);
    }
}
template<class T>
void BinaryTree<T>::InOrder(void(*visit)(BinTreeNode<T> *p)) {//非递归的中序遍历
    stack<BinTreeNode<T> *> S;
    BinTreeNode<T> *p = root;
    do {
        while (p!=NULL)
        {
            S.push(p);
            p = p->leftChild;
        }
        if (!S.empty()) {
            p = S.top(); S.pop(); visit(p);
            p = p->rightChild;
        }
    } while (p != NULL || !S.empty());
}
/******************后序遍历过程中所用栈的节点的定义********************/
template<class T>
struct stkNode
{
    BinTreeNode<T> *ptr;
    enum { L, R }tag;
    stkNode(BinTreeNode<T> *N = NULL) :ptr(N), tag(L) {}
};
template<class T>
void BinaryTree<T>::PostOrder(void(*visit)(BinTreeNode<T> *p)) {
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
            case stkNode<T>::R:visit(p); break;
            }
        }
    } while (!S.empty());
    cout << endl;
}
/*****************************************************/
template<class T>
BinTreeNode<T>* BinaryTree<T>::CreateBinTree(T *VLR, T *LVR, int n) {
    //VLR是前序序列，LVR是中序序列
    if (n == 0)return NULL;
    int k = 0;
    while (VLR[0]!=LVR[k])
    {
        k++;
    }
    BinTreeNode<T> *t = new BinTreeNode<T>(VLR[0]);//根节点
    t->leftChild = CreateBinTree(VLR + 1, LVR, k);//从前序VLR+1开始对中序的0~k-1左子序列的k个元素递归建立左子树
    t->rightChild = CreateBinTree(VLR + k + 1, LVR + k + 1, n - k - 1);//从前序VLR+k+1开始对中序的k+1到n-1的n-k-1个元素建立右子树
    return t;
}
#endif // BINARY_H
