#ifndef DATADECORATORS_H
#define DATADECORATORS_H

#include <QObject>
#include <Upld_global.h>
#include <QSharedPointer>

namespace upld_lib {
namespace data {
class DataDecorators : public QObject
{
    Q_OBJECT
public:
    explicit DataDecorators(QObject *parent = nullptr);
    ~DataDecorators();

    void setId(QString id) const;
    QString getId() const;
    QString translatedMessage() const;
    void setDecMode(bool mode);
    QString encryptedPCODE();

signals:
protected:
    void translateForsqlite();
private:
    class Implementation;
    QSharedPointer<Implementation> implementation;

};
}
}

#endif // DATADECORATORS_H
