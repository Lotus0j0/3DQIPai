#-------------------------------------------------
#
# Project created by QtCreator 2026-10-17T10:32:36
#
#-------------------------------------------------



QT       += core gui sql multimedia network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DengLu
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    widget.cpp \
    lobby.cpp \
    wuziqi_moshi.cpp \
    wuziqibendiduiju.cpp \
    wuziqibendimoshiduijugameover.cpp \
    wuziqimoshiinsertroom.cpp \
    wuziqimoshicreateroom.cpp \
    wuziqionline.cpp

HEADERS += \
    widget.h \
    lobby.h \
    wuziqi_moshi.h \
    wuziqibendiduiju.h \
    wuziqibendimoshiduijugameover.h \
    wuziqimoshicreateroom.h \
    wuziqimoshiinsertroom.h \
    wuziqionline.h

FORMS += \
    widget.ui \
    lobby.ui \
    wuziqi_moshi.ui \
    wuziqibendimoshiduijugameover.ui \
    wuziqimoshiinsertroom.ui \
    wuziqimoshicreateroom.ui

RESOURCES += \
    ../asset/res.qrc

# 在你的 .pro 文件中添加 ../ 表示返回上一级
INCLUDEPATH += $$PWD/../spdlog/include

# 禁用 spdlog 的时区偏移计算，解决 MinGW 下的 _tzset 链接错误
DEFINES += SPDLOG_NO_TZ_OFFSET
