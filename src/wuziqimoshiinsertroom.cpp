#include "wuziqimoshiinsertroom.h"
#include "ui_wuziqimoshiinsertroom.h"

WuZiQiMoShiInsertRoom::WuZiQiMoShiInsertRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WuZiQiMoShiInsertRoom)
{
    ui->setupUi(this);


}

void WuZiQiMoShiInsertRoom::onConnected()
{

    ui->ConnectStatus->setText("连接成功，正在进入游戏");

    QTimer::singleShot(1000,this,[=](){
        //将连接好的socket传出去，并关闭当前窗口
        emit ClientConnected(m_socket);
        this->close();
    });

}

void WuZiQiMoShiInsertRoom::onErrorOccurred(QAbstractSocket::SocketError SocketError)//SocketError底层把具体错误码传给这个参数
{
    Q_UNUSED(SocketError);

    //防崩判断
    if (!m_socket)return;

    ui->ConnectStatus->setText("连接失败");
    ui->ConnectServer->setEnabled(true);//恢复按钮

    QMessageBox::critical(this, "连接失败", "无法连接到房主，请检查：\n1. IP和端口是否输入正确\n2. 房主是否已经点击了创建房间\n3. 双方是否在同一个局域网（WiFi）下\n\n错误信息: " + m_socket->errorString());

}

WuZiQiMoShiInsertRoom::~WuZiQiMoShiInsertRoom()
{
    delete ui;
}

//点击"连接"按钮
void WuZiQiMoShiInsertRoom::on_ConnectServer_clicked()
{
    QString ip=ui->WuZiQiInsertIP->text().trimmed();
    quint16 port=ui->WuZiQiInsertPort->text().toUShort();

    if(ip.isEmpty()||port==0){
        QMessageBox::warning(this,"提示","请输入正确的IP和端口号");
        return;
    }

    //m_socket有值 先查、再断、后删、最后清零
//    if(m_socket){
//        //立即断开连接
//        m_socket->abort();
//        //安全释放内存（延迟销毁）
//        m_socket->deleteLater();
//        //断绝关系，变成空指针
//        m_socket = nullptr;
//    }


    if (m_socket) {
           // 1. 如果正在连接中，直接拦截，什么都不做
           if (m_socket->state() == QAbstractSocket::ConnectingState) {
               qDebug() << "正在连接中，请稍候，不要重复点击";
               return;
           }
           // 2. 如果已经连接成功，直接拦截
           if (m_socket->state() == QAbstractSocket::ConnectedState) {
               qDebug() << "已经连接成功，无需重连";
               return;
           }
}
    //实例化客户端 socket
    m_socket=new QTcpSocket(this);

    //信号发送者 信号 信号接收者 槽函数
    QMetaObject::Connection conn1=connect(m_socket,&QTcpSocket::connected,this,WuZiQiMoShiInsertRoom::onConnected);
    // 兼容旧版 Qt 5（低于 5.15）的 error 信号连接方式
    QMetaObject::Connection conn2=connect(m_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &WuZiQiMoShiInsertRoom::onErrorOccurred);


    if(!conn1){
        QMessageBox::critical(this,"Bug","connected 信号绑定失败！");
    }
    if(!conn2){
        QMessageBox::critical(this,"Bug","error 信号绑定失败！");
    }

    //连接状态时显示"正在连接房主" 连接完成后显示"连接成功，正在进入游戏"
    ui->ConnectStatus->setText("正在连接房主");
    ui->ConnectServer->setEnabled(false);//防止连续点击

          m_socket->connectToHost(ip,port);//拨打指定的 IP 和端口

}



//点击"取消"按钮
void WuZiQiMoShiInsertRoom::on_CancelLobby_clicked()
{
    //如果正在连接，立刻中断 abort() 关闭套接字
    if(m_socket){
        m_socket->abort();
    }
    this->close();
}
