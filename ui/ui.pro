TEMPLATE = app
TARGET = ui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core gui network

qtHaveModule(printsupport): QT += printsupport
INCLUDEPATH += ../upld/source

SOURCES += \
    downloadpane.cpp \
    form.cpp \
    homepane.cpp \
    label.cpp \
    main.cpp \
    mainview.cpp \
    viewfile.cpp

RESOURCES = stylesheet.qrc

HEADERS += \
    downloadpane.h \
    form.h \
    homepane.h \
    label.h \
    mainview.h \
    viewfile.h

LIBS += -L$$PWD/../build/upld/debug -lupld
message(dt $$PWD)
