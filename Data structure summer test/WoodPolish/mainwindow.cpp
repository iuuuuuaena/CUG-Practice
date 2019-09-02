#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    records="";
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
    in>>t;
    n=new int[t];
    a=new wood[t][5001];
    for(int i=0;i<t;i++){
        in>>n[i];
        for(int j=0;j<n[i];j++){
            in>>a[i][j].l>>a[i][j].wei;
        }
    }
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
    for(int i=0;i<t;i++){
        WoodPolish *p=new WoodPolish(n[i],a[i]);
        p->calculate();
        records+=p->getrecord();
    }
    writetofile(records);
}
