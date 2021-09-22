#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QtWidgets>
#include <QJsonArray>

namespace CTLogue {
namespace ui {

class Forms: public QWidget {
    Q_OBJECT
public:
    Forms(QWidget *parent = nullptr, const QJsonArray &arr = QJsonArray(), QFont *f = nullptr);
    ~Forms(){};

    void createForm();
    void setInputFields();
public slots:
    void submitBtnClicked();
    void radioBtnToggled();
signals:
    void actionBtnClicked(QString &selected);
    void test();
private:
    QString selected;
    QJsonArray *dList;
    QLabel *head1, *head2;
    QLineEdit *input1;
    QLineEdit *input2;
    QLineEdit *input3;
    QRadioButton *radio;

    QGridLayout *layout;
    QFont font;
    QJsonObject payload {
        {"f1",""},{"f2",""},{"f3",""}

    };
};

}}

#endif // FORM_H
