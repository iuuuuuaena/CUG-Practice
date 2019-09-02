#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->setFixedSize(823,589);
    this->setWindowIcon(QIcon(":/1.ico"));
    tree=NULL;
    tts = new QTextToSpeech(this);
    this->Init();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::Init(){
    tree=new AVLTree;
    QFile file(":/Words.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
       { QMessageBox::critical(this,"error","failed open file","OK");return false;}
    QTextStream in(&file);
    QString line1,line2;
    while(!in.atEnd()){
        line1=in.readLine();
        line2=in.readLine();
        WordNode WN(line1,line2);
        this->tree->Insert(WN);
    }
    file.close();
    return true;
}
void MainWindow::on_btn_search_clicked()
{
    QString str=this->ui->le_input->text();
    if(str.isEmpty()){
        QMessageBox::critical(this,"error","input empty","OK");return;
    }
    this->WordList.clear();
    disconnect(ui->listWidget,SIGNAL(itemSelectionChanged()),this,SLOT(on_listWidget_itemSelectionChanged()));
    this->ui->listWidget->clear();
    connect(ui->listWidget,SIGNAL(itemSelectionChanged()),this,SLOT(on_listWidget_itemSelectionChanged()));
    WordList=tree->BlurrySearch(str);
    for(auto node:WordList){
        this->ui->listWidget->addItem(node.key);
    }
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    int i=this->ui->listWidget->currentRow();

    //历史纪录
    if(this->History.size()==10)History.pop_front();
    this->History.push_back(WordList.at(i));
    this->ui->lw_history->clear();
    for(auto iter=History.begin();iter!=History.end();iter++){
        this->ui->lw_history->addItem(iter->key);
    }
    this->word=WordList.at(i).key;
    QString str=this->WordList.at(i).key;
    str+='\n'+this->WordList.at(i).description;
    this->ui->textBrowser->setText(str);
}

void MainWindow::on_btn_delete_clicked()
{
    WordNode temp;
    if(word.isEmpty()){
        QMessageBox::critical(this,"error","failed delete","OK");return;
    }
    if(this->tree->Remove(word,temp)){
        QMessageBox::information(this,"OK","succeed delete");return;
    }
    QMessageBox::critical(this,"error","failed delete","OK");
}

void MainWindow::on_lw_history_itemSelectionChanged()
{
    int i=this->ui->lw_history->currentRow();
    auto iter=History.begin();
    while (i--) {
        iter++;
    }
    QString str=iter->key;
    this->word=str;
    str+='\n'+iter->description;
    this->ui->textBrowser->setText(str);
}

void MainWindow::on_btn_all_clicked()
{
    this->WordList.clear();
    disconnect(ui->listWidget,SIGNAL(itemSelectionChanged()),this,SLOT(on_listWidget_itemSelectionChanged()));
    this->ui->listWidget->clear();
    connect(ui->listWidget,SIGNAL(itemSelectionChanged()),this,SLOT(on_listWidget_itemSelectionChanged()));
    WordList=tree->BlurrySearch("");
    for(auto node:WordList){
        this->ui->listWidget->addItem(node.key);
    }
}

void MainWindow::on_btn_alter_clicked()
{
    QString str=this->ui->te_alter->toPlainText();
    if(str.isEmpty()){
        QMessageBox::critical(this,"error","failed alter","OK");return;
    }
    this->tree->Search(this->word)->data.description=str;
    //qDebug()<<this->tree->Search(this->word)->data.description;
    QMessageBox::information(this,"OK","succeed alter");
}

void MainWindow::on_btn_add_clicked()
{
    QString key=this->ui->le_add->text();
    QString des=this->ui->te_add->toPlainText();
    if(key.isEmpty()||des.isEmpty()){
        QMessageBox::critical(this,"error","failed add","OK");return;
    }
    WordNode temp(key,des);
    if(this->tree->Insert(temp)){
        QMessageBox::information(this,"OK","succeed add");return;
    }
    QMessageBox::critical(this,"error","Duplicate words","OK");
}

void MainWindow::on_btn_audio_clicked()
{
    tts->stop();
    if(tts->state()==QTextToSpeech::Ready)
    {
        tts->say(this->word);
    }

}
void MainWindow::on_action_triggered()//导入
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("选择要导入的文件"));
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
       { QMessageBox::critical(this,"error","failed open file","OK");return;}
    QTextStream in(&file);
    if(tree!=NULL){
        delete tree;
        tree=NULL;
    }
    tree=new AVLTree;
    QString line1,line2;
    while(!in.atEnd()){
        line1=in.readLine();
        line2=in.readLine();
        WordNode WN(line1,line2);
        this->tree->Insert(WN);
    }
    file.close();
    QMessageBox::information(this,"OK","succeed Import");
}

void MainWindow::on_action_2_triggered()//导出
{
    if(tree==NULL){
        QMessageBox::critical(this,"error","tree is NULL","OK");
    }
    //QString fileName=QFileDialog::getOpenFileName(this,tr("选择要导出的文件"));
    QString fileName=QFileDialog::getSaveFileName(this,tr("TXT File"),qApp->applicationDirPath(),tr("Files (*.txt)"));
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
       { QMessageBox::critical(this,"error","failed create file","OK");return;}
    QTextStream out(&file);
    tree->Export(out);
    QMessageBox::information(this,"OK","succeed Export");
}
