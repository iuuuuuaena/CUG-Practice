#ifndef GENERATESUDOKU_H
#define GENERATESUDOKU_H
#include<QtAlgorithms>
#include"time.h"

class generateSudoku
{
public:
    generateSudoku();
    bool createSudoku(int **map,int b);
private:
    int	blank;  // 数独棋盘待填格数，新的待填数独棋盘模板初始化后有 72 格待填
    int	hint;  // 数独棋盘提示格数
    int fullBoard[9][9];  // 完整数独棋盘
    void newTemplate();
    bool dfs();
    int validNumbersQuantity(const int &row, const int &col, int mark[]);
};

#endif // GENERATESUDOKU_H
