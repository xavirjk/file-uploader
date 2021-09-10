#include "serverrequest.h"
#include "QJsonDocument"
namespace upld {
namespace network {
class ServerRequest::Implementation {
public:Implementation(ServerRequest *_serverRequest, INetworkAccessManager *_networkAccessManager, const QUrl &_uri):
        serverRequest(_serverRequest),
        netWorkAccessManager(_networkAccessManager),
        uri(_uri)
    {}
    ServerRequest* serverRequest{nullptr};
    INetworkAccessManager* netWorkAccessManager{nullptr};
    QUrl uri{};
    QNetworkReply *response{nullptr};

    bool isBusy() const{
        return isBusy_ ;
    }
    bool handlingFl() const {
        return handlingFile;
    }
    void setIsBusy(bool value){
        if(value != isBusy_){
            isBusy_ = value;
            emit serverRequest->isBusyChanged();
        }
    }
    void setFileHandling(bool value){
        if(value != handlingFile){
            handlingFile = value;
        }
    }
private:
    bool isBusy_ {false};
    bool handlingFile{false};
};

ServerRequest::ServerRequest(QObject *parent, INetworkAccessManager *networkAccessManager, const QUrl &uri) : IServerRequest(parent)
{
    implementation.reset(new Implementation(this,networkAccessManager,uri));

}

ServerRequest::~ServerRequest(){}

void ServerRequest::executePost(const QByteArray &data, const QString &user){
    if(!implementation->netWorkAccessManager->isNetAccessible()){
        return;
    }
    implementation->setIsBusy(true);
    emit isBusyChanged();
    QNetworkRequest request;
    request.setRawHeader("Reference",encodeUser(user).toLocal8Bit());
    request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
    request.setUrl(implementation->uri);
    implementation->response =  implementation->netWorkAccessManager->post(request,data);
    handleRes();
}

void ServerRequest::executeUpload(const QStringList list, const QString &PCODE){
    QHttpMultiPart *multipart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    for(int i = 0; i < list.size(); i++) {
        QHttpPart filePart;
        QFile *file = new QFile(list[i]);
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader,QVariant("form-data; name = \"uploads\";filename=\""+list[i]+"\""));
        file->open(QIODevice::ReadOnly);
        filePart.setBodyDevice(file);
        file->setParent(multipart);
        multipart->append(filePart);
    }
    QNetworkRequest request;
    request.setUrl(implementation->uri);
    request.setRawHeader("Reference",encodeUser(PCODE).toLocal8Bit());
    implementation->response = implementation->netWorkAccessManager->upload(request,multipart);
    handleRes();
}
void ServerRequest::executeSearch(const QString &text, const QString &searchkey){
    if(!implementation->netWorkAccessManager->isNetAccessible()){
        return;
    }
    QNetworkRequest request;
    if(!(text.isEmpty()&&searchkey.isEmpty())) {
        request.setRawHeader(searchkey.toLocal8Bit(),text.toLocal8Bit().toBase64());
    }
    else {
        implementation->setFileHandling(true);
    }

    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setUrl(implementation->uri);
    implementation->response = implementation->netWorkAccessManager->get(request);
    handleRes();

}
bool ServerRequest::isBusy() const{
    return implementation->isBusy();
}
void ServerRequest::setUrl(const QUrl &uri) {
    if(implementation->uri != uri) {
        implementation->uri = uri;
        emit uriChanged();
    }

}

QUrl ServerRequest::uri() const{
    return implementation->uri;
}

void ServerRequest::replyDelegate(){
    implementation->setIsBusy(false);
    emit isBusyChanged();
    disconnect(implementation->response,&QNetworkReply::finished, this,&ServerRequest::replyDelegate);
    disconnect(implementation->response,&QNetworkReply::sslErrors, this,&ServerRequest::sslErrors);

    auto statusCode = implementation->response->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray data = implementation->response->readAll();
    QJsonDocument jsdoc(QJsonDocument::fromJson(data));
    auto json = jsdoc.object();
    QString message = json.find("message").value().toString();
    message = message.isEmpty()?"Server Unavailable!": message;
    emit resMessage(message);
    switch (statusCode) {
    case 201: {
        if(message == "PCODE success") {
            emit PCODEGenerated();
        }
        break;
    }
    case 200: {
        if(message == "pcode success") emit savePcode(json.find("PCODE").value().toString());
        else if(message == "files found") emit filesFound(json.find("files").value().toObject());
    }
    default:break;
    }
}

void ServerRequest::mimeDelegate(){
    disconnect(implementation->response,&QNetworkReply::finished, this,&ServerRequest::replyDelegate);
    disconnect(implementation->response,&QNetworkReply::sslErrors, this,&ServerRequest::sslErrors);
    disconnect(implementation->response,&QIODevice::readyRead,this,&ServerRequest::mimeDelegate);
    implementation->setFileHandling(false);
    QByteArray data = implementation->response->readAll();
    auto statusCode = implementation->response->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    emit fileData(data);
}

void ServerRequest::sslErrors(const QList<QSslError> &errors){
    QString sslError;
    for(const auto& error : errors){
        sslError += error.errorString() + "\n";
    }
    qDebug()<<"sslError"<<sslError;
    emit error(sslError);
}

void ServerRequest::handleRes(){
    if(implementation->response != nullptr){
        connect(implementation->response,&QNetworkReply::finished, this,&ServerRequest::replyDelegate);
        connect(implementation->response,&QNetworkReply::sslErrors, this,&ServerRequest::sslErrors);
        if(implementation->handlingFl()){
            connect(implementation->response,&QIODevice::readyRead,this,&ServerRequest::mimeDelegate);
        }
    }
}

QString ServerRequest::encodeUser(const QString &user){
    QByteArray ref = user.toLocal8Bit().toBase64();
    return "Bearer " + ref;
}

}}

