QT       += core gui
QT       += network
QT       += xml
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    client.cpp \
    main.cpp \
    mainwindow.cpp \
    serverconfigdialog.cpp \
    transportinginterfaces.cpp \
    userelements.cpp \
    usernameeditdialog.cpp \
    vuex.cpp \
    xmlsavedialog.cpp

HEADERS += \
    client.h \
    mainwindow.h \
    serverconfigdialog.h \
    transportinginterfaces.h \
    userelements.h \
    usernameeditdialog.h \
    vuex.h \
    xmlsavedialog.h

FORMS += \
    mainwindow.ui \
    serverconfigdialog.ui \
    usernameeditdialog.ui \
    xmlsavedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
