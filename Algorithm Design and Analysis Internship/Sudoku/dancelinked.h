#ifndef DANCELINKED_H
#define DANCELINKED_H
#include<vector>
#include<assert.h>
#include<QDebug>
using namespace std;

const int kMaxNodes = 1 + 81 * 4 + 9 * 9 * 9 * 4;
const int kMaxColumns = 400; // 列的数目最多不超过400个
const int kRow = 100, kCol = 200, kBox = 300;
const int N=81;

struct Node;
typedef Node Column;
struct Node
{
    Node() {}
    Node *left;
    Node *right;
    Node *up;
    Node *down;
    Column *col;
    int name;//记录该元素所在列的表头元素在columns数组中的下标
    int size;//用于记录这一列一共有多少元素,一般这个域只供表头元素使用
};

class DanceLinked
{
public:
    DanceLinked();
    DanceLinked(int inout[81]);
    Column* new_column(int n = 0); // 构建一个新列
    Node* new_row(int col);
    Column* get_min_column();

    void append_column(int n);

    int get_row_col(int row, int val);
    int get_col_col(int col, int val);
    int get_box_col(int box, int val);

    void getSolution(int a[81]);
    void cover(Column* c);//所谓的cover,表示我们选择了这一列,我们就要将这一列中其它元素所在的行移除
    void uncover(Column* c);

    void put_left(Column* old, Column* nnew);
    void put_up(Column* old, Node* nnew);

    bool solve();
private:
    Column* root; // root表示上面的head
    int*    inout; // 输入的谜题
    Column* columns[400]; // columns用于记录每一列的头部,即表头
    vector<Node*> stack; // 用于存储选择的列
    Node    nodes[kMaxNodes]; // 我们使用数组来实现算法,事先分配好,避免new
    int     cur_node; // 指示器,表示nodes中已经分配了的node的数目
};

#endif // DANCELINKED_H
