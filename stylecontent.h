#ifndef STYLECONTENT_H
#define STYLECONTENT_H

#include <QObject>
#include <QWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QSettings>
#include <QStandardPaths>
#include <QListWidgetItem>

class styleContent : public QWidget
{
    Q_OBJECT
public:
    explicit styleContent(QWidget *parent = nullptr);

    QListWidget *widgetlist = new QListWidget(this);
    QStringList list;
      QString path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

signals:

};

#endif // STYLECONTENT_H
