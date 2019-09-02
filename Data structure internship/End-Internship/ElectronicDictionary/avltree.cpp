#include "AVLtree.h"
bool isContain(const QString &str1,const QString &str2){
    for(int i=0;i<str2.length();i++){
        if(str1[i]!=str2[i]){return false;}
    }
    return true;
}

AVLTree::AVLTree()
{
    root=NULL;
}
AVLNode *AVLTree::Search(QString x, AVLNode *ptr){
    if (ptr == NULL){
        return NULL;
    }
    AVLNode *temp = ptr;
    while (temp){
        if (temp->data.key == x){
            return temp;
        }
        if (temp->data.key > x){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }
    return NULL;
}
vector<WordNode> AVLTree::BlurrySearch(QString x, AVLNode *ptr) const{
//    if(isContain("abc","a")){qDebug()<<"contain";}
    //qDebug()<<x;
    //qDebug()<<1;
    vector<WordNode> Vec;
    if (ptr == NULL){
        return Vec;
    }
    AVLNode *temp = ptr;//qDebug()<<2;
    while (temp){/*qDebug()<<i<<temp->data.key;i++;*/
        if (isContain(temp->data.key,x)){//qDebug()<<3;//qDebug()<<"contain";
            //Vec.push_back(temp->data);
            break;
        }
        if (temp->data.key > x){//qDebug()<<4;
            temp = temp->left;
        }
        else{//qDebug()<<5;
            temp=temp->right;
        }
    }std::stack<AVLNode*> S;
    do {//qDebug()<<6;
        while (temp!=NULL)
        {
            S.push(temp);
            temp = temp->left;
        }
        if (!S.empty()) {
            temp = S.top(); S.pop();if(isContain(temp->data.key,x)){Vec.push_back(temp->data);}
            temp = temp->right;
        }
    } while (temp != NULL || !S.empty());
//    temp=temp->right;
//    while (temp!=NULL) {
//        if(temp->data.key.contains(x)){
//            Vec.push_back(temp->data);
//        }
//        temp=temp->right;
//        //qDebug()<<i;i++;
//    }
    return Vec;
}
bool AVLTree::Export(AVLNode *ptr, QTextStream &out){
    if (ptr == NULL){
        return false;
    }
    AVLNode *temp = ptr;
    std::stack<AVLNode*> S;
    do {//qDebug()<<6;
        while (temp!=NULL)
        {
            S.push(temp);
            temp = temp->left;
        }
        if (!S.empty()) {
            temp = S.top(); S.pop();out<<temp->data.key<<'\n'<<temp->data.description<<'\n';
            temp = temp->right;
        }
    } while (temp != NULL || !S.empty());
    return true;
}

int AVLTree::Height(AVLNode *ptr)const{
    if (!ptr){
        return 0;
    }
    int n=Height(ptr->left);
    int m=Height(ptr->right);
    return n<m ? m+1 : n+1;
}
//以下必须对应教材的图，而教材图缺了一些中间步骤，要补足才易于理解
//右子树比左子树高: 做左单旋转后新根在ptr
void AVLTree::RotateL(AVLNode *& ptr){
    AVLNode *subL = ptr;			//保留原来的根结点
    ptr = subL->right;					//原根的右子女将成为新根
    subL->right = ptr->left;			//ptr成为新根前卸掉左子女，成为原根的右子女
    ptr->left = subL;					//左单旋，ptr成为新根，原根成为新根的右子女
    ptr->bf = subL->bf = 0;				//改写平衡度
}


//左子树比右子树高, 旋转后新根在ptr
void AVLTree::RotateR(AVLNode *& ptr){
    AVLNode *subR = ptr;
    ptr = subR->left;					//原根的左子女成为新根
    subR->left = ptr->right;			//新根原右子女成为原根的左子女
    ptr->right = subR;					//原根成为新根的右子女
    ptr->bf = subR->bf = 0;				//改写平衡度
}

void AVLTree::RotateLR(AVLNode *& ptr){
    AVLNode *subR = ptr;
    AVLNode *subL = subR->left;
    ptr = subL->right;					//先左旋
    subL->right = ptr->left;			//ptr成为新根前卸掉左子女，成为原根的右子女
    ptr->left = subL;					//左单旋，ptr成为新根，原根成为新根的右子女
    if (ptr->bf <= 0){					//旋转前插入新结点后ptr左子树变高
        subL->bf = 0;
    }
    else{								//插入新结点后ptr右子树变高
        subL->bf = -1;
    }
    subR->left = ptr->right;
    ptr->right = subR;
    if (ptr->bf == -1){					//旋转前插入新结点后ptr左子树变高
        subR->bf = 1;
    }
    else{								//插入新结点后ptr右子树变高
        subR->bf = 0;
    }
    ptr->bf = 0;
}


void AVLTree::RotateRL(AVLNode *& ptr){
    AVLNode *subL = ptr;
    AVLNode *subR = subL->right;
    ptr = subR->left;
    subR->left = ptr->right;
    ptr->right = subR;
    if (ptr->bf >= 0){
        subR->bf = 0;
    }
    else{
        subR->bf = 1;
    }
    subL->right = ptr->left;
    ptr->left = subL;
    if (ptr->bf == 1){
        subL->bf = -1;
    }
    else{
        subL->bf = 0;
    }
    ptr->bf = 0;
}

//在以ptr为根的AVL树中插入新元素e1,
//如果插入成功,函数返回true,否则返回false。
bool AVLTree::Insert(AVLNode *& ptr, WordNode &e1){
    AVLNode *pr = NULL, *p = ptr, *q;
    int d;
    std::stack<AVLNode*> st;
    while (p != NULL){					//寻找插入位置
        if (e1 == p->data) return false;//找到等于e1的结点,不插入
        pr = p;  st.push(pr);			//否则用栈记忆查找路径
        if (e1 < p->data) p = p->left;
        else p = p->right;
    }
    p = new AVLNode(e1);			//创建新结点,data=e1,bf=0
    //assert(p);
    if (pr == NULL){						//空树,新结点成为根结点
        ptr = p;
        return true;
    }
    if (e1 < pr->data){					//新结点插入
        pr->left = p;
    }
    else{
        pr->right = p;
    }
    //重新平衡化
    while (st.empty() == false){
        pr=st.top();st.pop();						//从栈中退出父结点
        if (p == pr->left){				//调整父结点的平衡因子
            pr->bf--;
        }
        else{
            pr->bf++;
        }
        if (pr->bf == 0){				//第1种情况,|bf|=0,平衡退出
            break;
        }
        if (pr->bf == 1 || pr->bf == -1){//第2种情况,|bf|=1
            p = pr;
        }
        else{							//第3种情况,|bf|=2
            d = (pr->bf < 0) ? -1 : 1;	//区别单双旋转标志
            if (p->bf == d){				//两结点平衡因子同号,单旋转
                if (d == -1)				{
                    RotateR(pr);		//右单旋转
                }
                else{
                    RotateL(pr);		//左单旋转
                }
            }
            else{							//两结点平衡因子反号,双旋转
                if (d == -1){
                    RotateLR(pr);		//先左后右双旋转,”<”型
                }
                else{
                    RotateRL(pr);		//先右后左双旋转,”>”型
                }
            }
            break;						//不再向上调整
        }//第三种情况结束
    }
    // 对于第二种情况需要继续从结点向根的方向回溯调整
    if (st.empty() == true){			//调整到树的根结点
        ptr = pr;
    }
    else{								//中间重新链接
        q=st.top();//st.getTop(q);
        if (q->data > pr->data){
            q->left = pr;
        }
        else{
            q->right = pr;
        }
    }
    return true;
}

//在以ptr为根的AVL树中删除关键码为x的结点。
//如果删除成功,函数返回true,同时通过参数e1返回被删结点元素；
//如果删除失败则函数返回false。
bool AVLTree::Remove(AVLNode *& ptr, QString x, WordNode &e1){
    AVLNode *pr = NULL, *p = ptr, *q, *ppr;
    int d, dd = 0;
    std::stack<AVLNode*> st;
    while (p != NULL){					//寻找删除位置
        if (x == p->data.key){			//找到等于x的结点,停止搜索
            break;
        }
        pr = p;  st.push(pr);			//否则用栈记忆查找路径
        if (x < p->data.key){
            p = p->left;
        }
        else{
            p = p->right;
        }
    }

    if (p == NULL){						//未找到被删结点,删除失败
        return false;
    }
    e1 = p->data;

    if (p->left && p->right){			//被删结点有两个子女
        pr = p;  st.push(pr);
        q = p->left;					//在p左子树找p的直接前驱
        while (q->right){
            pr = q;
            st.push(pr);
            q = q->right;
        }
        p->data = q->data;				//用q的值填补p
        p = q;							//被删结点转化为q
    }
    //以下包括由双子女转换后的和原来就非双子女的。
    //同时以下也包括单子女和无子女
    if (p->left){						//被删结点p最多只有一个子女q
        q = p->left;
    }
    else{
        q = p->right;					//无子女时，q为NULL
    }
    if (pr == NULL){					//被删结点为根结点,其父结点为空
        ptr = q;
    }
    else{								//被删结点不是根结点
        if (pr->left == p){				//链接
            pr->left = q;
        }
        else{
            pr->right = q;
        }
        while (st.empty() == false){	//重新平衡化
            pr=st.top();st.pop();					//从栈中退出父结点
            if(q==NULL){				//调整父结点的平衡因子。无子女
                pr->bf=0;
            }
            else{						//单子女
                if (pr->right == q){
                    pr->bf--;			//删在右边
                }
                else{
                    pr->bf++;			//删在左边
                }
            }
            if (st.empty() == false){
                ppr=st.top();//st.getTop(ppr);			//从栈中取出祖父结点
                dd = (ppr->left == pr) ?-1 : 1;	//旋转后与上层链接方向
            }
            else{						//栈空,旋转后不与上层链接
                dd = 0;
            }
            if (pr->bf == 1 || pr->bf == -1){ 	//图7.20,|bf|=1
                break;
            }
            if (pr->bf != 0){			//|bf|=2
                if (pr->bf < 0) {d = -1;  q = pr->left;}
                else{					//用q指示较高的子树
                    d = 1;
                    q = pr->right;
                }
                if (q->bf == 0){			//图7.22
                    if (d == -1){
                        RotateR(pr);		//再参见图7.15
                        pr->bf = 1;
                        pr->right->bf = -1;	//#改
                    }
                    else{
                        RotateL(pr);
                        pr->bf = -1;
                        pr->left->bf = 1;	//#改
                    }
                    //旋转后新根与上层链接
                    if (dd == -1){
                        ppr->left = pr;
                    }
                    else if (dd == 1){
                        ppr->right = pr;
                    }
                    break;
                }
                if (q->bf == d){			//两结点平衡因子同号,图7.23
                    if (d == -1){		//右单旋转
                        RotateR(pr);
                    }
                    else{				//左单旋转
                        RotateL(pr);
                    }
                }
                else{					//两结点平衡因子反号,图7.24
                    if (d == -1){		//先左后右双旋转,”<”型
                        RotateLR(pr);
                    }
                    else{				//先右后左双旋转,”>”型
                        RotateRL(pr);
                    }
                }
                //旋转后新根与上层链接
                if (dd == -1){
                    ppr->left = pr;
                }
                else if (dd == 1){
                    ppr->right = pr;
                }
            }
            q = pr;						//图7.21,|bf|=0
        }
        if (st.empty() == true){		//调整到树的根结点
            ptr = pr;
        }
    }
    delete p;
    return true;
}


//void AVLTree::Traverse(AVLNode *ptr, ostream &out)const{
//    if (ptr != NULL){					//树非空
//        Traverse(ptr->left, out);		//中序遍历左子树
//        out << ptr->data.key << ' ';	//输出根的数据
//        Traverse(ptr->right, out);		//中序遍历右子树
//    }
//}
//
//void AVLTree::PrintTree(AVLNode *ptr, ostream &out)const{
//    if (!ptr){
//        return;
//    }
//    out << ptr->data.key;
//    if (ptr->left == NULL && ptr->right == NULL){
//        return;
//    }
//    out << "(";
//    PrintTree(ptr->left, out);
//    out << ',';
//    PrintTree(ptr->right, out);
//    out << ")";
//}

//void AVLTree::PrintData(AVLNode *ptr, ostream &out)const{
//    if (ptr){
//        PrintData(ptr->left, out);
//        out << ptr->data <<'\t'<< ptr->bf << endl;
//        PrintData(ptr->right, out);
//    }
//}
