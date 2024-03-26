QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstraktui.cpp \
    active.cpp \
    attackcontroller.cpp \
    button.cpp \
    character.cpp \
    chest.cpp \
    controller.cpp \
    door.cpp \
    dungeoncrawler.cpp \
    floor.cpp \
    graphen.cpp \
    graphicalui.cpp \
    guardcontroller.cpp \
    level.cpp \
    levelchanger.cpp \
    list.cpp \
    main.cpp \
    mainwindow.cpp \
    passive.cpp \
    pit.cpp \
    player.cpp \
    portal.cpp \
    ramp.cpp \
    startscreen.cpp \
    stationarycontroller.cpp \
    switch.cpp \
    terminalui.cpp \
    tile.cpp \
    wall.cpp \
    zombie.cpp \
    zombieattack.cpp \
    zombieguard.cpp

HEADERS += \
    abstraktui.h \
    active.h \
    attackcontroller.h \
    button.h \
    character.h \
    chest.h \
    controller.h \
    door.h \
    dungeoncrawler.h \
    floor.h \
    graphen.h \
    graphicalui.h \
    guardcontroller.h \
    level.h \
    levelchanger.h \
    list.h \
    mainwindow.h \
    passive.h \
    pit.h \
    player.h \
    portal.h \
    ramp.h \
    startscreen.h \
    stationarycontroller.h \
    switch.h \
    terminalui.h \
    tile.h \
    wall.h \
    zombie.h \
    zombieattack.h \
    zombieguard.h

FORMS += \
    mainwindow.ui \
    startscreen.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    DungoenCrawler2.pro

DISTFILES +=
