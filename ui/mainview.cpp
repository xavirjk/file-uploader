#include "mainview.h"
#include <QTableView>
#include <QDebug>
#include <QFontDatabase>
using namespace CTLogue::ui;

Mainview::Mainview(QWidget *parent):
    QWidget(parent) {
    ;
    setUpHome();
    //resize(500, 300);
    setMaximumSize(700,500);
    setWindowTitle(tr("CTLogue"));
}

void Mainview::setUpHome(){
    if (QFontDatabase::addApplicationFont(":/qss/fontawesome.ttf") < 0){
        qWarning()<<"Font awesome could not be loaded";
    }
    font.setFamily("FontAwesome");
    font.setPixelSize(60);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox2 = new QHBoxLayout;
    hbox3 = new QHBoxLayout;
    QPushButton *moviesBtn = new QPushButton(tr("Movies"));
    QPushButton *tvShowsBtn = new QPushButton(tr("Tv Shows"));
    QPushButton *booksBtn = new QPushButton(tr("Books"));

    homePane = new HomePane(this);
    //downloadPane =  new DownloadPane(this,"download");

    connect(moviesBtn,&QAbstractButton::clicked,this,&Mainview::toggleMoviesView);
    connect(tvShowsBtn,&QAbstractButton::clicked,this,&Mainview::toggleTvShowView);
    connect(booksBtn,&QAbstractButton::clicked,this,&Mainview::toggleBooksView);
    connect(homePane, &HomePane::addCode, log, &CT_Logue::getPCODE);
    connect(homePane, &HomePane::PCODEtoCreate,log,&CT_Logue::generatePCODE);
    connect(log,&CT_Logue::fileNamesUpdated,this,&Mainview::filesReceived);
    connect(log, &CT_Logue::renderFile,this,&Mainview::fileDataReceived);
    connect(log, &CT_Logue::displayMessage, this, &Mainview::displayResMessage);
    moviesBtn ->setProperty("class", "hdBtns");
    tvShowsBtn ->setProperty("class","hdBtns");
    booksBtn ->setProperty("class", "hdBtns");
    responseTag ->setProperty("class", "res");

    moviesBtn ->setFont(font);
    moviesBtn ->setText("\uf093");
    tvShowsBtn ->setFont(font);
    tvShowsBtn ->setText("\uf019");
    booksBtn ->setFont(font);
    booksBtn->setText("\uf083");

    hbox ->addWidget(moviesBtn);
    hbox ->addWidget(tvShowsBtn);
    hbox ->addWidget(booksBtn);

    hbox3->addWidget(responseTag);
    hbox2 ->addWidget(homePane);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout ->setAlignment(Qt::AlignTop);
    mainLayout ->addLayout(hbox);
    mainLayout ->addLayout(hbox3);
    mainLayout ->addLayout(hbox2, 0);
    hideMessage();
    setLayout(mainLayout);
}

void Mainview::toggleMoviesView(){
    hbox2 ->itemAt(0) ->widget()->setVisible(false);
    hbox2 ->removeWidget(hbox2->itemAt(0)->widget());
    pane = new viewPane(this,"upload");
    connect(pane, &viewPane::requestFormBtnClicked, this,&Mainview::theForm);
    hbox2 ->addWidget(pane);

    return ;
}

void Mainview::toggleTvShowView(){
    hbox2 ->itemAt(0) ->widget()->setVisible(false);
    hbox2 ->removeWidget(hbox2->itemAt(0)->widget());
    downloadPane =  new DownloadPane(this,"download",&font);
    connect(downloadPane,&DownloadPane::navigateViewFile,this,&Mainview::viewFile);
    /*connect(log,&CT_Logue::fileNamesUpdated,downloadPane,&DownloadPane::fetchFiles);*/
    hbox2 ->addWidget(downloadPane);
    log->fetchFiles();
    return;
}

void Mainview::toggleBooksView(){
    hbox2 ->itemAt(0) ->widget()->setVisible(false);
    hbox2 ->removeWidget(hbox2->itemAt(0)->widget());
    homePane = new HomePane(this);
    connect(homePane, &HomePane::PCODEtoCreate,log,&CT_Logue::generatePCODE);
    connect(homePane, &HomePane::addCode, log, &CT_Logue::getPCODE);
    hbox2 ->addWidget(homePane);
    return ;
}

void Mainview::theForm(QString &text){

    qDebug()<<"Emmited...";
    hbox2 ->removeWidget(pane);
    pane ->setVisible(false);
    log->downloadersList();
    form  = new Forms(this,log->getList(),&font);
    connect(form, &Forms::actionBtnClicked,this,&Mainview::sendFiles);
    hbox2 ->addWidget(form);
}
void Mainview::viewFile(const QString &path){
    hbox2->removeWidget(downloadPane);
    downloadPane->setVisible(false);
    viewFl = new ViewFile(this,path,&font);
    connect(viewFl, &ViewFile::getFileforPrinting,log,&CT_Logue::requestFile);
    hbox2->addWidget(viewFl);
    viewFl->setUpPage();

}

void Mainview::sendFiles(QString &selected){
    log->uploadFiles(pane->getFILES(),selected);
}

void Mainview::filesReceived(QJsonArray &fileNames){
    downloadPane->fetchFiles(fileNames);
}
void Mainview::fileDataReceived(const QByteArray &bytes, const QString &name){
    viewFl->printFile(bytes,name);
}
void Mainview::displayResMessage(const QString &message){
    responseTag->setText(message);
    responseTag->setVisible(true);
    QTimer::singleShot(3000,this,&Mainview::hideMessage);
}
void Mainview::hideMessage(){
    responseTag->setVisible(false);
}
