TEMPLATE = app
TARGET = ui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets core gui network

qtHaveModule(printsupport): QT += printsupport
INCLUDEPATH += ../upld/source

RESOURCES = stylesheet.qrc

message(dt $$PWD)
