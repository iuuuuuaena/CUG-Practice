#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include "MyEllipseItem.h"
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGraphicsScene *Scene;
    void init();

private slots:
    void on_horizontalSlider_valueChanged(int value);

    void on_btn_search_clicked();
    void clear();
    void wait(int ms);
    void on_btn_clear_clicked();

private:
    Ui::MainWindow *ui;
    int z;
    int r;
    Graphlnk<int,double> *G;
    vector<QGraphicsLineItem*> vec;
};

#endif // MAINWINDOW_H
