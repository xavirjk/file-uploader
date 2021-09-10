#include "downloadpane.h"
using namespace upld::ui;
class DownloadPane::Implementation {
public:Implementation(DownloadPane *_downloadPane, const QString &_text, QFont *_f):
        downloadPane(_downloadPane),
        text(_text),
        font(_f)
    {

    }
    DownloadPane *downloadPane{nullptr};
    QVBoxLayout *mainL = new QVBoxLayout;
    QGridLayout *grid;
    QString text;
    QFont *font;
    QJsonArray fileNames;
};

DownloadPane::DownloadPane(QWidget *parent, const QString &text, QFont *f) : QWidget(parent)
{
    implementation.reset(new Implementation(this, text, f));
    setLayout(implementation->mainL);
}

void DownloadPane::fetchFiles(QJsonArray &fileNames){
    implementation->fileNames = fileNames;
    implementation->font->setPixelSize(20);
    QLabel *label = new QLabel;
    implementation->grid = new QGridLayout;
    if(!fileNames.size()){
        label->setText("No Data Found");
        label->setProperty("class", "label");
        implementation->mainL->addWidget(label);
        implementation->grid->deleteLater();
        return;
    }
    int row = 0;
    for(const QJsonValue val: fileNames){
        label = new QLabel;
        label->setText(val.toObject().value("name").toString());
        label->setProperty("class", "label");
        implementation->grid->addWidget(label,row,0);
        for(const QJsonValue fileName: val.toObject().value("files").toArray()){
            QPushButton *fileBtn = new QPushButton;
            //Refactor

            QString name = fileName.toString();
            QString displayName = name.sliced(name.indexOf("-")+1);
            if(displayName.length() > 27) displayName = displayName.sliced(0,27)+ "...";
            fileBtn->setText(displayName);
            fileBtn->setProperty("source",fileName.toString());
            fileBtn->setProperty("class", "key");
            fileBtn->setProperty("class", "fileBtn");
            fileBtn->setMinimumSize(QSize(60, 30));
            implementation->grid->addWidget(fileBtn,++row,1);
            connect(fileBtn, &QAbstractButton::clicked,this, &DownloadPane::previewFile);
        }
        row++;
    }
    QWidget *scrollWidget = new QWidget;
    scrollWidget->setLayout(implementation->grid);
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->verticalScrollBar()->setProperty("class", "scrollbar");
    scrollArea->setWidget(scrollWidget);
    implementation->mainL->addWidget(scrollArea);
}

void DownloadPane::downloadfile(){
    qDebug()<<"Downloading file";
}

void DownloadPane::printFile(){
    qDebug()<<"Printing File";
}
void DownloadPane::previewFile(){
  QWidget *ww = implementation->grid->parentWidget();
  QList<QPushButton *> allPushButtons = ww->findChildren<QPushButton *>();
  for(int i = 0; i < allPushButtons.size(); i++){
      if(allPushButtons[i]->hasFocus()) {
          qDebug()<<"i:"<<allPushButtons[i]->property("source");
          QString file = QVariant(allPushButtons[i]->property("source")).toString();
          emit navigateViewFile(file);
          break;
      }
  }


}
QString DownloadPane::cleanName(const QString name) const{
    return name.sliced(name.indexOf("-")+1);
}
DownloadPane::~DownloadPane(){}
