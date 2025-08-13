QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Удаляем Qt EntryPoint, если он был добавлен
# LIBS -= -lQt6EntryPoint

# Добавляем системные библиотеки для MinGW
LIBS += "-Wl,--start-group" \
        "D:/a/qt/qt/Qt/6.8.3/mingw_64/lib/libQt6Widgets.a" \
        "D:/a/qt/qt/Qt/6.8.3/mingw_64/lib/libQt6Gui.a" \
        "D:/a/qt/qt/Qt/6.8.3/mingw_64/lib/libQt6Core.a" \
        "D:/a/qt/qt/Qt/6.8.3/mingw_64/lib/libQt6EntryPoint.a" \
        -lmingw32 -lmingwex -lshell32 \
        "-Wl,--end-group"


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
