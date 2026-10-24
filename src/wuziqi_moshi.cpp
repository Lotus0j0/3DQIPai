#include "wuziqi_moshi.h"
#include "ui_wuziqi_moshi.h"
#include"wuziqibendiduiju.h"

WuZiQi_MoShi::WuZiQi_MoShi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WuZiQi_MoShi)
{
    ui->setupUi(this);
}

WuZiQi_MoShi::~WuZiQi_MoShi()
{
    delete ui;
}
void WuZiQi_MoShi::on_BenDiModel_clicked()
{
    WuZiQiBenDiDuiJu* WuZiQigame=new WuZiQiBenDiDuiJu();
    WuZiQigame->setAttribute(Qt::WA_DeleteOnClose);
    WuZiQigame->show();
    this->close();
}

void WuZiQi_MoShi::on_CreateRoom_clicked()
{
    WuZiQiMoShiCreateRoom* createroom=new WuZiQiMoShiCreateRoom();
    createroom->show();
    //x掉后 释放server对象
    createroom->setAttribute(Qt::WA_DeleteOnClose);
}

void WuZiQi_MoShi::on_InsertRoom_clicked()
{
    WuZiQiMoShiInsertRoom* insertroom=new WuZiQiMoShiInsertRoom();
    insertroom->show();
    insertroom->setAttribute(Qt::WA_DeleteOnClose);
}
