#include "Information.h"
#include "ui_Information.h"

Information::Information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Information)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);//背景透明
    setVisible(false);
}
void Information::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setBrush(QBrush(Qt::white));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    painter.drawRoundedRect(rect, 15, 15);
}

void Information::setup(QString path, QString text)
{
    this->text=text;
    pixmap=new QPixmap(path);
    ui->lb_pic->setPixmap(*pixmap);
    ui->lb_pic->setScaledContents(true);
    ui->lb_text->setText(text);
}
Information::~Information()
{
    delete pixmap;
    delete ui;
    this->close();
}
