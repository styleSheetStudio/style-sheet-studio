#ifndef PANELICON_H
#define PANELICON_H

#include <QObject>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "QFile"
#include "QFileDialog"
#include "QStandardPaths"
#include "QComboBox"
#include "texteditlabel.h"


class panelIcon : public QWidget
{
    Q_OBJECT
public:
    explicit panelIcon(QWidget *parent = nullptr);
    QLineEdit *pathEdit = new QLineEdit(this);
    QPushButton *pathBtns = new QPushButton(this);
void setupCheckBox();
    QString getIconPath();
    QString getHeight();
    QString getWidth();
    QString getRepeat();
    QString getPos();
     QLabel *rlabel;
       QLabel *plabel;
    QComboBox *editRepeat = new QComboBox(this);
    QComboBox *editPos = new QComboBox(this);

    TextEditLabel *editWidth;
    TextEditLabel *editHeight;
private:
// QFileDialog dlg();
 QString fileIconPath;
 void dataUpdate();
 void updatePath();
signals:
void onDataChanged();
};

#endif // PANELICON_H
