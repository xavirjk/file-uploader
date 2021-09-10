#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QObject>
#include <QScopedPointer>

#include "i-db-controller.h"
#include "Upld_global.h"

namespace upld {
namespace controllers {
class UPLD_EXPORT DBController : public IDBController {
    Q_OBJECT
public:
    DBController(QObject *parent = nullptr);
    ~DBController();
    bool createRow(const QString &id, const QString &name, const QString &email) const override;
    bool createPeersRow(const QString &id, const QString &name) const override;
    bool deleteRow(const QString &tableName, const QString &id) const override;
    bool updateRow(const QString &tableName, const QString &id, const QJsonObject &payload) const override;
    QJsonObject readRow(const QString &tableName, const QString &id) const override;
    QJsonArray find(const QString &tableName, const QString &searchText) const override;
    QJsonArray all(const QString &tableName) const override;
private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}
#endif // DBCONTROLLER_H
