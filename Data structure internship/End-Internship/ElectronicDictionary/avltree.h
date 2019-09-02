#ifndef AVLTREE_H
#define AVLTREE_H
#include<QString>
#include<stack>
#include<iostream>
#include<vector>
#include<QDebug>
using namespace std;

struct WordNode
{
    QString key;
    QString description;
    WordNode(){}
    WordNode(QString _key,QString _description) {
        this->key=_key;this->description=_description;
    }
    bool operator ==(const WordNode &wd)const{
        return this->key==wd.key;
    }
    bool operator <(const WordNode &wd)const{
        return this->key<wd.key;
    }
    bool operator >(const WordNode &wd)const{
        return this->key>wd.key;
    }
};

struct AVLNode
{
    int bf;//平衡度
    WordNode data;//单词
    AVLNode *left,*right;
    AVLNode() {
        left=NULL;right=NULL;bf=0;
    }
    AVLNode(WordNode d,AVLNode *l=NULL,AVLNode *r=NULL){
        data=d;left=l;right=r;bf=0;
    }
};

class AVLTree
{
protected:
    QString RefValue;
    AVLNode *root;
    int Height(AVLNode *ptr)const;
    bool Insert(AVLNode *&ptr, WordNode &e1);
    bool Remove(AVLNode *&ptr, QString x, WordNode &e1);
    void RotateL(AVLNode *&ptr);
    void RotateR(AVLNode *&ptr);
    void RotateLR(AVLNode *&ptr);
    void RotateRL(AVLNode *&ptr);
    AVLNode *Search(QString x, AVLNode *par);
    void Traverse(AVLNode *ptr, ostream &out)const;
    void PrintTree(AVLNode *ptr, ostream &out)const;
    void PrintData(AVLNode *ptr, ostream &out)const;
    vector<WordNode> BlurrySearch(QString x, AVLNode *ptr) const;
    bool Export(AVLNode *ptr,QTextStream &out);
public:
    AVLTree();
    AVLTree(QString Ref){
        this->RefValue=Ref;
    }
    int Height()const{
            return Height(root);
        }
    bool Insert(WordNode &e1){
        return Insert(root, e1);
    }
    bool Remove(QString k, WordNode &e1){
        return Remove(root, k, e1);
    }
    AVLNode *Search(QString k){
        return Search(k,root);
    }
    vector<WordNode> BlurrySearch(QString k) const{
        return BlurrySearch(k,root);
    }
    bool Export(QTextStream &out){
        return Export(root,out);
    }
};

#endif // AVLTREE_H
