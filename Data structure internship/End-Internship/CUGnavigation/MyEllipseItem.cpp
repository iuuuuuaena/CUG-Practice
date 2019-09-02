#include "MyEllipseItem.h"

MyEllipseItem::MyEllipseItem(QWidget *parent)
{
    info=new Information(parent);
    setAcceptHoverEvents(true);
}

MyEllipseItem::MyEllipseItem(int key, QWidget *parent){
    this->key=key;
    info=new Information(parent);
    setAcceptHoverEvents(true);
}

void MyEllipseItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    info->setGeometry(event->screenPos().rx()+10,event->screenPos().ry(),380,297);
    info->setVisible(true);
}
void MyEllipseItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    info->setVisible(false);
}

void MyEllipseItem::setString(QString s)
{
    str=s;
}

MyEllipseItem::~MyEllipseItem(){
    info->close();
    delete info;
}
