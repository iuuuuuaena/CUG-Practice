#include "treepaint.h"
#include "ui_treepaint.h"

TreePaint::TreePaint(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreePaint)
{
    ui->setupUi(this);
}

TreePaint::~TreePaint()
{
    delete ui;
}
void TreePaint::getNode(MyBinTree<char> *p){
    this->tree=p;
}

struct TreePoint
{
    TreePoint(QPoint po,int f,BinTreeNode<char> *p_=NULL):p(p_) ,floor(f),point(po){}
    QPoint point;
    BinTreeNode<char> *p;
    int floor;
};

void TreePaint::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing, true);//抗锯齿
    painter.setRenderHints(QPainter::TextAntialiasing,true);
    QFont font;
    painter.setPen(QColor(0, 160, 230));
    font.setFamily("Microsoft YaHei");
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    painter.setBrush(brush);

    double w=this->width();
    double h=this->height();
    int tree_height=tree->Height();
    int r=w/qPow(2,tree_height-1);
    r=(r/2-20>10)?r/2-20:10;
    int b=2;//倍数
    int dis_y=h/(tree_height+1);
    r=(r<dis_y/2)?r:dis_y/2;
    r=(r>40)?40:r;
    font.setPointSize(r);
    painter.setFont(font);
    BinTreeNode<char> *p=tree->getRoot();
    QPoint point(w/2,r*2);
    TreePoint tp(point,tree_height,p);
    QQueue<TreePoint> Q;
    Q.push_back(tp);
    painter.drawEllipse(tp.point,r,r);
    painter.drawText(tp.point.x()-r/2,tp.point.y()+r/2,QString(tp.p->data));
    while (!Q.isEmpty()) {
        tp=Q.front();Q.pop_front();
        if(tp.p->leftChild!=NULL||tp.p->rightChild!=NULL)
        {
            if(tp.p->leftChild!=NULL){
                QPoint po(tp.point.x()-r*qPow(b,tp.floor-2),tp.point.y()+dis_y);
                TreePoint temp(po,tp.floor-1,tp.p->leftChild);
                Q.push_back(temp);
                painter.drawLine(tp.point,temp.point);
                painter.drawEllipse(tp.point,r,r);
                painter.drawText(tp.point.x()-r/2,tp.point.y()+r/2,QString(tp.p->data));
                painter.drawEllipse(temp.point,r,r);
                painter.drawText(temp.point.x()-r/2,temp.point.y()+r/2,QString(temp.p->data));
            }
            else {
                QPoint po(tp.point.x()-r*qPow(b,tp.floor-2),tp.point.y()+dis_y);
                painter.drawLine(tp.point,po);
                painter.drawEllipse(tp.point,r,r);
                painter.drawText(tp.point.x()-r/2,tp.point.y()+r/2,QString(tp.p->data));
                painter.drawEllipse(po,r,r);
                painter.drawText(po.x()-r/2,po.y()+r/2,"#");
            }
            if(tp.p->rightChild!=NULL){
                QPoint po(tp.point.x()+r*qPow(b,tp.floor-2),tp.point.y()+dis_y);
                TreePoint temp(po,tp.floor-1,tp.p->rightChild);
                Q.push_back(temp);
                painter.drawLine(tp.point,temp.point);
                painter.drawEllipse(tp.point,r,r);
                painter.drawText(tp.point.x()-r/2,tp.point.y()+r/2,QString(tp.p->data));
                painter.drawEllipse(temp.point,r,r);
                painter.drawText(temp.point.x()-r/2,temp.point.y()+r/2,QString(temp.p->data));
            }
            else {
                QPoint po(tp.point.x()+r*qPow(b,tp.floor-2),tp.point.y()+dis_y);
                painter.drawLine(tp.point,po);
                painter.drawEllipse(tp.point,r,r);
                painter.drawText(tp.point.x()-r/2,tp.point.y()+r/2,QString(tp.p->data));
                painter.drawEllipse(po,r,r);
                painter.drawText(po.x()-r/2,po.y()+r/2,"#");
            }
        }
    }
}

void TreePaint::on_btn_swap_clicked()
{
    tree->SwapTree();
    this->update();
}
