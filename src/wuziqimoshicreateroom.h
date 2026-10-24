#ifndef CREATEROOM_H
#define CREATEROOM_H

#include <QWidget>
#include <QTcpServer>
#include <QNetworkInterface>
#include <QString>
#include<QMessageBox>
#include<QTcpSocket>
#include<QTimer>
#include<vector>
#include<wuziqibendiduiju.h>
#define PORT 12345

namespace Ui {
class WuZiQiMoShiCreateRoom;
}

class WuZiQiMoShiCreateRoom : public QWidget
{
    Q_OBJECT

public:
    explicit WuZiQiMoShiCreateRoom(QWidget *parent = 0);
    ~WuZiQiMoShiCreateRoom();

signals:
    //当有客户端成功连接时，发射此信号，将套接字传递出去
    void ClientConnected(QTcpSocket* socket);

private slots:
    //处理新连接的槽函数
    void onNewConnection();

    void onReadyRead();//接收客户端数据
    void onClientDisconnected();//处理断线

private:
    Ui::WuZiQiMoShiCreateRoom *ui;

    QTcpServer* m_server;//服务器指针
    QTcpSocket* m_socket;

    //获取本机局域网IP
    QString getLocalIP();
    QString ip;

    QList<QTcpSocket*>m_client;//保存连接的玩家
    std::vector<std::vector<int>>m_board;//棋盘状态(0空，1黑，2白)
    int m_turn;//当前是谁的回合
    bool checkWin(int row,int col,int color);//判胜函数

};

#endif // CREATEROOM_H
