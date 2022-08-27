QT       += core gui
QT       += multimedia
QT       += sql
CONFIG += resources_big

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background.cpp \
    bird.cpp \
    land.cpp \
    main.cpp \
    music.cpp \
    pipe.cpp \
    skill.cpp \
    sqlite.cpp \
    widget.cpp

HEADERS += \
    background.h \
    bird.h \
    land.h \
    music.h \
    pipe.h \
    pipe.h \
    skill.h \
    sqlite.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    image/info_score.png \
    image/light (1).png \
    image/light (2).png \
    image/light (3).png \
    image/light (4).png \
    image/light (5).png \
    image/light (6).png
