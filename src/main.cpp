#include "widget.h"
#include <QApplication>
#include <QNetworkProxy>
#include <spdlog/spdlog.h>
#ifdef __MINGW32__
#include <ctime>
time_t _mkgmtime(struct tm* const tmp) {
    return mktime(tmp); // 注意：这只是一个简化替代，在某些情况下可能不够精确
}
#endif
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //禁用系统代理配置
    QNetworkProxyFactory::setUseSystemConfiguration(false);

    Widget w;
    w.show();

    //LoggerManager::logUserLogin(username);

    return a.exec();
}
