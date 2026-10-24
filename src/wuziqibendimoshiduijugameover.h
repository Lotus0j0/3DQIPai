#ifndef WUZIQIBENDIMOSHIDUIJUGAMEOVER_H //#ifndef 如果没有定义
#define WUZIQIBENDIMOSHIDUIJUGAMEOVER_H //就定义 他

#include <QWidget>
#include <QString>

class WuZiQiBenDiDuiJu;

namespace Ui {
class wuziqibendimoshiduijugameover;
}

class wuziqibendimoshiduijugameover : public QWidget
{
    Q_OBJECT

public:
    explicit wuziqibendimoshiduijugameover(int CurrentPlayer, WuZiQiBenDiDuiJu* TempRegameWuZiQi,QWidget *parent = 0);
    ~wuziqibendimoshiduijugameover();

private slots:
    void on_ReStart_clicked();

    void on_ReturnLobby_clicked();

private:
    Ui::wuziqibendimoshiduijugameover *ui;

    WuZiQiBenDiDuiJu* RegameWuZiQi;

    QString winner;
};

#endif // WUZIQIBENDIMOSHIDUIJUGAMEOVER_H //定义过 就结束
