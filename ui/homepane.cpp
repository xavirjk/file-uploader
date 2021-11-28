#include "homepane.h"

#include <QtDebug>
namespace CTLogue {
namespace ui {

HomePane::HomePane(QWidget *parent) : QWidget(parent)
{
    QLabel *header1 = new QLabel(this);
    QLabel *header2 = new QLabel(this);
    header1->setText("File Upload Customs");
    header2->setText("File Download Customs");
    custom_upld = new QGroupBox(tr("Uploading"));
    custom_dwnld = new QGroupBox(tr("downloading"));
    QPushButton *genButton = new QPushButton("Generate");
    QPushButton *setCode = new QPushButton("Add Code");


    connect(genButton, &QPushButton::clicked, this,&HomePane::generatePCODEBtnClicked);
    connect(setCode, &QPushButton::clicked, this, &HomePane::setCodeBtnClicked);
    genButton->setProperty("class", "submit");
    setCode->setProperty("class", "submit");
    auto vbox1 = new QVBoxLayout;
    auto vbox2 = new QVBoxLayout;
    auto vbox = new QVBoxLayout;
    auto grid = new QGridLayout;
    auto grid1 = new QGridLayout;

    header1->setProperty("class","label");
    header2->setProperty("class","label");
    header1->setStyleSheet("text-decoration:underline");
    header2->setStyleSheet("text-decoration:underline");
    //header1->setText("File Upload Customs");
    QLabel *PName = new QLabel("Peer Name");
    QLabel *Pemail = new QLabel("Recipient Email");
    PName ->setProperty("class", "key");
    Pemail ->setProperty("class", "key");
    input1 = new QLineEdit;
    input2 = new QLineEdit;


    //header2->setText("File Download Customs");
    QLabel *PCODE = new QLabel("Peer Code");
    PCODE ->setProperty("class", "key");
    input3 = new QLineEdit;
    QLabel *PName2 = new QLabel("Peer Name");
    PName2 ->setProperty("class", "key");
    input4 = new QLineEdit;

    grid->addWidget(PName,0,0);
    grid->addWidget(input1,0,1);
    grid->addWidget(Pemail,1,0);
    grid->addWidget(input2,1,1);
    grid->addWidget(genButton,1,2);

    grid1->addWidget(PCODE,0,0);
    grid1->addWidget(input3,0,1);
    grid1->addWidget(PName2,1,0);
    grid1->addWidget(input4,1,1);
    grid1->addWidget(setCode,1,2);
    vbox1->addWidget(header1);
    vbox1->addLayout(grid,0);
    vbox2->addWidget(header2);
    vbox2->addLayout(grid1);

    custom_upld->setLayout(vbox1);
    custom_dwnld->setLayout(vbox2);
    vbox->addWidget(custom_upld);
    vbox->addWidget(custom_dwnld);
    setLayout(vbox);
}
void HomePane::generatePCODEBtnClicked(){
    emit PCODEtoCreate(input1->text(), input2->text());

}
void HomePane::setCodeBtnClicked(){
    emit addCode(input4->text(),input3->text());
}
HomePane::~HomePane(){}
}}
