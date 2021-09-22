#ifndef LABEL_H
#define LABEL_H

#include <QObject>
#include <QtWidgets>

namespace CTLogue {
namespace ui {

class viewPane : public QWidget {
    Q_OBJECT
public:
    viewPane(QWidget *parent = nullptr, const QString &text = "text");
    ~viewPane(){};

    QStringList getFILES();
public slots:
    void requestForm();
    void openFile();
signals :
    void requestFormBtnClicked(QString &text);
private:
    QString *_text ;
    QHBoxLayout *cont;
    QPushButton *findFile;
    QLabel *desc;
    QLabel *selected;

    QStringList fileNames;
};

}
}
#endif // LABEL_H
