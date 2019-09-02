#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->exp.clear();
    this->ui->le->setText("0");
    this->clipboard=QApplication::clipboard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clear()
{
    this->exp.clear();
    this->ui->le->setText("0");
}
void MainWindow::on_btn_clear_clicked()
{
    this->clear();
}

void MainWindow::on_btn_0_clicked()
{
    this->exp+="0";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_point_clicked()
{
    this->exp+=".";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_1_clicked()
{
    this->exp+="1";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_2_clicked()
{
    this->exp+="2";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_3_clicked()
{
    this->exp+="3";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_plus_clicked()
{
    this->exp+="+";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_4_clicked()
{
    this->exp+="4";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_5_clicked()
{
    this->exp+="5";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_6_clicked()
{
    this->exp+="6";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_minus_clicked()
{
    this->exp+="-";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_7_clicked()
{
    this->exp+="7";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_8_clicked()
{
    this->exp+="8";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_9_clicked()
{
    this->exp+="9";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_time_clicked()
{
    this->exp+="*";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_left_clicked()
{
    this->exp+="(";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_right_clicked()
{
    this->exp+=")";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_mod_clicked()
{
    this->exp+="%";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_divide_clicked()
{
    this->exp+="/";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_sin_clicked()
{
    this->exp+="sin";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_cos_clicked()
{
    this->exp+="cos";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_tan_clicked()
{
    this->exp+="tan";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_ln_clicked()
{
    this->exp+="ln";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_Log_clicked()
{
    this->exp+="Log";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_Sqrt_clicked()
{
    this->exp+="Sqrt";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_pow_clicked()
{
    this->exp+="^";
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_delete_clicked()
{
    this->exp.remove(exp.length()-1,1);
    this->ui->le->setText(exp);
}

void MainWindow::on_btn_res_clicked()
{
    exp=this->ui->le->text();
    if(!this->bracketMatch()){
        QMessageBox::critical(NULL,"error","bracket is not matching!","OK");
        //this->clear();
        return;
    }
    cal *newexp=new cal(exp);
    double res;
    if(newexp->calculate(res)){
        QString result=exp+"="+QString::number(res);
        this->ui->le->setText(result);
    }
    else {
        QMessageBox::critical(NULL,"error","input error!","OK");
        this->clear();
    }
    exp.clear();
    delete newexp;
}

void MainWindow::on_action_triggered()
{
    exp=clipboard->text();
    this->ui->le->setText(exp);
}

void MainWindow::on_actioncopy_triggered()
{
    exp=this->ui->le->text();
    clipboard->setText(exp);
}

bool MainWindow::bracketMatch(){
    QByteArray temp=exp.toLocal8Bit();
    LinkedStack<char> bracket;
    for(int i=0;i<temp.length();i++){
        if(temp[i]=='('){
            bracket.Push('(');
        }
        else if (temp[i]==')') {
            if(bracket.IsEmpty()||bracket.Top()!='('){return false;}
            else bracket.Pop();
        }
        else continue;
    }
    if(!bracket.IsEmpty()){return false;}
    else {
        return true;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return){
        this->on_btn_res_clicked();
    }
}
