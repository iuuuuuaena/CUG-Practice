#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->progressBar->setValue(0);
    newPress=NULL;
    ui->progressBar->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete newPress;
    delete ui;
}

void MainWindow::on_btn_Compression_clicked()
{
    fileName=QFileDialog::getOpenFileName(this,tr("open file"));
    //qDebug()<<fileName;
    if(fileName.isEmpty()){
        QMessageBox::critical(this,"error","请选择一个文件.","ok");
        return;
    }this->ui->progressBar->setValue(0);
    if(newPress!=NULL)delete newPress;newPress=NULL;
    newPress=new HuffCode(fileName.toStdString(),this->ui->progressBar);
    if(newPress->Coding()){
        QMessageBox::information(this, "succeed", "压缩完成.");fileName.clear();
    }
}

void MainWindow::on_btn_Decompression_clicked()
{
    fileName=QFileDialog::getOpenFileName(this,tr("open file"));
    if(fileName.isEmpty()){
        QMessageBox::critical(this,"error","请选择一个文件.","ok");
        return;
    }this->ui->progressBar->setValue(0);
    QString temp=fileName.right(4);
    if(temp!=".haf"){
        QMessageBox::critical(this,"error","请选择一个被压缩过的文件(.haf).","ok");
        return;
    }
    if(newPress)delete newPress;newPress=NULL;
    newPress=new HuffCode(fileName.toStdString(),this->ui->progressBar);
    if(newPress->Decoding()){
        QMessageBox::information(this, "succeed", "解压完成.");fileName.clear();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e){
//    if(e->mimeData()->hasFormat("text/url-list")){
        e->acceptProposedAction();
//    }
//    else{
//        QMessageBox::critical(this,"error","请拖入文件.","ok");
//    }
}

void MainWindow::dropEvent(QDropEvent *e){
    QList<QUrl> urls=e->mimeData()->urls();
    if(urls.isEmpty()){
        return;
    }
    int n=urls.length();
    for(int i=0;i<n;i++){
        fileName=urls[i].toLocalFile();
        if(fileName.isEmpty()){
            QMessageBox::critical(this,"error","请选择一个文件.","ok");
            return;
        }
        if(fileName.right(4)!=".haf"){
            this->ui->progressBar->setValue(0);
            if(newPress!=NULL)delete newPress;newPress=NULL;
            newPress=new HuffCode(fileName.toStdString(),this->ui->progressBar);
            if(newPress->Coding()){
                QMessageBox::information(this, "succeed", "压缩完成.");fileName.clear();
            }
        }
        else {
            this->ui->progressBar->setValue(0);
            if(newPress)delete newPress;newPress=NULL;
            newPress=new HuffCode(fileName.toStdString(),this->ui->progressBar);
            if(newPress->Decoding()){
                QMessageBox::information(this, "succeed", "解压完成.");fileName.clear();
            }
        }
    }
}
