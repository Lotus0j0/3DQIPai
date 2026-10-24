#include "widget.h"
#include "ui_widget.h"
#include"lobby.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("192.168.1.10");
    db.setDatabaseName("account_password");
    db.setUserName("DENGLU");
    db.setPassword("wangyang?");

    if(db.open()){
        QMessageBox::information(this,"连接提示","连接成功");
    }else{
        // 获取具体的错误信息
           QString errorMsg = db.lastError().text();
           QMessageBox::warning(this, "连接提示", "连接失败:\n" + errorMsg); // 弹窗显示
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_ZhuCe_clicked()
{
    QString aAccount=ui->Account->text();
    QString aPassword=ui->Password->text();

    if (aAccount.isEmpty() || aPassword.isEmpty()) {
           QMessageBox::warning(this, "提示", "所有字段不能为空！");
           return;
       }

    QSqlQuery query;

    query.prepare("insert into user_info(username,password) VALUES (:Ausername,:Apassword)");//:Ausername,:Apassword 占位符

    query.bindValue(":Ausername",aAccount);
    query.bindValue(":Apassword",aPassword);

    if (query.exec()) {
            QMessageBox::information(this, "插入提示", "插入成功");
            // 插入成功后，可以选择清空输入框
            // ui->idlineedit->clear();
            // ui->namelineedit->clear();
            // ui->birlinedit->clear();
        } else {
            QString err = query.lastError().text();
            QMessageBox::warning(this, "插入失败", "错误原因: " + err);
        }
}

void Widget::on_DengLu_clicked()
{
    QString aAccount=ui->Account->text();
    StaAccount=aAccount;
    QString aPassword=ui->Password->text();

    if (aAccount.isEmpty() || aPassword.isEmpty()) {
           QMessageBox::warning(this, "提示", "账号和密码不能为空！");
           return;
       }

    QSqlQuery query;

    query.prepare("SELECT * FROM user_info WHERE username = :username AND password = :password");

    query.bindValue(":username", aAccount);
    query.bindValue(":password", aPassword);

    if (query.exec()) {

           if (query.next()) {
               // 如果 next() 返回 true，说明查到了数据，账号密码完全匹配！
               QMessageBox::information(this, "登录成功", "欢迎回来，" + aAccount);

               //跳转到主界面
               Lobby *lobbywin=new Lobby(aAccount);

               lobbywin->setAttribute(Qt::WA_DeleteOnClose);

               lobbywin->show();

               this->hide();

           } else {
               // 如果 next() 返回 false，说明没查到数据，账号不存在或密码错误
               QMessageBox::warning(this, "登录失败", "账号或密码错误！");
           }
       } else {
           // 如果 exec() 失败，说明 SQL 语句或数据库出问题了
           QString err = query.lastError().text();
           QMessageBox::warning(this, "数据库错误", "查询失败: " + err);
       }
   }
