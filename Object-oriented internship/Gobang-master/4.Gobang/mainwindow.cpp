#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->xPressed = 0;
    this->yPressed = 0;
    this->numCounts = 0;
    for(int i=0;i<19;i++)
    {
        for(int j=0;j<19;j++)
        {
            map[i][j] = 0;
        }
    }
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);
    //画线
    for(int i=50;i<1000;)
    {
        QPoint pointOne(50,i);
        QPoint pointTwo(950,i);
        painter.drawLine(pointOne,pointTwo);
        i = i + 50;
    }
    for(int i=50;i<1000;)
    {
        QPoint pointOne(i,50);
        QPoint pointTwo(i,950);
        painter.drawLine(pointOne,pointTwo);
        i = i + 50;
    }
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    for(int i=0;i<this->numCounts;i++)
    {
        if(i%2 == 0)
        {
            brush.setColor(Qt::black);
        }
        else
        {
            brush.setColor(Qt::white);
        }
        painter.setBrush(brush);
        painter.drawEllipse(this->counts[i][0]-20,this->counts[i][1]-20,40,40);
    }
}
void MainWindow::mousePressEvent(QMouseEvent *mouseEvent)
{

    int x = int(float(mouseEvent->x())/50+0.5)*50;
    int y = int(float(mouseEvent->y())/50+0.5)*50;


    //按下的位置在棋盘内
    if(x>0&&x<1000&&y>0&&y<1000&&this->map[y/50-1][x/50-1]==0)//当前按键位置在棋盘内并且当前位置没有棋子
    {
        QSound::play("E:\\素材\\下棋音效.wav");
        this->numCounts += 1;//棋子数目加一
        if(this->numCounts%2 != 0)//棋局矩阵构造
        {
            this->map[y/50-1][x/50-1] = 1; //1表示黑色
        }
        else
        {
            this->map[y/50-1][x/50-1] = -1;//-1表示白色
        }
        this->counts[this->numCounts-1][0] = x;
        this->counts[this->numCounts-1][1] = y;
        this->counts[this->numCounts-1][2] = this->numCounts%2;
        this->update();      //用于绘图
        checkWin(x,y);
    }

}

void MainWindow::checkWin(int x,int y)
{
    int row = y/50-1; //显示第几行
    int col = x/50-1; //显示第几列
    int colorCenter = this->map[row][col];//中间点的颜色
    int total = 1;
        int i,j;
        for(i = row-1; i >= 0; i--)//统计同行左侧连续同样棋子个数。
            if(map[i][col]==map[row][col]) total++;
            else break;
        for(i = row+1; i < 19; i++)//统计同行右侧连续同样棋子个数。
            if(map[i][col] == map[row][col]) total++;
            else break;
        if(total>=5) { winShow(colorCenter);return;}
        total = 1;
        for(i = col-1; i >= 0; i--)//统计同列上侧连续同样棋子个数。
            if(map[row][i]==map[row][col]) total++;
            else break;
        for(i = col+1; i < 19; i++)//统计同列下侧连续同样棋子个数。
            if(map[row][i] == map[row][col]) total++;
            else break;
        if(total>=5) { winShow(colorCenter);return;}
        total=1;
        for(i=row-1,j=col-1;i>=0,j>=0;i--,j--)//判断\方向左上方连续同样棋子个数
            if(map[i][j] == map[row][col]) total++;
            else break;
        for(i=row+1,j=col+1;i<=19,j<=19;i++,j++)//判断\方向右下方连续同样棋子个数
            if(map[i][j] == map[row][col]) total++;
            else break;
        if(total>=5) { winShow(colorCenter);return;}
        total=1;
        for(i=row-1,j=col+1;i>=0,j<=19;i--,j++)//判断/方向右上方连续同样棋子个数
            if(map[i][j] == map[row][col]) total++;
            else break;
        for(i=row+1,j=col-1;i<=19,j>=0;i++,j--)//判断/方向左下方连续同样棋子个数
            if(map[i][j] == map[row][col]) total++;
            else break;
        if(total>=5) { winShow(colorCenter);return;}
        if(this->numCounts==361)
        {
            tie();
        }



}
void MainWindow::winShow(int colorCenter)
{
    QString infoShow;
    if(colorCenter == 1)//中心点是黑色
    {
        infoShow = "黑棋赢!";
    }
    else if(colorCenter == -1)
    {
        infoShow = "白棋赢!";
    }
    if(QMessageBox::information(NULL,"Game Over",infoShow,"Again","Exit")==1)
    {
        close();
    }
    else for(int i=0;i<19;i++)//清空棋盘
    {
        for(int j=0;j<19;j++)
        {
            this->map[i][j]=0;
        }
    }
    this->numCounts = 0;//下子数目为0，即下一个子从黑子开始
}

void MainWindow::tie()
{
    QString Tie="和局";
    if(QMessageBox::information(NULL,"Game Over",Tie,"Again","Exit")==1)
    {
        close();
    }
    else for(int i=0;i<19;i++)//清空棋盘
    {
        for(int j=0;j<19;j++)
        {
            this->map[i][j]=0;
        }
    }
    this->numCounts = 0;//下子数目为0，即下一个子从黑子开始
}




void MainWindow::on_action_triggered()
{
    for(int i=0;i<19;i++)//清空棋盘
        {
            for(int j=0;j<19;j++)
            {
                this->map[i][j]=0;
            }
        }
        this->numCounts = 0;
    this->update();
}
