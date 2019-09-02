#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "changeproblem.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int readfromfile();
    void writetofile(QString record);

private slots:
    void on_btn_choose_clicked();

    void on_btn_ok_clicked();

private:
    int n;//n种不同硬币
    int *t;//硬币面值
    int *coins;//各种硬币个数
    int m;//要找的钱

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
