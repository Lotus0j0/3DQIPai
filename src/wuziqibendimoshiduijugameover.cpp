#include "wuziqibendimoshiduijugameover.h"
#include "ui_wuziqibendimoshiduijugameover.h"
#include "wuziqibendiduiju.h"

wuziqibendimoshiduijugameover::wuziqibendimoshiduijugameover(int CurrentPlayer,WuZiQiBenDiDuiJu* TempRegameWuZiQi,QWidget *parent) :
    QWidget(parent),
    //初始化QWidget对象，内部传入QWidget类指针
    /*
    QObject::QObject(QObject *parent) // 这里的 parent 接收到了 mainWin 的地址
    {
        if (parent) { // parent 是 mainWin，不是空指针
            // 1. 记录父亲（当前弹窗内部偷偷记下：我的爸爸是 mainWin）
            d_ptr->parent = parent;  // 左边是弹窗自己的变量，右边是主窗口地址

            // 2. 上户口（把当前这个弹窗对象，塞进 mainWin 的孩子列表里）
            // 这里的 this 指的是当前正在 new 的弹窗对象
            parent->d_ptr->children.append(this);
        }
    }
    }
    */
    ui(new Ui::wuziqibendimoshiduijugameover)
{
    ui->setupUi(this);

    if(CurrentPlayer==1){
        ui->label->setText("游戏结束,<span style='color:black;font-weight:bold;'>黑棋</span>赢了");
    }else if(CurrentPlayer==2){
        ui->label->setText("游戏结束,<span style='color:black;font-weight:bold;'>白棋</span>赢了");
    }else if(CurrentPlayer==3){
        ui->label->setText("游戏结束,<span style='color:black;font-weight:bold;'>平局</span>");
    }

    RegameWuZiQi=TempRegameWuZiQi;

}

wuziqibendimoshiduijugameover::~wuziqibendimoshiduijugameover()
{
    delete ui;
}

void wuziqibendimoshiduijugameover::on_ReStart_clicked()
{
    RegameWuZiQi->ResetGame();

    RegameWuZiQi->show();

    //close会执行当前界面的delete
    this->deleteLater();

}

void wuziqibendimoshiduijugameover::on_ReturnLobby_clicked()
{
        //topLevelWidgets() 返回当前应用程序中所有"顶层窗口"的列表
        for (QWidget *widget : QApplication::topLevelWidgets()) {
            //inherits 检查一个对象是否继承自某个特定的类
            if (widget->inherits("Lobby")) {
                widget->show();
            }
        }
        this->close();
        RegameWuZiQi->close();
}
