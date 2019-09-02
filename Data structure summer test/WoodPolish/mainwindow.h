#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "woodpolish.h"

//struct wood
//{
//    int wei;
//    int l;
//};

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
    Ui::MainWindow *ui;
    int t;
    int *n;
    wood (*a)[5001];
    QString records;
};

#endif // MAINWINDOW_H
