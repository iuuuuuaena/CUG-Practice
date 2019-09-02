#ifndef MYELLIPSEITEM_H
#define MYELLIPSEITEM_H
#include<QGraphicsEllipseItem>
#include<QGraphicsSceneHoverEvent>
#include<QCursor>
#include<QWidget>
#include"Information.h"

class MyEllipseItem : public QGraphicsEllipseItem
{
public:
    MyEllipseItem(QWidget *parent=0);
    MyEllipseItem(int key,QWidget *parent=0 );
    ~MyEllipseItem();
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void setString(QString s);
    Information *info;
private:
    QString str;
    int key;

};

#endif // MYELLIPSEITEM_H
