#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    this->setWindowTitle("ImageCompression");
    this->ui->btn_Decompression->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_Compression_clicked()
{
    fileName=QFileDialog::getOpenFileName(this,tr("open file"));
    //qDebug()<<fileName;
    if(fileName.isEmpty()){
        //QMessageBox::critical(this,"error","请选择一个文件.","ok");
        return;
    }
    if(fileName.right(4)==".bmp"){
        double start=(double)clock();
        GrayImage *img=new GrayImage(fileName.toStdString());
        if(img->Compress()){
            //img->print();
            double end=(double)clock();
            QMessageBox::information(this, "succeed", "压缩完成,用时"+QString::number(end-start,10,2)+"ms.");fileName.clear();
        }
        return;
    }
    if(fileName.right(4)==".img"){
        double start=(double)clock();
        GrayImage *img=new GrayImage(fileName.toStdString());
        if(img->UnCompress()){
            double end=(double)clock();
            QMessageBox::information(this, "succeed", "解压完成,用时"+QString::number(end-start,10,2)+"ms.");fileName.clear();
        }
        return;
    }
    QMessageBox::critical(this,"error","请选择一个bmp/img文件.","ok");
}

void MainWindow::on_btn_Decompression_clicked()
{
    fileName=QFileDialog::getOpenFileName(this,tr("open file"));
    if(fileName.isEmpty()){
        //QMessageBox::critical(this,"error","请选择一个文件.","ok");
        return;
    }
    GrayImage *img=new GrayImage(fileName.toStdString());
    if(img->UnCompress()){
        QMessageBox::information(this, "succeed", "解压完成.");fileName.clear();
    }
}
void MainWindow::dragEnterEvent(QDragEnterEvent *e){
      e->acceptProposedAction();
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
        if(fileName.right(4)!=".img"){//解压
            GrayImage *img=new GrayImage(fileName.toStdString());
            if(img->UnCompress()){
                QMessageBox::information(this, "succeed", "解压完成.");fileName.clear();
            }
        }
        else if(fileName.right(4)!=".bmp"){//压缩
            GrayImage *img=new GrayImage(fileName.toStdString());
            if(img->Compress()){
                QMessageBox::information(this, "succeed", "压缩完成.");fileName.clear();
            }
        }
    }
}
