QT       += core gui network xml multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, unQT_DISABLE_DEPRECATED_BEFOREcomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bulletNode.cpp \
    bulletlist.cpp \
    listid.cpp \
    localserver.cpp \
    main.cpp \
    nodeid.cpp \
    thread.cpp

HEADERS += \
    bulletNode.h \
    bulletlist.h \
    listid.h \
    localserver.h \
    nodeid.h \
    thread.h

FORMS += \
    form.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    backG.qrc \
    bulletFile.qrc \
    main.qrc \
    naveFile.qrc \
    naveenemiga2.qrc \
    stra1.qrc \
    stra2.qrc \
    stra3.qrc \
    stra4.qrc
