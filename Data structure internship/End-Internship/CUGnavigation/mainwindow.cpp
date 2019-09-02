#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include<QtMath>
#include<QStack>
#include<QDebug>
#include<QEventLoop>
#include<QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Scene=new QGraphicsScene;
    G=new Graphlnk<int,double>(53);
    G->ReadFromFile("D:/MyQtCode/CUGnavigation/resource/files/xianlu.txt");
    this->ui->view->setDragMode(QGraphicsView::ScrollHandDrag);
    this->init();
    this->ui->view->setScene(Scene);
    this->ui->view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Scene;
    delete G;
    //exit(0);
}

void MainWindow::init(){
    QPixmap background;
    background.load("D:/MyQtCode/CUGnavigation/resource/pictures/daohang.png");
    Scene->addPixmap(background);
    z=50;r=20;
    QFile file("D:/MyQtCode/CUGnavigation/resource/files/infopath.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::critical(NULL,"error","failed open","OK");return;
    }
    QTextStream in(&file);
    QString path,text;
    for(int i=0;i<16;i++){in>>text>>path;
        MyEllipseItem *Item=new MyEllipseItem(i);Item->info->setup(path,text);
        Item->setBrush(QBrush(QColor(255,0,0)));
        Item->setRect(QRectF(G->NodeTable[i].point.x()-r/2,G->NodeTable[i].point.y()-r/2,r,r));
        this->Scene->addItem(Item);
    }
    //G->output();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    qreal s;
    if(value>z){
        s=qPow(1.01,value-z);
    }else {
        s=qPow(1/1.01,z-value);
    }
    ui->view->scale(s,s);
    z=value;
}

void MainWindow::on_btn_search_clicked()
{
    int start=this->ui->cb_start->currentIndex();
    int end=this->ui->cb_end->currentIndex();
    if(start<0||end<0||start==end){
        QMessageBox::critical(this,"error","please choose_start point and end_point","OK");
        return;
    }
    start-=1;
    end-=1;
    this->clear();
    int path[53];double dist[53];
    ShortestPath(*G,start,dist,path);
    QStack<QPoint> stack_point;
    stack_point.push(G->NodeTable[end].point);int i=end;
//    for(int i=0;i<53;i++){
//        qDebug()<<path[i];
//    }
    while (path[i]!=-1) {
        stack_point.push(G->NodeTable[path[i]].point);
        i=path[i];
    }//stack_point.push(G->NodeTable[start].point);
    QPoint temp=G->NodeTable[start].point;
    while (!stack_point.empty()) {
        QGraphicsLineItem *Line=new QGraphicsLineItem;
        QPen pen=Line->pen();
        pen.setColor(QColor(0,0,255));
        pen.setWidth(7);
        pen.setStyle(Qt::SolidLine);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        Line->setPen(pen);
        Line->setLine(temp.x(),temp.y(),stack_point.top().x(),stack_point.top().y());
        vec.push_back(Line);
        this->Scene->addItem(Line);wait(200);
        temp=stack_point.top();
        stack_point.pop();
    }
}

void MainWindow::clear(){
    while (!vec.empty()) {
        Scene->removeItem(vec.back());
        vec.pop_back();
    }
    this->ui->view->update();
    this->update();
    //init();
}

void MainWindow::on_btn_clear_clicked()
{
    this->clear();
}

void MainWindow::wait(int ms){
    QEventLoop eventloop;
    QTimer::singleShot(ms, &eventloop, SLOT(quit()));
    eventloop.exec();
}
