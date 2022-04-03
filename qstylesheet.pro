#Huge Thanks for S.N. Sergey!

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    allstylesheet.cpp \
    colorpicker.cpp \
    drawer.cpp \
    dynamicwidgettool.cpp \
    gpick.cpp \
    gradientpicker.cpp \
    highlighter.cpp \
    main.cpp \
    main_screen.cpp \
    marker.cpp \
    notificationpopup.cpp \
    panel.cpp \
    panelbackground.cpp \
    panelgeometry.cpp \
    panelicon.cpp \
    panelmargins.cpp \
    panelround.cpp \
    paneltext.cpp \
    projectpreview.cpp \
    stylecontent.cpp \
    texteditlabel.cpp \
    threadwhile.cpp \
    titlebutton.cpp \
    widget.cpp

HEADERS += \
    allstylesheet.h \
    colorpicker.h \
    defines.h \
    drawer.h \
    dynamicwidgettool.h \
    gpick.h \
    gradientpicker.h \
    highlighter.h \
    main_screen.h \
    marker.h \
    notificationpopup.h \
    panel.h \
    panelbackground.h \
    panelgeometry.h \
    panelicon.h \
    panelmargins.h \
    panelround.h \
    paneltext.h \
    projectpreview.h \
    stylecontent.h \
    texteditlabel.h \
    threadwhile.h \
    titlebutton.h \
    widget.h

FORMS += \
    drawer.ui \
    gradientpicker.ui \
    main_screen.ui \
    notificationpopup.ui \
    widget.ui




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc \
    icons.qrc

DISTFILES += \
    icons/images/plus.png \
    icons/images/plus_normal.png
