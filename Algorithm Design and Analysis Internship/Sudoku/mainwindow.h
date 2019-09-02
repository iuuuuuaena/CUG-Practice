#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include<QPaintEvent>
#include<QPainter>
#include<QPen>
#include<vector>
#include<QLabel>
#include"generatesudoku.h"
#include"dancelinked.h"
#include<QDebug>
#include<QTime>
#include<QTimer>
#include<QMessageBox>

using namespace std;

#include<QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_actionnew_game_triggered();

    void update_Time();

    void on_btn_restart_clicked();

    void on_btn_clear_clicked();

    void on_btn_auto_clicked();

    void on_btn_submit_clicked();

    void on_btn_pause_clicked();

private:
    Ui::MainWindow *ui;
    int **map;//用于更新
    int **map_;//题目
    bool init();
    bool clear();
    bool newGame();

    bool check_();
    bool checkVal_(int vec[], int val);
    bool finished();

    int dis_x,dis_y,r;

    generateSudoku sudoku;

    QPoint choose_point;//当前选择的map上的格
    int choose_val;//选择的值
    vector<vector<QLabel*>> label_map;
    vector<QLabel*> label_val;

    //计时器
    QTimer *ptimer;
    QTime basetime;
    QTime pauseTime;
    void start();
    void pause();
    void carryOn();
    int go;

    int level;
};

#endif // MAINWINDOW_H
