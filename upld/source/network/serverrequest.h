#ifndef SERVERREQUEST_H
#define SERVERREQUEST_H

#include <QObject>
#include <QScopedPointer>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QHttpMultiPart>
#include <QHttpPart>
#include "Upld_global.h"
#include "network/IServerRequest.h"
#include "network/inetworkaccessmanager.h"

namespace upld{
namespace network {

class UPLD_EXPORT ServerRequest : public IServerRequest
{
    Q_OBJECT
public:
    explicit ServerRequest(QObject *parent = nullptr, INetworkAccessManager *networkAccessManager = nullptr, const QUrl &uri = QUrl());
    ~ServerRequest();

    QString encodeUser(const QString &user);
    void handleRes();
    void executePost(const QByteArray &data, const QString &user) override;
    void executeUpload(const QStringList list, const QString &PCODE) override;
    void executeSearch(const QString &text, const QString &searchkey) override;
    bool isBusy() const override;
    void setUrl(const QUrl &uri) override;
    QUrl uri() const override;

signals:
    void uriChanged();
    void isBusyChanged();
    void error(QString error);
    void requestComplete();
    void PCODEGenerated();
    void savePcode(const QString &pcode);
    void filesFound(QJsonObject fileNames);
    void fileData(const QByteArray &bytes);
    void resMessage(const QString message = "");

private slots:
    void replyDelegate();
    void sslErrors(const QList<QSslError>& errors);
    void mimeDelegate();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};

}
}


#endif // SERVERREQUEST_H
