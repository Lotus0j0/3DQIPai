#ifndef WUZIQIBENDIDUIJU_H
#define WUZIQIBENDIDUIJU_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QMessageBox>
#include<QPaintEvent>
#include<vector>
#include<QtMath>
#include<QTimer>
#include<QApplication>
#include<QDebug>
//前向声明 防止头文件嵌套
class wuziqibendimoshiduijugameover;

class WuZiQiBenDiDuiJu: public QWidget
{
public:
    void paintEvent(QPaintEvent *event)override;
    WuZiQiBenDiDuiJu();
    void mousePressEvent(QMouseEvent *event)override;
    void SaveData(int row,int col);
    int CheckWin(int row,int col,int player);
    void ResetGame();
    int isdraw();

    static int getBOARD_SIZE();
private:
    static const int BOARD_SIZE=3;//棋子的数量
    static const int MARGIN=50;//离窗口的边距
    static const int GRID_SIZE=100;//每两个棋子间的间距

    int isdrawdata=0;

    //棋盘状态 0=空 1=黑棋 2=白棋
    std::vector<std::vector<int>>m_board;

    int CurrentPlayer=1;//当前轮到谁下(1=黑,2=白)

    bool IsGameOver=false;//游戏是否结束
};

#endif // WUZIQIBENDIDUIJU_H
