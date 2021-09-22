#ifndef HOMEPANE_H
#define HOMEPANE_H

#include <QWidget>
#include <QtWidgets>
#include <QLabel>
namespace CTLogue {
namespace ui {

class HomePane : public QWidget
{
    Q_OBJECT
public:
    explicit HomePane(QWidget *parent = nullptr);
    ~HomePane();

signals:
    void PCODEtoCreate(const QString &name, const QString &email);
    void addCode(const QString &name,const QString &code);

public slots:
    void generatePCODEBtnClicked();
    void setCodeBtnClicked();

private:
    QGroupBox *custom_upld, *custom_dwnld;
    QLineEdit *input1, *input2,*input3,*input4;

};
}}

#endif // HOMEPANE_H
