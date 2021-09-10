#ifndef VIEWFILE_H
#define VIEWFILE_H

#include <QWidget>
#include <QtWidgets>
#include <QFile>
#include <QFrame>
#include <QGraphicsView>
#include <QScopedPointer>
#include <CT_Logue_global.h>

namespace upld {
namespace ui {

class ViewFile : public QWidget
{
    Q_OBJECT
public:
    explicit ViewFile(QWidget *parent = nullptr, const QString &resource = "",QFont *f = nullptr);
    ~ViewFile();
    void setUpPage();
    void printFile(const QByteArray &bytes, const QString &name);
    void printfcn();
    void saveFile();
public slots:
    void handleBtnClick();
    void handlePrintFileBtn();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

signals:
    void getFileforPrinting(const QUrl &path);

};
}}

#endif // VIEWFILE_H
