#ifndef IDBCONTROLLER_H
#define IDBCONTROLLER_H

#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

#include "Upld_global.h"

namespace upld_lib {
namespace controllers {

class UPLD_EXPORT IDBController : public QObject {
    Q_OBJECT
public:
    IDBController(QObject *parent = nullptr):
        QObject(parent){}
    virtual ~IDBController(){}
    virtual bool createRow(const QString &id, const QString &name, const QString &email) const = 0;
    virtual bool createPeersRow(const QString &id, const QString &name) const  = 0;
    virtual bool deleteRow(const QString &tableName, const QString &id) const = 0;
    virtual QJsonObject readRow(const QString &tableName, const QString &id ) const = 0;
    virtual QJsonArray find(const QString &tableName, const QString &searchText) const = 0;
    virtual bool updateRow(const QString &tableName, const QString &id, const QJsonObject &payload) const = 0;
    virtual QJsonArray all(const QString &tableName) const  = 0;

};

}

}
#endif // IDBCONTROLLER_H
