#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QtWidgets>
#include "label.h"
#include "form.h"
#include "homepane.h"
#include "downloadpane.h"
#include "viewfile.h"
#include <model/ct_logue.h>

using namespace CTLogue::Lib;
namespace CTLogue {
namespace ui {


class  Mainview: public QWidget {
    Q_OBJECT
public:
    Mainview(QWidget *parent = nullptr);
    ~Mainview(){};

    void setUpHome();
signals:
    void moviesBtnClicked();
    void tvShowBtcClicked();
    void booksBtnClicked();
public slots:
    void toggleMoviesView();
    void toggleTvShowView();
    void toggleBooksView();
    void theForm(QString &text );
    void viewFile(const QString &path);
    void sendFiles(QString &selected);
    void filesReceived(QJsonArray &fileNames);
    void fileDataReceived(const QByteArray &bytes, const QString &name);
    void displayResMessage(const QString &message);
    void hideMessage();
private:
    CT_Logue *log = new CT_Logue(this);
    QLabel *responseTag = new QLabel;
    viewPane *pane;
    DownloadPane *downloadPane;
    Forms *form;
    ViewFile *viewFl;
    HomePane *homePane;
    QHBoxLayout *hbox2,*hbox3;
    QFont font;

};

}}
#endif // MAINVIEW_H
