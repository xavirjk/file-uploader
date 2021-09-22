#ifndef CT_LOGUE_H
#define CT_LOGUE_H

#include <QObject>
#include <QJsonObject>
#include <QVariant>
#include <QScopedPointer>
#include "CT_Logue_global.h"
#include "controllers/db-controller.h"
#include "network/serverrequest.h"
#include "network/networkaccessmanager.h"
#include "data/datadecorators.h"

namespace CTLogue {
namespace Lib {

class CT_LOGUE_EXPORT CT_Logue : public data::DataDecorators
{
    Q_OBJECT

public:
    CT_Logue(QObject *parent = nullptr);
    ~CT_Logue();

    void uploadFiles(QStringList list, QString &PCODE);
    void downloadersList();
    void fetchFiles();
    void fetchConsecutiveFiles();
    QJsonArray getList();
public slots:
    void generatePCODE(const QString &name, const QString &email);
    void getPCODE(const QString &name, const QString &code);
    void requestFile(const QUrl &path);
    void PCODEGenerated();
    void savePcode(const QString &PCODE);
    void populateFiles(QJsonObject fileNames);
    void fileData(const QByteArray &bytes);
    void onMessageReceived(const QString &message);
signals:
    void fileNamesUpdated(QJsonArray &fileNames);
    void renderFile(const QByteArray &bytes, const QString &name);
    void displayMessage(const QString &message);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
    QString *field;
};

}}


#endif // CT_LOGUE_H
