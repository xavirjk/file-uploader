#ifndef ISERVERREQUEST_H
#define ISERVERREQUEST_H

#include <QObject>
#include <QUrl>
#include <CT_Logue_global.h>

namespace CTLogue {
namespace network {

class CT_LOGUE_EXPORT IServerRequest: public QObject {
    Q_OBJECT
public:
    IServerRequest(QObject *parent = nullptr):
        QObject(parent){};
    virtual ~IServerRequest(){};

    virtual void executePost(const QByteArray &data,const QString &user) = 0;
    virtual void executeUpload(const QStringList list, const QString &PCODE) = 0;
    virtual void executeSearch(const QString &text,const QString &searchkey) = 0;
    virtual bool isBusy() const = 0;
    virtual void setUrl( const QUrl &uri) = 0;
    virtual QUrl uri() const = 0;

};

}
}
#endif // ISERVERREQUEST_H
