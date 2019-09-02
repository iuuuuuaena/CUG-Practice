#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    while(!in.atEnd()){
        line=in.readLine();
    }
    file.close();
    //qDebug()<<line;
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
    char *ch;
    QByteArray ba=line.toLatin1();
    ch=ba.data();
    //qDebug()<<ch;
    StringDecomposition *str1=new StringDecomposition(ch);
    str1->calculate();
    int *record=str1->get();
    int length=str1->getlength();
    QString qstr=QString::number(length,10)+'\n';
    for(int i=0;i<length;i++){
        qstr+=(QString::number(record[i],10)+'\n');
    }
    writetofile(qstr);
}
