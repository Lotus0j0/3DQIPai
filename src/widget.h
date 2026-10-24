#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QMessageBox>
#include<QDebug>
#include<QSqlDataBase>
#include <QSqlError>
#include<QSqlQuery>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_ZhuCe_clicked();

    void on_DengLu_clicked();

private:
    Ui::Widget *ui;

    QString StaAccount;

};

#endif // WIDGET_H
