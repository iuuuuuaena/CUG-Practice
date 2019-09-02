#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
    this->ptimer=new QTimer;
    go=0;
    connect(this->ptimer,SIGNAL(timeout()),this,SLOT(update_Time()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)//绘制数独布局
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    for(int i=0;i<10;++i){
        if(i%3==0){
            pen.setWidth(2);
            pen.setColor(Qt::black);
        }else {
            pen.setWidth(1);
            pen.setColor(Qt::gray);
        }
        painter.setPen(pen);
        painter.drawLine(QPoint(dis_x,dis_y+i*r),QPoint(dis_x+r*9,dis_y+i*r));
    }
    for(int i=0;i<10;++i){
        if(i%3==0){
            pen.setWidth(2);
            pen.setColor(Qt::black);
        }else {
            pen.setWidth(1);
            pen.setColor(Qt::gray);
        }
        painter.setPen(pen);
        painter.drawLine(QPoint(dis_x+i*r,dis_y),QPoint(dis_x+i*r,dis_y+r*9));
    }
    for(int i=0;i<10;++i){
        if(i%3==0){
            pen.setWidth(2);
        }else {
            pen.setWidth(1);
        }
        painter.setPen(pen);
        painter.drawLine(QPoint(dis_x+10*r,dis_y+i*r),QPoint(dis_x+r*11,dis_y+i*r));
    }
    for(int i=10;i<12;i++){
        painter.drawLine(QPoint(dis_x+i*r,dis_y),QPoint(dis_x+i*r,dis_y+r*9));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        QPoint point=event->pos();
        if(point.x()>=dis_x&&point.x()<=dis_x+r*9&&point.y()>=dis_y&&point.y()<=dis_y+9*r){

            if(go==-1){
                this->carryOn();
            }

            if(this->map_[choose_point.y()][choose_point.x()]!=0){
                this->label_map[choose_point.y()][choose_point.x()]->setStyleSheet("font: 30pt;color:gray");
            }else {
                this->label_map[choose_point.y()][choose_point.x()]->setStyleSheet("font:30pt;");
            }
            //this->label_map[choose_point.y()][choose_point.x()]->setStyleSheet("font:30pt;");
            if(this->map_[(point.y()-dis_y)/r][(point.x()-dis_x)/r]!=0)return;
            this->choose_point.setX((point.x()-dis_x)/r);
            this->choose_point.setY((point.y()-dis_y)/r);
//            qDebug()<<this->choose_point;
            this->label_map[choose_point.y()][choose_point.x()]->setStyleSheet("font:30pt;background-color:rgb(237, 240, 200);");
            //this->label_map[choose_point.y()][choose_point.x()]->setText("");
        }
        else if(point.x()>=dis_x+10*r&&point.x()<=dis_x+11*r&&point.y()>=dis_y&&point.y()<=dis_y+9*r){
            if(map_[choose_point.y()][choose_point.x()]!=0)return;
            this->choose_val=(point.y()-dis_y)/r+1;
            //this->label_map[choose_point.y()][choose_point.x()]->setStyleSheet("font:30pt");
            this->label_map[choose_point.y()][choose_point.x()]->setText(QString::number(this->choose_val));
            this->map[choose_point.y()][choose_point.x()]=choose_val;
            //qDebug()<<choose_val;
        }
    }
    else if (event->button() == Qt::RightButton){
        //qDebug() << "right click";
        QPoint point=event->pos();
        if(point.x()>=dis_x&&point.x()<=dis_x+r*9&&point.y()>=dis_y&&point.y()<=dis_y+9*r){
            if(go==-1){
                this->carryOn();
            }

            if(this->map_[choose_point.y()][choose_point.x()]!=0){
                this->label_map[choose_point.y()][choose_point.x()]->setStyleSheet("font: 30pt;color:gray");
            }else {
                this->label_map[choose_point.y()][choose_point.x()]->setStyleSheet("font:30pt;");
            }
            //this->label_map[choose_point.y()][choose_point.x()]->setStyleSheet("font:30pt;");
            if(this->map_[(point.y()-dis_y)/r][(point.x()-dis_x)/r]!=0)return;
            this->choose_point.setX((point.x()-dis_x)/r);
            this->choose_point.setY((point.y()-dis_y)/r);
//            qDebug()<<this->choose_point;
            this->label_map[choose_point.y()][choose_point.x()]->setStyleSheet("font:30pt;background-color:rgb(237, 240, 200);");
            this->label_map[choose_point.y()][choose_point.x()]->setText("");
            this->map[choose_point.y()][choose_point.x()]=0;
        }
    }
}

bool MainWindow::init()
{
    this->ui->label->setText("00:00:00");
    this->map=new int*[9];
    this->map_=new int*[9];
    level=0;
    for(int i=0;i<9;++i){
        this->map[i]=new int[9]();
        this->map_[i]=new int[9]();
    }
    dis_x=30,dis_y=80;
    r=50;
    for(int i=0;i<9;i++){
        vector<QLabel*> temp;
        for(int j=0;j<9;j++){
            QLabel *label=new QLabel(this);
            label->setAlignment(Qt::AlignHCenter);
            label->setText("");
            label->setGeometry(dis_x/*+r/4*/+j*r+1,dis_y+i*r+1,r-2,r-2);
            label->setStyleSheet("font: 30pt;color:gray");
            temp.push_back(label);
        }
        this->label_map.push_back(temp);
    }
    for(int i=0;i<9;++i){
        QLabel *label=new QLabel(this);
        label->setText(QString::number(i+1,10,0));
        label->setAlignment(Qt::AlignHCenter);
        label->setGeometry(dis_x+10*r+1,dis_y+i*r+1,r-2,r-2);
        label->setStyleSheet("font: 27pt;color:black");
        this->label_val.push_back(label);
    }
    return true;
}

bool MainWindow::clear()
{
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            map[i][j]=0;
            this->label_map[i][j]->setText("");
        }
    }
//    for(int i=0;i<9;++i){
//        delete map[i];
//    }
//    delete map;
//    for(int i=0;i<9;++i){
//        for(int j=0;j<9;++j){
//            delete this->label_map[i][j];
//        }
//        delete this->label_val[i];
//    }
//    this->label_map.clear();
//    this->label_val.clear();
    return true;
}

bool MainWindow::newGame()
{
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            this->map_[i][j]=0;
        }
    }
    sudoku.createSudoku(this->map_,30);
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            map[i][j]=map_[i][j];
            if(map_[i][j]==0)continue;
            this->label_map[i][j]->setText(QString::number(map_[i][j]));
            this->label_map[i][j]->setStyleSheet("font: 30pt;color:gray");
        }
    }
    return true;
}

bool MainWindow::check_()
{
    int row[10]={0};
    int col[10]={0};
    int jiu[10]={0};
    for(int i=0;i<9;++i){
        memset(row,0,sizeof(row));
        memset(col,0,sizeof(col));
        memset(jiu,0,sizeof(jiu));
        for(int j=0;j<9;++j){
            if(!checkVal_(row,map[i][j])||!checkVal_(col,map[j][i])||!checkVal_(jiu,map[3*(i/3) + j/3][3*(i%3) + j%3])){
                return false;
            }
        }
    }
    return true;
}

bool MainWindow::checkVal_(int vec[], int val)
{
    if(val==0)return true;
    if(vec[val]==1)return false;
    vec[val]=1;
    return true;
}

bool MainWindow::finished()
{
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            if(map[i][j]==0)return false;
        }
    }
    return true;
}

void MainWindow::start()
{
    this->basetime=QTime::currentTime();
    this->ptimer->start(10);
    go=1;
}

void MainWindow::pause()
{
    pauseTime=QTime::currentTime();
    this->ptimer->stop();
    go=-1;
}

void MainWindow::carryOn()
{
    QTime cut=QTime::currentTime();
    int t=pauseTime.msecsTo(cut);
    this->basetime=this->basetime.addMSecs(t);
    this->ptimer->start(10);
    go=1;
}

void MainWindow::on_actionnew_game_triggered()
{
    this->clear();
    newGame();
    start();
}

void MainWindow::update_Time()
{
    QTime current=QTime::currentTime();
    int t=this->basetime.msecsTo(current);
    QTime showtime(0,0,0,0);
    showtime=showtime.addMSecs(t);
    QString showstr=showtime.toString("mm:ss:zzz");
    this->ui->label->setText(showstr.left(showstr.length()-1));
}

void MainWindow::on_btn_restart_clicked()
{
    this->clear();
    newGame();
    start();
}

void MainWindow::on_btn_clear_clicked()
{
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            if(this->map_[i][j]==0){
                this->map[i][j]=0;
                this->label_map[i][j]->setText("");
                this->label_map[i][j]->setStyleSheet("font:30pt");
            }
        }
    }
}

void MainWindow::on_btn_auto_clicked()
{
    int a[81],k=0;
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            a[k++]=this->map_[i][j];
        }
    }
    DanceLinked *p=new DanceLinked(a);
    p->getSolution(a);
    k=0;
    for(int i=0;i<9;++i){
        for(int j=0;j<9;++j){
            if(this->map_[i][j]==0){
                this->label_map[i][j]->setText(QString::number(a[k]));
                this->label_map[i][j]->setStyleSheet("font:30pt");
                this->map[i][j]=a[k];
            }
            k++;
        }
    }
    delete p;
}

void MainWindow::on_btn_submit_clicked()
{
    if(!finished()){
        QMessageBox::information(this,"haven't finished","Please continue");return;
    }
    if(check_()){
        this->pause();
        int ret=QMessageBox::question(this,"Success","Next level?","Yes","Quit","Cancel");
        if(ret==1){
            this->close();
        }
        else if(ret==0){
            this->on_btn_restart_clicked();
            this->ui->level->setText("level "+QString::number(++level));
        }
    }else {
        int ret=QMessageBox::question(this,"Failed","Again?","Yes","Quit","Cancel");
        if(ret==0){
            this->on_btn_clear_clicked();start();
        }else if(ret==1){
            this->close();
        }
    }
}

void MainWindow::on_btn_pause_clicked()
{
    if(go==1){
        this->pause();
    }
}
