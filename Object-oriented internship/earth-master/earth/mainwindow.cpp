#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <earth.h>
#include <QMessageBox>
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

void MainWindow::on_show_clicked()
{
    QString a1=this->ui->le_jdd1->text();
    QString b1=this->ui->le_jdf1->text();
    QString c1=this->ui->le_jdm1->text();
    QString d1=this->ui->le_wdd1->text();
    QString e1=this->ui->le_wdf1->text();
    QString f1=this->ui->le_wdm1->text();
    QString g1=this->ui->le_jdd2->text();
    QString h1=this->ui->le_jdf2->text();
    QString i1=this->ui->le_jdm2->text();
    QString j1=this->ui->le_wdd2->text();
    QString k1=this->ui->le_wdf2->text();
    QString l1=this->ui->le_wdm2->text();
    double a=a1.toDouble();
    double b=b1.toDouble();
    double c=c1.toDouble();
    double d=d1.toDouble();
    double e=e1.toDouble();
    double f=f1.toDouble();
    double g=g1.toDouble();
    double h=h1.toDouble();
    double i=i1.toDouble();
    double j=j1.toDouble();
    double k=k1.toDouble();
    double l=l1.toDouble();
    earth earth1(a,b,c,d,e,f,g,h,i,j,k,l);
    if(earth1.check())
    {double dis=earth1.dis();
    QString tex=QString::number(dis);
    this->ui->le_show->setText(tex);}
    else {
        QMessageBox::warning(this,"输入错误.","请重新输入正确的经纬度.","ok");
        this->ui->le_jdd1->setText("");
        this->ui->le_jdf1->setText("");
        this->ui->le_jdm1->setText("");
        this->ui->le_wdd1->setText("");
        this->ui->le_wdf1->setText("");
        this->ui->le_wdm1->setText("");
        this->ui->le_jdd2->setText("");
        this->ui->le_jdf2->setText("");
        this->ui->le_jdm2->setText("");
        this->ui->le_wdd2->setText("");
        this->ui->le_wdf2->setText("");
        this->ui->le_wdm2->setText("");
        this->ui->le_show->setText("");
    }
}

void MainWindow::on_clear_clicked()
{
    this->ui->le_jdd1->setText("");
    this->ui->le_jdf1->setText("");
    this->ui->le_jdm1->setText("");
    this->ui->le_wdd1->setText("");
    this->ui->le_wdf1->setText("");
    this->ui->le_wdm1->setText("");
    this->ui->le_jdd2->setText("");
    this->ui->le_jdf2->setText("");
    this->ui->le_jdm2->setText("");
    this->ui->le_wdd2->setText("");
    this->ui->le_wdf2->setText("");
    this->ui->le_wdm2->setText("");
    this->ui->le_show->setText("");
}
