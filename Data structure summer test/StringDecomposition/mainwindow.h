#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stringdecomposition.h>
#include <fstream>
#include <iostream>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QByteArray>
#include <QDebug>

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
    QString line;
};

#endif // MAINWINDOW_H
