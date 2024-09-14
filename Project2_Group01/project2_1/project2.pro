QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    auto.cpp \
    bullet.cpp \
    characters.cpp \
    fireboss.cpp \
    gamebase.cpp \
    greenmonster.cpp \
    main.cpp \
    mainwindow.cpp \
    mediaplayer.cpp \
    monster.cpp \
    runestone.cpp \
    slime.cpp

HEADERS += \
    auto.h \
    bullet.h \
    characters.h \
    fireboss.h \
    gamebase.h \
    greenmonster.h \
    mainwindow.h \
    mediaplayer.h \
    monster.h \
    runestone.h \
    slime.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    project2_zh_TW.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    data.qrc

DISTFILES += \
    readme
