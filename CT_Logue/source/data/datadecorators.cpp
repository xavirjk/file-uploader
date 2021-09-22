#include "datadecorators.h"
#include <QUuid>

using namespace CTLogue::data;
class DataDecorators::Implementation {
public: Implementation(DataDecorators *_dataDecoarator):
        dataDecorator(_dataDecoarator)
    {}
    DataDecorators *dataDecorator{nullptr};
    QByteArray keyId = "U[#I`V.26\\CJ}*^9%7Z-_3TW$)Y;K]DX(FH4P?QM/A8SN:'0<@=!GL5>&+OR1{B,E|";
    QString LETTERS = "!#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`{|}";
    QByteArray id = "";
    QString translated;
    bool decrytionMode;
};

DataDecorators::DataDecorators(QObject *parent) : QObject(parent)
{
    implementation.reset(new Implementation(this));
}
void DataDecorators::setId(QString id) const{
    implementation ->id = id.toLocal8Bit();
}
void DataDecorators::translateForsqlite(){
    implementation->translated = "";
    QString charsA = implementation->LETTERS;
    QString charsB = implementation->keyId;

    if(implementation->decrytionMode){
        QString temp = charsA;
        charsA = charsB;
        charsB = temp;
    }
    for(QChar val: implementation->id) {
        if(val.isLower()) val = val.toUpper();
        int symIndex = charsA.indexOf(val);
        implementation->translated += charsB.at(symIndex).toLower();
    }
}
void DataDecorators::setDecMode(bool mode){
    if(!mode){
        implementation->id = QUuid::createUuid().toByteArray().mid(1,36);
    }
    implementation->decrytionMode  = mode;
    translateForsqlite();
}
QString DataDecorators::encryptedPCODE(){
    QByteArray bytes = implementation->translated.toLocal8Bit();
    return bytes.toHex();
}

QString DataDecorators::getId() const{
    return implementation->id;
}
QString DataDecorators::translatedMessage() const{
    return implementation->translated;
}
DataDecorators::~DataDecorators(){}
