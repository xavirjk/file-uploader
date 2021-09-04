#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QtWidgets>
namespace upld {
namespace ui {


class  Mainview: public QWidget {
    Q_OBJECT
public:
    Mainview(QWidget *parent = nullptr);
    ~Mainview(){};

    void setUpHome();
signals:
    void uploadBtnClicked();
    void downloadBtcClicked();
    void homeBtnClicked();
public slots:
    void toggleUploadView();
    void toggleDownloadView();
    void toggleHomeView();
private:
    QLabel *responseTag = new QLabel;
    QHBoxLayout *hbox2,*hbox3;
    QFont font;

};

}}
#endif // MAINVIEW_H
