#include <QApplication>
#include <QFile>
#include "mainview.h"
#include <iostream>
using namespace std;
using namespace  CTLogue::ui;

int main (int argc, char *argv[]) {
    QApplication app(argc, argv);
    Mainview ui;

    QFile File(":/qss/default.qss");

    File.open(QFile::ReadOnly);
    QString stylesheet = QLatin1String(File.readAll());
    app.setStyleSheet(stylesheet);
    ui.show();

    return app.exec();
}
