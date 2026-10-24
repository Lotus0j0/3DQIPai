#ifndef LOBBY_H
#define LOBBY_H

#include <QWidget>
#include <QString>
#include<QFile>
#include<QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>

namespace Ui {
class Lobby;
}

class Lobby : public QWidget
{
    Q_OBJECT

public:
    explicit Lobby(QString TemAccount,QWidget *parent = 0);
    ~Lobby();

private slots:
    void on_WuZiQi_clicked();

private:
    Ui::Lobby *ui;

    QString Account;
};

#endif // LOBBY_H
