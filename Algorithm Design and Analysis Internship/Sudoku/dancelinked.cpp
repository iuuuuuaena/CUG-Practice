#include "dancelinked.h"

DanceLinked::DanceLinked()
{

}

DanceLinked::DanceLinked(int inout[]) : inout(inout), cur_node(0)
{
    stack.reserve(100); //事先分配好空间

    root = new_column(); //表头元素,并没有加入到column中
    root->left = root->right = root;
    memset(columns, 0, sizeof(columns));

    bool rows[N][10] = { false }; /* 0~9一共10个数 */
    bool cols[N][10] = { false };
    bool boxes[N][10] = { false };

    for (int i = 0; i < N; ++i) {
        int row = i / 9;
        int col = i % 9;
        int box = row / 3 * 3 + col / 3;
        int val = inout[i];
        rows[row][val] = true; //表示在第row行val已经被填了
        cols[col][val] = true; /* 在第col列val已经被填了 */
        boxes[box][val] = true; /* 在第box宫val已经被填了 */
    }

    for (int i = 0; i < N; ++i) { /* 初始化第1~81列 */
        if (inout[i] == 0) { /* 第i格需要填写 */
            append_column(i);
        }
    }

    for (int i = 0; i < 9; ++i) {
        for (int v = 1; v < 10; ++v) {
            if (!rows[i][v]) /* 如果rows[i][v]==0,表示第i行可以填入v */
                append_column(get_row_col(i, v));
            if (!cols[i][v]) /* 如果cols[i][v]==0,表示第i列可以填入v */
                append_column(get_col_col(i, v));
            if (!boxes[i][v]) /* 如果boxes[i][v]==0,表示第i宫可以填入v */
                append_column(get_box_col(i, v));
        }
    }

    for (int i = 0; i < N; ++i) {
        if (inout[i] == 0) {
            int row = i / 9;
            int col = i % 9;
            int box = row / 3 * 3 + col / 3;
            //int val = inout[i];
            for (int v = 1; v < 10; ++v) {
                if (!(rows[row][v] || cols[col][v] || boxes[box][v])) {
                    Node* n0 = new_row(i);
                    Node* nr = new_row(get_row_col(row, v));
                    Node* nc = new_row(get_col_col(col, v));
                    Node* nb = new_row(get_box_col(box, v));
                    put_left(n0, nr);
                    put_left(n0, nc);
                    put_left(n0, nb);
                }
            }
        }
    }
    this->solve();
}

Column *DanceLinked::new_column(int n)
{
    Column* c = &nodes[cur_node++]; // 分配一个节点
    memset(c, 0, sizeof(Column));
    // 让节点内所有的指针都指向自己
    c->left = c;
    c->right = c;
    c->up = c;
    c->down = c;
    c->col = c;
    c->name = n; // name用于表示该节点代表的列,0代表head
    return c;
}

void DanceLinked::append_column(int n) /*  */
{
    assert(columns[n] == NULL);

    Column* c = new_column(n);
    put_left(root, c); /* 将c放在root的左边 */
    columns[n] = c; /* 记录下列头 */
}

Node *DanceLinked::new_row(int col)
{
    assert(columns[col] != NULL);
    assert(cur_node < kMaxNodes);

    Node* r = &nodes[cur_node++];


    memset(r, 0, sizeof(Node));
    r->left = r;
    r->right = r;
    r->up = r;
    r->down = r;
    r->name = col;
    r->col = columns[col];
    put_up(r->col, r);
    return r;
}

int DanceLinked::get_row_col(int row, int val) /* 得到第row行的val对应的下标,这里实际上实现了一个映射函数 */
{
    return kRow + row * 10 + val;
}

int DanceLinked::get_col_col(int col, int val) /* 得到第col列的val所在的下标 */
{
    return kCol + col * 10 + val;
}

int DanceLinked::get_box_col(int box, int val) /*  得到第box宫的val所在的下标 */
{
    return kBox + box * 10 + val;
}

Column *DanceLinked::get_min_column()//元素最少的列
{
    Column* c = root->right;
    int min_size = c->size; /* 获得某一列的元素的个数 */
    if (min_size > 1) {
        for (Column* cc = c->right; cc != root; cc = cc->right) {
            if (min_size > cc->size) {
                c = cc;
                min_size = cc->size;
                if (min_size <= 1)
                    break;
            }
        }
    }
    return c;
}

void DanceLinked::cover(Column *c) /* 所谓的cover,表示我们选择了这一列 */
{
    c->right->left = c->left;
    c->left->right = c->right; /* 在表头中删除掉c */
    for (Node* row = c->down; row != c; row = row->down) { /* 遍历c所在列的元素 */
        for (Node* j = row->right; j != row; j = j->right) { /* 解除该元素所在行 */
            j->down->up = j->up;
            j->up->down = j->down;
            j->col->size--;
        }
    }
}

void DanceLinked::uncover(Column *c)
{
    for (Node* row = c->up; row != c; row = row->up) {
        for (Node* j = row->left; j != row; j = j->left) {
            j->col->size++;
            j->down->up = j;
            j->up->down = j;
        }
    }
    c->right->left = c;
    c->left->right = c;
}

bool DanceLinked::solve()
{
    if (root->left == root) { /* 运行到了这里表示所有的列都被覆盖到了 */
        for (size_t i = 0; i < stack.size(); ++i) {
            Node* n = stack[i]; /* 取出Node */
            int cell = -1;
            int val = -1;
            while (cell == -1 || val == -1) {
                if (n->name < 100)
                    cell = n->name;
                else
                    val = n->name % 10;
                n = n->right;
            }

            //assert(cell != -1 && val != -1);
            inout[cell] = val;
        }
        return true;
    }

    Column* const col = get_min_column();
    cover(col);
    for (Node* row = col->down; row != col; row = row->down) {
        stack.push_back(row);
        for (Node* j = row->right; j != row; j = j->right) {
            cover(j->col);
        }
        if (solve()) {
            return true;
        }
        stack.pop_back();
        for (Node* j = row->left; j != row; j = j->left) {
            uncover(j->col);
        }
    }
    uncover(col);
    return false;
}

void DanceLinked::put_left(Column *old, Column *nnew) /* 将nnew放在old的左边 */
{
    nnew->left = old->left;
    nnew->right = old;
    old->left->right = nnew;
    old->left = nnew;
}

void DanceLinked::put_up(Column *old, Node *nnew) /* 将nnew放在old的上面 */
{
    // 如果old是表头元素,那么nnew就是插入到该列的尾部
    // 不过,说实话,nnew在old所在的列的哪个位置并不重要,因为我们并不是依靠old来确定nnew的位置的
    nnew->up = old->up; /* 需要注意的是,Column结构是一个十字交叉链表 */
    nnew->down = old;
    old->up->down = nnew;
    old->up = nnew;
    old->size++; /* size表示这一列增加了一个元素 */
    nnew->col = old; /* 列头 */
}

void DanceLinked::getSolution(int a[81])
{
    for(int i=0;i<81;++i){
        a[i]=this->inout[i];
    }
}

