#include "lobby.h"
#include "ui_lobby.h"
#include "wuziqi_moshi.h"

Lobby::Lobby(QString TemAccount,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lobby)
{
    ui->setupUi(this);

    Account=TemAccount;

    ui->AccountUi->setText(Account);

    /* 安装解码器 LAV Filters */

    //判断文件是否存在 本地文件判断
//    QString filePath = "c/";
//    if (!QFile::exists(filePath)) {
//        qDebug() << "文件不存在:" << filePath;
//    }

    //创建播放列表
    QMediaPlaylist *playlist=new QMediaPlaylist(this);
    playlist->addMedia(QUrl("qrc:/everaudio/Sunset.mp3"));

    //设置音源
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    //创建播放器并绑定播放列表
    QMediaPlayer* player=new QMediaPlayer(this);
    player->setPlaylist(playlist);

    //设置音量并播放
    player->setVolume(50);
    player->play();
}

Lobby::~Lobby()
{
    delete ui;
}

void Lobby::on_WuZiQi_clicked()
{
    WuZiQi_MoShi* WUZIQI=new WuZiQi_MoShi();
    WUZIQI->setAttribute(Qt::WA_DeleteOnClose);
    WUZIQI->show();
    this->hide();
}
