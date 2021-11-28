#include "ct_logue.h"
#include <QUuid>
#include <QJsonObject>
#include <QJsonDocument>

using namespace CTLogue::network;
using namespace CTLogue::controllers;
using namespace CTLogue::Lib;
class CT_Logue::Implementation{
public:Implementation(CT_Logue *_ct_log):
        cT_Logue(_ct_log)
    {
        net = new NetworkAccessManager(cT_Logue);
        serverRequest = new ServerRequest(cT_Logue,net,QUrl());
        dbController = new  DBController(cT_Logue);

        connect(serverRequest, &ServerRequest::PCODEGenerated,cT_Logue, &CT_Logue::PCODEGenerated);
        connect(serverRequest, &ServerRequest::savePcode, cT_Logue, &CT_Logue::savePcode);
        connect(serverRequest, &ServerRequest::filesFound, cT_Logue, &CT_Logue::populateFiles);
        connect(serverRequest, &ServerRequest::fileData,cT_Logue, &CT_Logue::fileData);
        connect(serverRequest, &ServerRequest::resMessage,cT_Logue, &CT_Logue::onMessageReceived);
    }
    CT_Logue *cT_Logue{nullptr};
    QString PCODE;
    QString email;
    QString ref = "";
    QJsonArray dList,fileNames;
    NetworkAccessManager *net{nullptr};
    ServerRequest *serverRequest{nullptr};
    DBController *dbController{nullptr};
    int propMark = 0;

};

CT_Logue::CT_Logue(QObject *parent):data::DataDecorators(parent)
{
    implementation.reset(new Implementation(this));
}

void CT_Logue::downloadersList(){
    implementation->dList = implementation->dbController->all("entries");
}
QJsonArray CT_Logue::getList(){
    return implementation->dList;
}

void CT_Logue::uploadFiles(QStringList list, QString &PCODE){
    QString path = "http://localhost:3400/upF/upload/";
    implementation->serverRequest->setUrl(path);
    setId(QByteArray::fromHex(PCODE.toLocal8Bit()));
    setDecMode(true);
    implementation->serverRequest->executeUpload(list,translatedMessage());
}

void CT_Logue::generatePCODE(const QString &name, const QString &email){
    setDecMode(false);
    implementation->email = email;
    implementation->ref = name;
    QJsonObject obj;
    obj.insert("PCODE",getId());
    QJsonDocument doc(obj);
    QString path = "http://localhost:3400/upF/create/";
    implementation->serverRequest->setUrl(path);
    implementation->serverRequest->executePost(doc.toJson(),email);
}
void CT_Logue::getPCODE(const QString &name, const QString &code){
    implementation->ref = name;
    QString path = "http://localhost:3400/upF/getPCODE/";
    implementation->serverRequest->setUrl(path);
    implementation->serverRequest->executeSearch(code,"code");
}
void CT_Logue::PCODEGenerated(){
    implementation->dbController->createRow(encryptedPCODE(), implementation->ref.isEmpty()?"N/A":implementation->ref, implementation->email);
}
void CT_Logue::savePcode(const QString &PCODE){
    implementation->dbController->createPeersRow(PCODE,implementation->ref.isEmpty()?"N/A":implementation->ref);
}
void CT_Logue::fetchFiles(){
    implementation->fileNames = {};

    implementation->propMark = 0;
    QString path = "http://localhost:3400/upF/getfiles/";
    implementation->dList = implementation->dbController->all("peers");
    implementation->serverRequest->setUrl(path);
    fetchConsecutiveFiles();
}

void CT_Logue::populateFiles(QJsonObject fileNames){
    for(const QJsonValue val: implementation->dList) {
        if(val.toObject().find("PCODE").value() == fileNames.find("code").value()) {
            fileNames.insert("name",val.toObject().find("name").value());
            break;
        }
    }
    implementation->fileNames<<fileNames;
    if(implementation->propMark < implementation->dList.size()) fetchConsecutiveFiles();
    else emit fileNamesUpdated(implementation->fileNames);
}

void CT_Logue::fetchConsecutiveFiles(){
    implementation->serverRequest->executeSearch(implementation->dList[implementation->propMark].toObject().find("PCODE").value().toString(),"files");
    implementation->propMark += 1;
}

void CT_Logue::requestFile(const QUrl &path){
    implementation->serverRequest->setUrl(path);
    implementation->serverRequest->executeSearch("","");
}

void CT_Logue::fileData(const QByteArray &bytes){
    emit renderFile(bytes, "fl");
}

void CT_Logue::onMessageReceived(const QString &message){
    emit displayMessage(message);
}

CT_Logue::~CT_Logue(){}
