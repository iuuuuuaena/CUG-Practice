#ifndef TREEPAINT_H
#define TREEPAINT_H

#include <QWidget>
#include"mainwindow.h"
#include<QtMath>
#include<QPoint>
#include<QQueue>

namespace Ui {
class TreePaint;
}

class TreePaint : public QWidget
{
    Q_OBJECT

public:
    explicit TreePaint(QWidget *parent = 0);
    ~TreePaint();
    void getNode(MyBinTree<char> *p);
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_btn_swap_clicked();

private:
    Ui::TreePaint *ui;
    MyBinTree<char> *tree;
};

#endif // TREEPAINT_H
