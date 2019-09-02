#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->model=new QStandardItemModel;
    this->model->setHorizontalHeaderItem(0,new QStandardItem("ID"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("Gender"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("Birthday"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("Enrollment date"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("Enrollment age"));
    this->ui->tableView->setModel(model);
    this->ui->tableView->setColumnWidth(0,100);
    this->ui->tableView->setColumnWidth(1,100);
    this->ui->tableView->setColumnWidth(2,140);
    this->ui->tableView->setColumnWidth(3,140);
    this->ui->tableView->setColumnWidth(4,140);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::readfromfile()
{
    QString str=this->ui->le_input->text();
    QFile file(str);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
       { return -1;}
    QTextStream in(&file);
    while(!in.atEnd()){
        QString line=in.readLine();
        records.append(line);
    }
    file.close();
//    for(int i=0;i<records.length();i++){
//        qDebug()<<records.at(i);
//    }
    return 0;
}
void MainWindow::on_btn_open_clicked()
{
    this->records.clear();
    if(readfromfile()==-1)
    {
        QMessageBox::critical(this,"error","failed open file");
    };
    this->model->clear();
    this->ui->tableView->setModel(model);
    this->model->setHorizontalHeaderItem(0,new QStandardItem("ID"));
    this->model->setHorizontalHeaderItem(1,new QStandardItem("Gender"));
    this->model->setHorizontalHeaderItem(2,new QStandardItem("Birthday"));
    this->model->setHorizontalHeaderItem(3,new QStandardItem("Enrollment date"));
    this->model->setHorizontalHeaderItem(4,new QStandardItem("Enrollment age"));
    this->ui->tableView->setModel(model);
    this->ui->tableView->setColumnWidth(0,100);
    this->ui->tableView->setColumnWidth(1,100);
    this->ui->tableView->setColumnWidth(2,140);
    this->ui->tableView->setColumnWidth(3,140);
    this->ui->tableView->setColumnWidth(4,140);
    int i=0;
    int row=0;
    for(i=0;i<records.length();i++)
    {
        QString line=records.at(i);
        line=line.trimmed();
        QStringList subs=line.split(" ");
        display(row++,subs);
    }
}

void MainWindow::display(int row, QStringList subs)
{
    int i=0;
    for(i;i<4;i++){
        this->model->setItem(row,i,new QStandardItem(subs.at(i)));
    }
}

void MainWindow::on_btn_cancel_clicked()
{
    this->close();
}

void MainWindow::on_btn_ok_clicked()
{
    if(records.length()==0)
    {
        QMessageBox::critical(this,"文件未打开","请先打开文件","确定");
    }
    QFile file("out.csv");
    file.open(QFile::WriteOnly|QFile::Truncate);
        file.close();
    for(int i=0;i<records.length();i++)
    {
        QString line=records.at(i);
        line=line.trimmed();
        QStringList subs=line.split(" ");
        QString Birthday=subs.at(2);
        QString Enrollmentdate=subs.at(3);
        QStringList birthday=Birthday.split("/");
        QStringList enrollmentdate=Enrollmentdate.split("/");
        QString b1=birthday.at(0);
        double db1=b1.toDouble();
        QString b2=birthday.at(1);
        double db2=b2.toDouble();
        QString b3=birthday.at(2);
        double db3=b3.toDouble();
        double b=db1+db2/12+db3/365;
        QString e1=enrollmentdate.at(0);
        double de1=e1.toDouble();
        QString e2=enrollmentdate.at(1);
        double de2=e2.toDouble();
        QString e3=enrollmentdate.at(2);
        double de3=e3.toDouble();
        double e=de1+de2/12+de3/365;
        double enrollmentage=e-b;
        enrollmentage = double((int)(enrollmentage*100))/100.0;
        QString Enrollmentage=QString::number(enrollmentage);
        this->model->setItem(i,4,new QStandardItem(Enrollmentage));
        QString record=line+" "+Enrollmentage+'\n';
        writetofile(record);
    }
}
void MainWindow::writetofile(QString record)
{
    QFile file("out.csv");
    if(!file.open(QIODevice::Append|QIODevice::Text))
    {
        QMessageBox::critical(this,"错误","文件打开失败","确定");
        return;
    }
    QTextStream out(&file);
    out<<record;
    file.close();
}
