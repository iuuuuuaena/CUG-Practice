#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtMath>
#include<QDebug>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(560,360);
    this->ui->btn_ok->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::QcharToInt(QChar c){
    if(c=='0')return 0;
    if(c=='1')return 1;
    else {
        return -1;
    }
}

void MainWindow::on_btn_ok_clicked()
{
    QString str=this->ui->le_input->text();
//    if(str.length()!=32){
//        QMessageBox::critical(this,"error","please input 32 bit","ok");
//        return;
//    }
    int e=0;
    for(int i=1;i<=8;i++){
        e+=QcharToInt(str[i])*qPow(2,8-i);
    }
    double s=0;
    for(int i=9;i<=32;i++){
        s+=QcharToInt(str[i])*qPow(2,8-i);
        }
    if(0==e){
        if(isZero(str)){
            this->ui->label->setText("0");
        }
        else {
            double result=s*qPow(2,-126);
            if(str[0]=='1'){result=-result;}
            QString res=QString::number(result);
            QString r;
            for(int i=0;i<res.length();i++){
                if(res[i]=='e'){
                    r.append("*10^");
                }
                else {
                    r.append(res[i]);
                }
            }
            this->ui->label->setText(r);
        }
        return;
    }
    if(255==e){
        if(isZero(str)){
            if(str[0]=='0'){
                this->ui->label->setText("+无穷");
            }
            else {
                this->ui->label->setText("-无穷");
            }
        }
        else {
            this->ui->label->setText("NaN");
        }
        return;
    }
    s+=1;
    e-=127;
    double result=s*qPow(2,e);
    if(str[0]=='1'){result=-result;}
    QString res=QString::number(result);
    QString r;
    for(int i=0;i<res.length();i++){
        if(res[i]=='e'){
            r.append("*10^");
        }
        else {
            r.append(res[i]);
        }
    }
    this->ui->label->setText(r);
    return;
}

void MainWindow::on_le_input_textEdited(const QString &arg1)
{
    QString str=arg1;
    int j=0;
    for(int i=0;i<arg1.length();i++){
        if(arg1[i]!='0'&&arg1[i]!='1'){
            str.remove(i-j,1);
            j++;
        }
    }
    this->ui->le_input->setText(str);
    if(j){
        QMessageBox::critical(this,"error","only '0' and '1' are allowed","ok");
    }
    if(str.length()==32){
        this->ui->btn_ok->setEnabled(true);
    }else {
        this->ui->btn_ok->setEnabled(false);
    }
}

bool MainWindow::isZero(QString str){
    for(int i=9;i<=32;i++){
        if(str[i]=='1')return false;
    }
    return true;
}

//void MainWindow::on_le_input_editingFinished()
//{
//    QString str=this->ui->le_input->text();
//    if(str.length()!=32){
//        QMessageBox::critical(this,"error","please input 32 bit","ok");
//    }
//}
