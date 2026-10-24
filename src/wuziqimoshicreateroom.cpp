#include "wuziqimoshicreateroom.h"
#include "ui_wuziqimoshicreateroom.h"

WuZiQiMoShiCreateRoom::WuZiQiMoShiCreateRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WuZiQiMoShiCreateRoom)
{
    ui->setupUi(this);

    //实例化服务器
    m_server=new QTcpServer(this);

    //开始监听所有网卡 端口号为PORT
    //返回true 1.端口未被占用 2.至少有一张可用的网络接口，并且成功绑定了 3.操作系统允许当前用户的程序进行监听操作 4.底层网络环境（包括代理设置）没有阻碍监听动作
   if(m_server->listen(QHostAddress::Any,PORT)){
        //获取本机的局域网ip和端口号，并显示在界面
        ip = getLocalIP();
        ui->WuZiQiCreateIP->setText(ip);
        ui->WuZiQiCreatePORT->setText(QString::number(PORT));

        ui->LianJieZhuangTai->setText("正在等待对手连接");

        //连接 newConnection 信号到槽函数
        connect(m_server,&QTcpServer::newConnection,this,&WuZiQiMoShiCreateRoom::onNewConnection);
    }else{
        QMessageBox::critical(this,"错误","服务器端口被占用"+m_server->errorString());
    }
}

void WuZiQiMoShiCreateRoom::onNewConnection(){

    //nextPendingConnection() 从队列头部拿出来一个，包装成 QTcpSocket 对象返回
    QTcpSocket* socket=m_server->nextPendingConnection();
    m_server->close();

    ui->LianJieZhuangTai->setText("对手已加入，正在进入游戏");

    //断绝socket与m_server关系 注意释放
    socket->setParent(nullptr);

    QTimer::singleShot(1000,this,[=](){
        emit ClientConnected(socket);
        this->close();
    });

    m_board.assign(WuZiQiBenDiDuiJu::getBOARD_SIZE(),std::vector<int>(WuZiQiBenDiDuiJu::getBOARD_SIZE(),0));
}

void WuZiQiMoShiCreateRoom::onReadyRead()
{

}

void WuZiQiMoShiCreateRoom::onClientDisconnected()
{

}

WuZiQiMoShiCreateRoom::~WuZiQiMoShiCreateRoom()
{
    delete ui;
}

//获取本机互联网ip
QString WuZiQiMoShiCreateRoom::getLocalIP()
{
    QString ipAddress;
    // 获取所有网络接口的地址列表
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();

    // 遍历这些地址
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        // 排除本地回环地址(127.0.0.1)，并且只找IPv4地址
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            // 优先获取局域网常见的 192.168.x.x 或 10.x.x.x 开头的地址
            if(ipAddress.startsWith("192.168.") || ipAddress.startsWith("10.")) {
                break;
            }
        }
    }
    // 如果没找到，就默认返回本机回环地址
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    return ipAddress;
}
