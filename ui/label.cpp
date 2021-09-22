#include "label.h"
using namespace CTLogue::ui;

viewPane::viewPane(QWidget *parent, const QString &text):
    QWidget(parent) {

    _text = new QString(text);

    auto lab = new QPushButton(text);
    desc = new QLabel(this);
    desc->setText("Lorem ipsum dolor sit amet, consectetur adipiscing elit."
                  "Etiam id odio non sapien "
                  "\ntristique tempus eu sit amet est. "
                  "\nPraesent ullamcorper risus et ipsum suscipit, et tincidunt augue aliquam");
    desc->setProperty("class", "key");
    findFile = new QPushButton("select");

    findFile ->setProperty("class", "submit");
    selected = new QLabel(this);
    selected->setText("No File selected...");
    selected->setProperty("class", "label");
    findFile ->setProperty("class", "submit");
    connect(lab,&QAbstractButton::clicked,this,&viewPane::requestForm);
    connect(findFile, &QAbstractButton::clicked,this,&viewPane::openFile);

    lab ->setStyleSheet("padding: 20px");
    lab->setProperty("class", "submit");
    auto main = new QVBoxLayout;
    auto dispLabel = new QGridLayout;
    dispLabel->addWidget(findFile,0,0);
    dispLabel->addWidget(selected,0,1);
    main->addWidget(desc,0);
    main->addLayout(dispLabel,0);
    main ->addWidget(lab,1,Qt::AlignBottom);

    setLayout(main);
}

void viewPane::openFile(){
    qDebug()<<"Button clicked";
    fileNames = QFileDialog::getOpenFileNames(0,QString(),QString(),
                                                    tr("Files(*.png *.xpm *.jpg *.pdf .*doc .*docx .*xps)"));
    int files = fileNames.length();
    if(files==1) {
        QString displayName = fileNames[0].sliced(fileNames[0].lastIndexOf("/") + 1);
        if(displayName.length() > 27) displayName = displayName.sliced(0,27)+ "...";
        selected->setText(displayName);
    }
    else if(files>1){
        QString renderText = "Files Selected %1";
        selected->setText(renderText.arg(files));
    }
}


void viewPane::requestForm() {
    qDebug()<<"Emitting data";
    emit requestFormBtnClicked(*_text);
}

QStringList viewPane::getFILES(){
    return fileNames;
}

