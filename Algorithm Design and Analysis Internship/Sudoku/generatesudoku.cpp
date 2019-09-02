#include "generatesudoku.h"

generateSudoku::generateSudoku()
{

}

bool generateSudoku::createSudoku(int **map,int b)
{
    blank=72;
    int k=rand()%10+50;
    while (true) {
        newTemplate();
        if (dfs()) {
            for(int i=0;i<9;++i){
                for(int j=0;j<9;++j){
                    map[i][j]=this->fullBoard[i][j];
                }
            }
            while (k--) {
                int q=rand()%9,w=rand()%9;
                map[q][w]=0;
            }
            return true;
        }
    }
    return false;
}

void generateSudoku::newTemplate()
{
    srand(unsigned(time(nullptr)) + rand());
    hint = 9;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (i == 0) {
                fullBoard[0][j] = 9-j;
            }
            else {
                fullBoard[i][j] = 0;
            }
        }
    }
    for (int i = 0, j; i < 20; i++) {
        j = (rand() * 10) % 7 + 2;
        qSwap(fullBoard[0][1], fullBoard[0][j]);
    }
    for (int i = 1; i < 9; i++) {
        int a = (rand() * 10) % 9;
        int b = (rand() * 10) % 9;
        if (a + b == 0) {
            i--;
            continue;
        }
        qSwap(fullBoard[0][i], fullBoard[a][b]);
    }
}

bool generateSudoku::dfs()
{
    if (blank == 0) {
        return true;
    }
    int minQuantity = 10;
    int mini = 0, minj = 0;
    int mark[10] = {0};

    // 寻找可填写数字数量最少的格子
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (fullBoard[i][j] != 0) {
                continue;
            }

            int count = validNumbersQuantity(i, j, mark);
            if (count == 0) {
                return false;
            }
            if (count < minQuantity) {
                minQuantity = count;
                mini = i;
                minj = j;
            }
        }
    }

    // 优先填写 可填写数字数量最少 的格子
    validNumbersQuantity(mini, minj, mark);
    for (int i = 1; i <= 9; i++) {
        if (mark[i] == 0) {
            fullBoard[mini][minj] = i;
            blank--;
            dfs();
            if (blank == 0) {
                return true;
            }
            fullBoard[mini][minj] = 0;  // 回溯法
            blank++;
        }
    }
    return true;
}

int generateSudoku::validNumbersQuantity(const int &row, const int &col, int mark[])
{
    for (int i = 0; i < 10; i++) {
        mark[i] = 0;
    }
    for (int i = 0; i < 9; i++) {
        mark[fullBoard[i][col]] = 1;
        mark[fullBoard[row][i]] = 1;
    }
    int baseRow = row / 3 * 3;
    int baseCol = col / 3 * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mark[fullBoard[baseRow + i][baseCol + j]] = 1;
        }
    }
    int count = 0;
    for (int i = 1; i <= 9; i++) {
        if (mark[i] == 0) {
            count++;
        }
    }
    return count;
}
