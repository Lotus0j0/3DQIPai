#include "wuziqibendiduiju.h"
#include "wuziqibendimoshiduijugameover.h"

WuZiQiBenDiDuiJu::WuZiQiBenDiDuiJu()
{   
    int xwindow=MARGIN*2+GRID_SIZE*(BOARD_SIZE-1);
    int ywindow=MARGIN*2+GRID_SIZE*(BOARD_SIZE-1);


    //qInfo()<<"[init]五子棋窗口初始化.宽:"<<xwindow<<"高:"<<ywindow;//控制台显示

    this->resize(xwindow,ywindow);
    this->setWindowTitle("本地五子棋");

    m_board.assign(BOARD_SIZE,std::vector<int>(BOARD_SIZE,0));
}

// 绘制棋盘和棋子
void WuZiQiBenDiDuiJu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //绘制背景
    painter.fillRect(rect(),QColor(230,190,130));

    //设置画笔:黑色，1像素宽
    painter.setPen(QPen(Qt::black,1));

    //绘制网格线
        for(int i=0;i<BOARD_SIZE;i++){
            //起点的X, 起点的Y, 终点的X, 终点的Y
            //左上角是原点 (0,0)，X轴向右递增，Y轴向下递增
       painter.drawLine(MARGIN,MARGIN+i*GRID_SIZE,MARGIN+GRID_SIZE*(BOARD_SIZE-1),MARGIN+i*GRID_SIZE);
       painter.drawLine(MARGIN+i*GRID_SIZE,MARGIN,MARGIN+i*GRID_SIZE,MARGIN+GRID_SIZE*(BOARD_SIZE-1));
        }

        //绘制棋子
    for(int row=0;row<BOARD_SIZE;row++){
        for(int col=0;col<BOARD_SIZE;col++){
            if(m_board[row][col]==0)continue;

            //1.计算交叉点的屏幕坐标
            //qreal == double

            //cx 由列决定
            qreal cx=MARGIN+col*GRID_SIZE;
            //cy 由行决定
            qreal cy=MARGIN+row*GRID_SIZE;

            //计算棋子半径
            qreal radius=GRID_SIZE*0.4;

            //根据颜色绘制带立体感的棋子

            //保存当前画笔状态
            painter.save();

            //去除边框
            painter.setPen(Qt::NoPen);
            //黑棋
            if(m_board[row][col]==1){
                //QRadialGradient(焦点x,焦点y,半径); 确认渐变中心点为棋子的左上
                QRadialGradient gradient(cx-radius*0.3,cy-radius*0.3,radius);
                //渐变起点
                gradient.setColorAt(0,QColor(120,120,120));//高光点(亮灰)
                //渐变终点
                gradient.setColorAt(1,QColor(0,0,0));//边缘(纯黑)
                //塞给画笔函数
                painter.setBrush(gradient);
            }
            //白棋
            else if(m_board[row][col]==2){
                QRadialGradient gradient(cx-radius*0.3,cy-radius*0.3,radius);
                gradient.setColorAt(0,QColor(255,255,255));//高光点(亮灰)
                gradient.setColorAt(1,QColor(200,200,200));//边缘(浅灰)
                painter.setBrush(gradient);
            }
            //画圆
            painter.drawEllipse(QPointF(cx,cy),radius,radius);

            //恢复到保存前的状态 brush和line不重复
            painter.restore();

        }
    }
    }

//鼠标点击事件
void WuZiQiBenDiDuiJu::mousePressEvent(QMouseEvent *event){

    if(IsGameOver)return;

    //如果游戏已经结束,点击鼠标左键重新开始
    if(IsGameOver){
        if(event->button()==Qt::LeftButton){
            ResetGame();
        }
        return;
    }

    //如果不是鼠标左键点击，忽略
    if(event->button()!=Qt::LeftButton){
        return;
    }

    //获取鼠标点击的x,y坐标
    int x=event->pos().x();
    int y=event->pos().y();

    int row;//行
    int col;//列

    //确认棋子位置
    //算的行
    if((y-MARGIN)%GRID_SIZE>=GRID_SIZE*0.5){
        row=((y-MARGIN)/GRID_SIZE)+1;
    }else{
        row=(y-MARGIN)/GRID_SIZE;
    }
    //算的列
    if((x-MARGIN)%GRID_SIZE>=GRID_SIZE*0.5){
       col=((x-MARGIN)/GRID_SIZE+1);
    }else{
       col=(x-MARGIN)/GRID_SIZE;
    }
    // 使用 qRound 直接进行四舍五入（需要包含 <QtMath> 或者 <cmath>，不过 Qt 里通常自带）
//    int row = qRound((qreal)(x - MARGIN) / GRID_SIZE);
//    int col = qRound((qreal)(y - MARGIN) / GRID_SIZE);

    SaveData(row,col);
}


//边界检查与空位检查 0表示第一颗棋子位置
//存储棋子位置数据 切换玩家
void WuZiQiBenDiDuiJu::SaveData(int row,int col){
    //防呆设计
    if (IsGameOver) {
           return;
       }
    //边界检查
if(row>=0&&row<BOARD_SIZE&&col>=0&&col<BOARD_SIZE){
    //检查该交叉点是否有棋子(0表示空)
    if(m_board[row][col]==0){
        //落子并更新状态
        m_board[row][col]=CurrentPlayer;//记录当前玩家落子

        //重绘
        update();

        //获胜逻辑
        int Win_Or_Lose=CheckWin(row,col,CurrentPlayer);
        if(Win_Or_Lose==1){
            IsGameOver=true;

            //定时器(延时时间，绑定窗口，定时器响的时候执行代码[this](){});)
            QTimer::singleShot(1000,this,[this](){

            wuziqibendimoshiduijugameover* gameover=new wuziqibendimoshiduijugameover(CurrentPlayer,this);
            gameover->setAttribute(Qt::WA_DeleteOnClose);

            gameover->show();
            this->hide();

        });
}
        if(Win_Or_Lose==2){
            int Tempisdrawdata=3;
            IsGameOver=true;

            //定时器(延时时间，绑定窗口，定时器响的时候执行代码[this](){});)
            QTimer::singleShot(1000,this,[=](){

            wuziqibendimoshiduijugameover* gameover=new wuziqibendimoshiduijugameover(Tempisdrawdata,this);
            gameover->setAttribute(Qt::WA_DeleteOnClose);

            gameover->show();
            this->hide();
            });

            return;

        }
        //切换玩家
        CurrentPlayer=(CurrentPlayer==1)?2:1;

}
}
}

//判断获胜逻辑   判断每个刚下的棋子横，纵，对角线是否连成
int WuZiQiBenDiDuiJu::CheckWin(int row, int col, int player)
{
    //棋盘棋子下满时仍未结束
    int Tempisdrawdata=isdraw();
    if(Tempisdrawdata==2){
        return Tempisdrawdata;
    }

    //定义4个方向的增量:水平、垂直、主对角线(\)、副对角线(/)
    //dx 表示列的变化,dy表示行的变化
    int directions[4][2]={
        {1,0},//水平
        {0,1},//竖直
        {1,1},//右下
        {1,-1}//右上
    };

    for(int i=0;i<4;i++){
        int dx=directions[i][0];
        int dy=directions[i][1];

        int count=1;

        //正向查找
        for(int step=1;step<5;step++){
            int nRow=row+step*dy;
            int nCol=col+step*dx;
            //判断是否是边缘棋子  0~14
            if(nRow<0||nRow>=BOARD_SIZE||nCol<0||nCol>=BOARD_SIZE){
                break;
            }
            //是否是同一玩家下的
            if(m_board[nRow][nCol]==player){
                count++;
            }else{
                break;
            }
        }

        //反向查找
        for(int step=1;step<5;step++){
            int nRow=row-step*dy;
            int nCol=col-step*dx;

            //检查边界
            if(nRow<0||nRow>=BOARD_SIZE||nCol<0||nCol>=BOARD_SIZE){
                break;
            }

            if(m_board[nRow][nCol]==player){
                count++;
            }else{
                break;
            }
        }

        //五子连成
        if(count==5){
            return 1;
        }
    }
    //五子未练成
    return 0;
}

//重置
void WuZiQiBenDiDuiJu::ResetGame(){
    for(auto &row:m_board){
        std::fill(row.begin(),row.end(),0);
    }
    CurrentPlayer=1;
    IsGameOver=false;
    update();
}

//棋盘棋子下满时仍未结束
int WuZiQiBenDiDuiJu::isdraw()
{
        isdrawdata=0;
    for(int i=0;i<BOARD_SIZE;i++){
        for(int j=0;j<BOARD_SIZE;j++){
            if(m_board[i][j]==0){
                isdrawdata++;
            }
        }
    }
    if(isdrawdata==0){
        return 2;
    }
    return 0;
}

int WuZiQiBenDiDuiJu::getBOARD_SIZE()
{
    return BOARD_SIZE;
}
