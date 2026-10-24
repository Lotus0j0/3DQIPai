#ifndef WUZIQI_MOSHI_H
#define WUZIQI_MOSHI_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include"wuziqimoshicreateroom.h"
#include"wuziqimoshiinsertroom.h"


namespace Ui {
class WuZiQi_MoShi;
}

class WuZiQi_MoShi : public QWidget
{
    Q_OBJECT

public:
    explicit WuZiQi_MoShi(QWidget *parent = 0);
    ~WuZiQi_MoShi();

private slots:
    void on_BenDiModel_clicked();

    void on_CreateRoom_clicked();

    void on_InsertRoom_clicked();

private:
    Ui::WuZiQi_MoShi *ui;
};

#endif // WUZIQI_MOSHI_H
