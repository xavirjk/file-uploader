#include "viewfile.h"
#if defined(QT_PRINTSUPPORT_LIB)
#include <QtPrintSupport/qtprintsupportglobal.h>
#if QT_CONFIG(printdialog)
#include <QPrinter>
#include <QPrintDialog>
#endif
#endif
#include <QPdfWriter>
#include <QPainter>
using namespace CTLogue::ui;

class ViewFile::Implementation{
public: Implementation(ViewFile *_viewFile, const QString &_resource,QFont *f = nullptr ):
        viewFile(_viewFile),
        resource(_resource),
        font(f)
    {

    }
    ViewFile *viewFile{nullptr};
    QVBoxLayout *mainL = new QVBoxLayout;
    QString resource;
    QFont *font;
    QGraphicsView *graphicsView;
    QString uri = "http://localhost:3400/%1";
    QUrl url = uri.arg(resource);
    QByteArray data;
    QString basePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QString fullPath = basePath + '/' + resource;
};

ViewFile::ViewFile(QWidget *parent, const QString &resource , QFont *f) : QWidget(parent)
{
    implementation.reset(new Implementation(this, resource,f));
}
void ViewFile::setUpPage(){
    implementation->font->setPixelSize(30);
    QHBoxLayout *hbox = new QHBoxLayout;
    QLabel *label = new QLabel;
    QPushButton *printBtn = new QPushButton;
    QPushButton *openFile = new QPushButton("Open File");

    openFile->setProperty("class", "external rsBtn");
    //Refactor...
    QString displayName = implementation->resource.sliced(implementation->resource.indexOf("-")+1);
    if(displayName.length() > 27) displayName = displayName.sliced(0,27)+ "...";
    label->setText(displayName);
    printBtn->setFont(*implementation->font);
    printBtn->setText("\uf02f");
    printBtn->setProperty("class", "printBtn");
    label->setProperty("class", "key");
    hbox->addWidget(label);
    hbox->addWidget(printBtn);
    implementation->mainL->addLayout(hbox);
    implementation->mainL->addWidget(openFile,0);
    connect(openFile, &QAbstractButton::clicked, this,&ViewFile::handleBtnClick);
    connect(printBtn, &QAbstractButton::clicked, this,&ViewFile::handlePrintFileBtn);
    setLayout(implementation->mainL);
}

void ViewFile::handleBtnClick(){
    if(implementation->data.isEmpty()){
        QDesktopServices::openUrl(implementation->url);
        return;
    }
    QDesktopServices::openUrl(QUrl("file:///"+implementation->fullPath,QUrl::TolerantMode));
}
void ViewFile::handlePrintFileBtn(){
    if (implementation->data.isEmpty()){
        emit getFileforPrinting(implementation->url);
        return;
    }
    printfcn();
}
void ViewFile::printFile(const QByteArray &bytes, const QString &name){
    implementation->data = QByteArray();
    implementation->data = bytes;
    printfcn();
}
void ViewFile::printfcn(){
    return saveFile();
}
void ViewFile::saveFile(){

    QFile file(implementation->fullPath);
    QDir *dir = new QDir(implementation->basePath + "/Data");
    if(!dir->exists()) {
        dir->mkdir(implementation->basePath + "/Data");
    }
    if (!file.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Could not open %s for writing: %s\n",
                qPrintable(implementation->fullPath),
                qPrintable(file.errorString()));
        return;
    }

    file.write(implementation->data);
    file.close();
    QDesktopServices::openUrl(QUrl("file:///"+implementation->fullPath,QUrl::TolerantMode));
}

ViewFile::~ViewFile(){}
