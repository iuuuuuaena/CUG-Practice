#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "changeproblem.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::readfromfile(){
    QString str=this->ui->le_in->text();
    QFile file(str);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
       { return -1;}
    QTextStream in(&file);
//    while(!in.atEnd()){
//        line=in.readLine();
//    }
    n=in.readLine().toInt();
    t=new int[n+1];
    coins=new int[n+1];
    for (int i = 1; i<n + 1; i++){
            in >> t[i] >> coins[i];
    }
    in>>m;
    file.close();
    return 0;
}

void MainWindow::writetofile(QString record)
{
    QString str=this->ui->le_out->text();
    QFile file(str);
    if(!file.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败","确定");
        return;
    }
    QTextStream out(&file);
    out<<record;
    file.close();
}
void MainWindow::on_btn_choose_clicked()
{
    if(readfromfile()==-1)
    {
        QMessageBox::critical(this,"error","failed open file");
    };
}

void MainWindow::on_btn_ok_clicked()
{
    ChangeProblem *p=new ChangeProblem(n,t,coins,m);
    p->calculate();
    int count=p->getcount();
    writetofile(QString::number(count));
    delete p;
    p=NULL;
}
