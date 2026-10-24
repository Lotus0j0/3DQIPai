#ifndef INSERTROOM_H
#define INSERTROOM_H

#include <QWidget>
#include <QTcpSocket>
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include<QTimer>

namespace Ui {
class WuZiQiMoShiInsertRoom;
}

class WuZiQiMoShiInsertRoom : public QWidget
{
    Q_OBJECT

public:
    explicit WuZiQiMoShiInsertRoom(QWidget *parent = 0);    

    ~WuZiQiMoShiInsertRoom();

signals:
    void ClientConnected(QTcpSocket* socket);

private slots:
    void onConnected();
    void onErrorOccurred(QAbstractSocket::SocketError SocketError);

    void on_ConnectServer_clicked();

    void on_CancelLobby_clicked();

private:
    Ui::WuZiQiMoShiInsertRoom *ui;

    QTcpSocket* m_socket=nullptr;
};

#endif // INSERTROOM_H
