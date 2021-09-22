#ifndef DATADECORATORS_H
#define DATADECORATORS_H

#include <QObject>
#include <CT_Logue_global.h>
#include <QSharedPointer>

namespace CTLogue {
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
