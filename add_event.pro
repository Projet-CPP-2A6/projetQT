<<<<<<< Updated upstream
QT       += core gui sql
=======
QT       += core gui sql charts network location multimedia multimediawidgets widgets quickwidgets serialport
QT += printsupport
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
=======
    arduino.cpp \
    arduinotemp.cpp \
    artiste.cpp \
    association.cpp \
    chatbox.cpp \
>>>>>>> Stashed changes
    connection.cpp \
    event.cpp \
    main.cpp \
<<<<<<< Updated upstream
    mainwindow.cpp

HEADERS += \
=======
    mainwindow.cpp \
    notification.cpp \
    oeuvre.cpp \
    qrcode.cpp \
    smtp.cpp \
    statsdialog.cpp
INCLUDEPATH += "C:\Users\medal\Downloads\eigen-3.4.0"


HEADERS += \
    arduino.h \
    arduinotemp.h \
    artiste.h \
    association.h \
    chatbox.h \
>>>>>>> Stashed changes
    connection.h \
    event.h \
    mainwindow.h

FORMS += \
<<<<<<< Updated upstream
=======
    arduinotemp.ui \
    dialog.ui \
    dialog1.ui \
    dialogemp.ui \
>>>>>>> Stashed changes
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
