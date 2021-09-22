TEMPLATE = app
TARGET = ui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core gui network

qtHaveModule(printsupport): QT += printsupport
INCLUDEPATH += ../CT_Logue/source

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

LIBS += -L$$PWD/../build/CT_Logue/debug -lCT_Logue
message(dt $$PWD)
