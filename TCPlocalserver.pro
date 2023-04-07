QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
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
    bulletFile.qrc \
    main.qrc \
    naveFile.qrc
