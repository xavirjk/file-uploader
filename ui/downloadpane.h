#ifndef DOWNLOADPANE_H
#define DOWNLOADPANE_H

#include <QWidget>
#include <QtWidgets>
#include <QScopedPointer>
#include <QScrollBar>
#include <QScrollArea>

namespace upld {
namespace ui {
class DownloadPane : public QWidget
{
    Q_OBJECT
public:
    explicit DownloadPane(QWidget *parent = nullptr, const QString &text = "",QFont *f = nullptr);
    ~DownloadPane();
    QString cleanName(const QString name = "") const;

public slots:
    void fetchFiles(QJsonArray &fileNames);
    void downloadfile();
    void printFile();
    void previewFile();

signals:
    void navigateViewFile(const QString &path);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};
}}

#endif // DOWNLOADPANE_H
