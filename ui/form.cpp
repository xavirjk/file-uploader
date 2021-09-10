#include "form.h"
using namespace upld::ui;

Forms::Forms(QWidget *parent, const QJsonArray &arr, QFont *f) :
    QWidget(parent) {
    dList = new QJsonArray(arr);
    font = *f;
    createForm();
}

void Forms::createForm(){
   qDebug()<<"d"<<dList->begin()->toObject();
    layout = new QGridLayout;
    QVBoxLayout *layout2 = new QVBoxLayout;
    QPushButton *submit = new QPushButton("Submit");
    submit ->setProperty("class", "submit");
    submit ->setFont(font);
    submit ->setText(tr("%1 Submit").arg("\uf067"));
    head1 = new QLabel(this);
    head2 = new QLabel(this);
    head1->setProperty("class", "label");
    head2->setProperty("class","label");
    head1->setText("Peer Name");
    head2->setText("Email Address");
    layout->addWidget(head1,0,0);
    layout->addWidget(head2,0,1);
    for(int i = 0; i < dList->size(); i++){
        QLabel *l1 = new QLabel(dList->at(i).toObject().value("name").toString());
        l1->setProperty("class", "key");
        layout->addWidget(l1,i+1,0);
        l1 = new QLabel(dList->at(i).toObject().value("email").toString());
        l1->setProperty("class", "key");
        layout->addWidget(l1,i+1,1);
        radio = new QRadioButton("Select Peer", this);
        layout->addWidget(radio,i+1,2);
        connect(radio, &QRadioButton::clicked, this,&Forms::radioBtnToggled);

    }
    QWidget *scrollWidget = new QWidget;
    scrollWidget->setLayout(layout);
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->verticalScrollBar()->setProperty("class", "scrollbar");
    scrollArea->setWidget(scrollWidget);
    layout2->addWidget(scrollArea,0);
    layout2->addWidget(submit,1,Qt::AlignBottom);
    connect(submit, &QAbstractButton::clicked, this, &Forms::submitBtnClicked);
    setLayout(layout2);
}

void Forms::submitBtnClicked(){
    emit actionBtnClicked(selected);
}

void Forms::setInputFields(){
    input1->setPlaceholderText("entry title");
    input2->setPlaceholderText("dd /mm /yy");
    input3->setPlaceholderText(tr("entry %1").arg(""));
}

void Forms::radioBtnToggled(){
    QWidget *ww = layout->parentWidget();
    QList<QRadioButton *> allRButtons = ww->findChildren<QRadioButton *>();
    for(int i = 0; i <dList->size(); i++){
        if(allRButtons[i]->isChecked()) {
            selected = dList->at(i).toObject().value("PCODE").toString();
            break;
        }
    }
}
