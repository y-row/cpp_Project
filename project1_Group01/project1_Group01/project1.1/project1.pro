QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    boxbrick.cpp \
    brokenbrick.cpp \
    bullet.cpp \
    coin.cpp \
    fire_flower.cpp \
    flag.cpp \
    flag_pole.cpp \
    floor.cpp \
    flower.cpp \
    gamebase.cpp \
    main.cpp \
    mainwindow.cpp \
    mario.cpp \
    mediaplayer.cpp \
    normalbrick.cpp \
    stonebrick.cpp \
    super_mushroom.cpp \
    superstar.cpp \
    toxic_mushroom.cpp \
    turtle.cpp \
    waterpipe.cpp

HEADERS += \
    boxbrick.h \
    brokenbrick.h \
    bullet.h \
    coin.h \
    fire_flower.h \
    flag.h \
    flag_pole.h \
    floor.h \
    flower.h \
    gamebase.h \
    mainwindow.h \
    mario.h \
    mediaplayer.h \
    normalbrick.h \
    stonebrick.h \
    super_mushroom.h \
    superstar.h \
    toxic_mushroom.h \
    turtle.h \
    waterpipe.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    project1_zh_TW.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Dataset/Dataset.qrc

DISTFILES += \
    change_in_this_version \
    readme
