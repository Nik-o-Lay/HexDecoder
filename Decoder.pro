QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FormDrofa.cpp \
    FormKorshun.cpp \
    Window.cpp \
    main.cpp \
    Decoder.cpp

HEADERS += \
    Decoder.h \
    FormDrofa.h \
    FormKorshun.h \
    Window.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    FormDrofa.ui \
    FormKorshun.ui \
    Window.ui
