QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fourthwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    secondwindow.cpp \
    text_file.cpp \
    text_input_file.cpp \
    text_output_file.cpp \
    thirdwindow.cpp

HEADERS += \
    file.h \
    fourthwindow.h \
    mainwindow.h \
    secondwindow.h \
    text_file.h \
    text_input_file.h \
    text_output_file.h \
    thirdwindow.h

FORMS += \
    ../../Downloads/lab7/fourthwindow.ui \
    ../../Downloads/lab7/mainwindow.ui \
    ../../Downloads/lab7/secondwindow.ui \
    ../../Downloads/lab7/thirdwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
