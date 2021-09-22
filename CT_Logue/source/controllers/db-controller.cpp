#include "db-controller.h"
#include <QSqlDatabase>
#include <QJsonDocument>
#include <QSqlQuery>

using namespace CTLogue::controllers;

class DBController::Implementation {
public:
    Implementation(DBController *_DBController):
        dbController(_DBController)
    {
        if(init()) {
            qDebug()<<"Database created using "<<sqliteVersion();
            if(createTables()) qDebug()<<"Database Tables Created";
            else qDebug()<<"ERR! Unable to create Tables";
        }
        else qDebug()<<"Err creating Database";

    }
    DBController* dbController{nullptr};
    QSqlDatabase db;
    std::map<int, QString> tables = {{0,"entries"},{1,"peers"}};
private:
    bool init(){
        db = QSqlDatabase::addDatabase("QSQLITE","ct_l");
        db.setDatabaseName("ct_lentries");
        return db.open();
    }
    bool createTables(){
        for(const std::pair<int,QString> table : tables){
            if(!createJsonTable(table.second)) return false;
        }
        return true;
    }
    bool createJsonTable(const QString& tname){
        QSqlQuery query(db);
        QString sqlcmd = "CREATE TABLE IF NOT EXISTS %1 (id text primary key, name text not null, email text not null)";
        if(tname == "peers")sqlcmd = "CREATE TABLE IF NOT EXISTS %1 (id text primary key, name text not null)";
        if(!query.prepare(sqlcmd.arg(tname))) return false;
        return  query.exec();

    }
    QString sqliteVersion() const{
        QSqlQuery query(db);
        query.exec("SELECT sqlite_version()");
        if(query.next()) return query.value(0).toString();
        return  QString::number(-1);
    }

};
DBController::DBController(QObject *parent):
    IDBController(parent){
    implementation.reset(new Implementation(this));
}
DBController::~DBController(){};

bool DBController::createRow(const QString &id, const QString &name, const QString &email) const{
    if(id.isEmpty() || name.isEmpty()) return false;
    QSqlQuery query(implementation->db);
    QString sqlCmd = "INSERT OR REPLACE INTO entries (id, name, email) VALUES (:id, :name, :email)";
    if(!query.prepare(sqlCmd)) return false;
    query.bindValue(":id", QVariant(id));
    query.bindValue(":name", QVariant(name));
    query.bindValue(":email",QVariant(email));
    if(!query.exec()) return false;
    return query.numRowsAffected() > 0;
}
bool DBController::createPeersRow(const QString &id, const QString &name) const{
    if(id.isEmpty() || name.isEmpty()) return false;
    QSqlQuery query(implementation->db);
    QString sqlCmd = "INSERT OR REPLACE INTO peers (id, name) VALUES (:id, :name)";
    if(!query.prepare(sqlCmd)) return false;
    query.bindValue(":id", QVariant(id));
    query.bindValue(":name", QVariant(name));
    if(!query.exec()) return false;
    return query.numRowsAffected() > 0;
}

bool DBController::deleteRow(const QString &tableName, const QString &id) const{
    return true;
}

bool DBController::updateRow(const QString &tableName, const QString &id, const QJsonObject &payload) const{
    return true;
}
QJsonArray DBController::find(const QString &tableName, const QString &searchText) const{

}
QJsonArray DBController::all(const QString &tableName) const{
    QSqlQuery query(implementation->db);
    QString sqlCmd = "SELECT * FROM %1";
    if(!query.prepare(sqlCmd.arg(tableName))) return {};
    if(!query.exec()) return {};
    QJsonArray arr;
    while (query.next()) {
        QJsonObject obj;
        obj.insert("PCODE",query.value(0).toString());
        obj.insert("name",query.value(1).toString());
        if(!query.value(2).toString().isNull()){
            obj.insert("email",query.value(2).toString());
        }
        arr.append(obj);

    }
    return arr;
}

QJsonObject DBController::readRow(const QString &tableName, const QString &id) const{

}
